#include "WebSocketChat.hpp"

void WebSocketChat::handleNewMessage(const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &&message, const drogon::WebSocketMessageType &type) {
	if (type == drogon::WebSocketMessageType::Ping) {
		LOG_DEBUG << "recv a ping";
	} else if (type == drogon::WebSocketMessageType::Text) {
		if (message.size() > kMaxMessageBytes) {
			LOG_WARN << "Dropping oversized message from '" << wsConnPtr->peerAddr().toIpPort() << "'";
			return;
		}
		auto &s = wsConnPtr->getContextRef<Subscriber>();
		// Broadcast without logging plaintext to keep E2E opaque on the server
		chatRooms_.publish(s.chatRoomName_, message);
	}

	// Avoid logging full plaintext message contents for privacy
	LOG_INFO << "Message from '" << wsConnPtr->peerAddr().toIpPort() << "'";
}

void WebSocketChat::handleConnectionClosed(const drogon::WebSocketConnectionPtr &conn) {
	LOG_INFO << "Websocket connection closed!";
	auto &s = conn->getContextRef<Subscriber>();
	if (s.id_) {
		std::cout << " unsubscribe";
		chatRooms_.unsubscribe(s.chatRoomName_, *s.id_);
	} else {
		std::cout << " shutdown";
		conn->shutdown();
	}
}

void WebSocketChat::handleNewConnection(const drogon::HttpRequestPtr &req, const drogon::WebSocketConnectionPtr &conn) {
	LOG_DEBUG << "New websocket connection!";

	std::string input = req->getPath();
	Subscriber	s;
	s.chatRoomName_				 = req->getParameter("room_name");
	std::string example_chatroom = "karol";
	std::string example_userid	 = "187";

	switch (resolveOption(input)) {
		case Send_txt: {
			if (s.chatRoomName_ == example_chatroom) {
				break;
			} else {
				conn->setContext(std::make_shared<Subscriber>(std::move(s)));
				foo(conn, Wrong_chatroom);// jen test ale asi to bude vypada takto ta funkce
				return;
			}
		}

		case Send_media: {
			return;
		}

		case Create_chatroom: {
			return;
		}

		case Delete_chatroom: {
			return;
		}

		default: {
			return;
		}
	}
	conn->send("successful connection");
	s.id_ = chatRooms_.subscribe(s.chatRoomName_, [conn](const std::string &topic, const std::string &message) {
		(void) topic;
		conn->send(message);
	});
	conn->setContext(std::make_shared<Subscriber>(std::move(s)));
	return;
}
