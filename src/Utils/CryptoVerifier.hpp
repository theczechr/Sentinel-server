#pragma once
#include <string>
#include <vector>

namespace sentinel {
namespace utils {

    // Verify Ed25519 signature over message using a raw 32-byte public key.
    // Inputs are Base64 strings; returns true on successful verification.
    bool verify_ed25519_base64(const std::string &public_key_b64,
                               const std::string &message_b64,
                               const std::string &signature_b64);

    // Compute a simple hex fingerprint (SHA-256) of raw bytes.
    // Inputs are Base64; output is lowercase hex.
    std::string sha256_hex_of_base64(const std::string &data_b64);

} // namespace utils
} // namespace sentinel


