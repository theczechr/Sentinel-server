#include "WebSocketAccount.hpp"
#include "Utils/CryptoVerifier.hpp"
#include "Utils/Base64.hpp"
#include "Utils/E2E.hpp"

#include <chrono>


void WebSocketAccount::handleNewMessage(const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &&message, const drogon::WebSocketMessageType &type) {
	std::string messageType = "Unknown";
	if (type == drogon::WebSocketMessageType::Text)
		messageType = "text";
	else if (type == drogon::WebSocketMessageType::Pong)
		messageType = "pong";
	else if (type == drogon::WebSocketMessageType::Ping)
		messageType = "ping";
	else if (type == drogon::WebSocketMessageType::Binary)
		messageType = "binary";
	else if (type == drogon::WebSocketMessageType::Close)
		messageType = "Close";

	LOG_INFO << "Message from '" << wsConnPtr->peerAddr().toIpPort() << "', message content '" << message
			 << "', message type '" << messageType << "'";
}

void WebSocketAccount::handleConnectionClosed(const drogon::WebSocketConnectionPtr &conn) {
	LOG_INFO << "Websocket connection closed!";
}

void WebSocketAccount::handleNewConnection(const drogon::HttpRequestPtr			&req,
											   const drogon::WebSocketConnectionPtr &conn) {
	LOG_INFO << "New websocket connection!";

	std::string input = req->getPath();

	switch (resolveOption(input)) {
		case Register: {
			LOG_INFO << "Request path '" << req->getPath() << "'";

			std::string username		= req->getParameter("username");
			std::string pub_key_fprint	= req->getParameter("pub_key_fprint");
			std::string recovery_phrase = req->getParameter("recovery_phrase");
			std::string public_key		= req->getParameter("public_key");
			// std::string last_login = req->getParameter("last_login"); // Dame do device

			auto acc = account_manager.create(username, pub_key_fprint, recovery_phrase);
			if (!public_key.empty()) {
				account_manager.upsert_public_key_for_pkf(pub_key_fprint, public_key);
			}

			conn->send("4444");

			return;
		}
		case Login: {
			LOG_INFO << "Request path '" << req->getPath() << "'";

			std::string pub_key_fprint = req->getParameter("pub_key_fprint");
			// std::string last_login = req->getParameter("last_login");

			return;
		}
		case Change_username: {
			LOG_INFO << "Request path '" << req->getPath() << "'";

			std::string pub_key_fprint = req->getParameter("pub_key_fprint");
			std::string new_username   = req->getParameter("new_username");
			// std::string last_login = req->getParameter("last_login");

			sentinel::account a = account_manager.get_by_pkf(pub_key_fprint);

			account_manager.update_username(a, new_username);

			conn->send("1");

			break;
		}
		case Recovery: {
			LOG_INFO << "Request path '" << req->getPath() << "'";

			std::string recovery_phrase = req->getParameter("recovery_phrase");
			std::string last_login		= req->getParameter("last_login");

			break;
		}
		case Get_pubkey: {
			LOG_INFO << "Request path '" << req->getPath() << "'";
			std::string target_pkf = req->getParameter("pub_key_fprint");
			auto pubkeyOpt = account_manager.get_public_key_by_pkf(target_pkf);
			if (pubkeyOpt.has_value()) {
				conn->send(pubkeyOpt.value());
			} else {
				conn->send("");
			}
			return;
		}
		case Publish_pubkey: {
			LOG_INFO << "Request path '" << req->getPath() << "'";
			std::string pub_key_fprint = req->getParameter("pub_key_fprint");
			std::string public_key		= req->getParameter("public_key");
			std::string signed_payload = req->getParameter("signed_payload"); // Base64 of the string being signed
			std::string signature		= req->getParameter("signature"); // Base64 of Ed25519 signature
			// Rate limit by ip + fingerprint
			std::string rl_key = conn->peerAddr().toIpPort() + "|" + pub_key_fprint;
			if (!publish_limiter.allow(rl_key)) {
				conn->send("0");
				return;
			}
			if (!pub_key_fprint.empty() && !public_key.empty()) {
				// Verify fingerprint matches published key
				if (!sentinel::utils::fingerprint_matches_pubkey_hex_b64(pub_key_fprint, public_key)) {
					conn->send("0");
					return;
				}
				// Verify signature matches the public key over the payload
				if (!sentinel::utils::verify_ed25519_base64(public_key, signed_payload, signature)) {
					conn->send("0");
					return;
				}
				// Replay protection: payload must be "fprint|timestamp" and recent
				auto parsed = sentinel::utils::parse_signed_payload_b64(signed_payload);
				if (!parsed.has_value()) {
					conn->send("0");
					return;
				}
				const std::string &payload_fprint = parsed->first;
				unsigned long long payload_ts = parsed->second;
				if (payload_fprint != pub_key_fprint) {
					conn->send("0");
					return;
				}
				const unsigned long long now = static_cast<unsigned long long>(std::chrono::duration_cast<std::chrono::seconds>(
											std::chrono::system_clock::now().time_since_epoch())
											.count());
				constexpr unsigned long long kMaxAgeSeconds = 300ULL; // 5 minutes
				if (payload_ts > now || (now - payload_ts) > kMaxAgeSeconds) {
					conn->send("0");
					return;
				}
				account_manager.upsert_public_key_for_pkf(pub_key_fprint, public_key);
				conn->send("1");
				return;
			}
			conn->send("0");
			return;
		}

		// handles Option_Invalid and any other missing/unmapped cases
		default: {
			LOG_ERROR << "Request path '" << req->getPath() << "' doesnt exist";
			break;
		}
	}
}
