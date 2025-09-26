#pragma once
#include <optional>
#include <string>

namespace sentinel {
namespace storage {

    class PublicKeyStore {
      public:
        explicit PublicKeyStore(const std::string &file_path);

        std::optional<std::string> get_by_fingerprint(const std::string &fingerprint) const;
        void upsert(const std::string &fingerprint, const std::string &public_key);
        void erase(const std::string &fingerprint);

      private:
        std::string file_path_;
        // naive file format: one record per line: <fingerprint>\t<base64_public_key>\n
        void ensure_initialized() const;
    };

} // namespace storage
} // namespace sentinel


