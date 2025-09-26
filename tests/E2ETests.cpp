#include "Utils/E2E.hpp"
#include "Utils/Base64.hpp"
#include <cassert>
#include <iostream>

int main() {
	// fingerprint match check
	std::vector<uint8_t> pub = {1,2,3,4};
	std::string pub_b64 = sentinel::utils::base64_encode(pub);
	std::string hex = sentinel::utils::sha256_hex_of_base64(pub_b64);
	assert(sentinel::utils::fingerprint_matches_pubkey_hex_b64(hex, pub_b64));

	// payload parse
	std::string payload = hex + "|" + std::to_string(123456789ULL);
	std::vector<uint8_t> bytes(payload.begin(), payload.end());
	std::string payload_b64 = sentinel::utils::base64_encode(bytes);
	auto parsed = sentinel::utils::parse_signed_payload_b64(payload_b64);
	assert(parsed.has_value());
	assert(parsed->first == hex);
	assert(parsed->second == 123456789ULL);

	std::cout << "E2ETests OK\n";
	return 0;
}

