#include "CryptoVerifier.hpp"
#include "Base64.hpp"

#include <openssl/evp.h>
#include <openssl/sha.h>

using namespace sentinel::utils;

bool sentinel::utils::verify_ed25519_base64(const std::string &public_key_b64,
                                            const std::string &message_b64,
                                            const std::string &signature_b64) {
	std::vector<uint8_t> pub = base64_decode(public_key_b64);
	std::vector<uint8_t> msg = base64_decode(message_b64);
	std::vector<uint8_t> sig = base64_decode(signature_b64);
	if (pub.size() != 32 || sig.size() != 64 || msg.empty()) return false;

	EVP_PKEY *pkey = EVP_PKEY_new_raw_public_key(EVP_PKEY_ED25519, nullptr, pub.data(), pub.size());
	if (!pkey) return false;

	EVP_MD_CTX *ctx = EVP_MD_CTX_new();
	if (!ctx) {
		EVP_PKEY_free(pkey);
		return false;
	}
	bool ok = false;
	if (EVP_DigestVerifyInit(ctx, nullptr, nullptr, nullptr, pkey) == 1) {
		if (EVP_DigestVerify(ctx, sig.data(), sig.size(), msg.data(), msg.size()) == 1) {
			ok = true;
		}
	}
	EVP_MD_CTX_free(ctx);
	EVP_PKEY_free(pkey);
	return ok;
}

static std::string to_hex(const uint8_t *data, size_t len) {
	static const char *hex = "0123456789abcdef";
	std::string out;
	out.resize(len * 2);
	for (size_t i = 0; i < len; ++i) {
		out[2*i] = hex[(data[i] >> 4) & 0xF];
		out[2*i+1] = hex[data[i] & 0xF];
	}
	return out;
}

std::string sentinel::utils::sha256_hex_of_base64(const std::string &data_b64) {
	std::vector<uint8_t> data = base64_decode(data_b64);
	uint8_t out[SHA256_DIGEST_LENGTH];
	SHA256(data.data(), data.size(), out);
	return to_hex(out, sizeof(out));
}


