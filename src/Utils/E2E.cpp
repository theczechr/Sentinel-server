#include "E2E.hpp"
#include "Base64.hpp"
#include "CryptoVerifier.hpp"

#include <string>

using namespace sentinel::utils;

bool sentinel::utils::fingerprint_matches_pubkey_hex_b64(const std::string &fingerprint_hex,
                                                         const std::string &public_key_base64) {
	return sha256_hex_of_base64(public_key_base64) == fingerprint_hex;
}

std::optional<std::pair<std::string, unsigned long long>> sentinel::utils::parse_signed_payload_b64(const std::string &payload_b64) {
	std::vector<uint8_t> bytes = base64_decode(payload_b64);
	if (bytes.empty()) return std::nullopt;
	std::string payload(bytes.begin(), bytes.end());
	size_t sep = payload.find('|');
	if (sep == std::string::npos) return std::nullopt;
	std::string f = payload.substr(0, sep);
	std::string ts_str = payload.substr(sep + 1);
	if (ts_str.empty()) return std::nullopt;
	unsigned long long ts = 0ULL;
	try { ts = std::stoull(ts_str); } catch (...) { return std::nullopt; }
	return std::make_pair(f, ts);
}


