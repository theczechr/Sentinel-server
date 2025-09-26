#pragma once
#include <optional>
#include <string>

namespace sentinel {
namespace utils {

    // Returns true if hex fingerprint equals SHA-256 of base64 public key
    bool fingerprint_matches_pubkey_hex_b64(const std::string &fingerprint_hex,
                                            const std::string &public_key_base64);

    // Parse payload of format: "<fingerprint_hex>|<unix_ts>" from Base64 into components
    std::optional<std::pair<std::string, unsigned long long>> parse_signed_payload_b64(const std::string &payload_b64);

} // namespace utils
} // namespace sentinel


