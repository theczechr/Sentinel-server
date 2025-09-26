#include "Base64.hpp"

#include <algorithm>
#include <openssl/evp.h>

using namespace sentinel::utils;

static inline std::string sanitize_b64(const std::string &in) {
	std::string out;
	out.reserve(in.size());
	for (char c : in) {
		if (c == '\n' || c == '\r' || c == ' ' || c == '\t') continue;
		out.push_back(c);
	}
	return out;
}

std::vector<uint8_t> base64_decode(const std::string &input_base64) {
	std::string in = sanitize_b64(input_base64);
	if (in.empty()) return {};
	const size_t in_len = in.size();
	std::vector<uint8_t> out(((in_len + 3) / 4) * 3);
	int len = EVP_DecodeBlock(out.data(), reinterpret_cast<const unsigned char *>(in.data()), static_cast<int>(in_len));
	if (len < 0) {
		return {};
	}
	// Adjust for padding
	int pad = 0;
	if (in_len >= 2) {
		if (in[in_len - 1] == '=') pad++;
		if (in[in_len - 2] == '=') pad++;
	}
	out.resize(static_cast<size_t>(len - pad));
	return out;
}

// Optional: simple Base64 encode for tests/utilities
std::string base64_encode(const std::vector<uint8_t> &data) {
	if (data.empty()) return {};
	int out_len = 4 * ((static_cast<int>(data.size()) + 2) / 3);
	std::string out;
	out.resize(static_cast<size_t>(out_len));
	int written = EVP_EncodeBlock(reinterpret_cast<unsigned char *>(&out[0]), data.data(), static_cast<int>(data.size()));
	if (written > 0) out.resize(static_cast<size_t>(written));
	return out;
}


