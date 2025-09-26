#include "PublicKeyStore.hpp"

#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace sentinel::storage;

namespace {
static std::unordered_map<std::string, std::string> load_map(const std::string &path) {
    std::unordered_map<std::string, std::string> map;
    std::ifstream in(path);
    if (!in.good()) {
        return map;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto tab = line.find('\t');
        if (tab == std::string::npos) continue;
        std::string key = line.substr(0, tab);
        std::string value = line.substr(tab + 1);
        map[key] = value;
    }
    return map;
}

static void save_map(const std::string &path, const std::unordered_map<std::string, std::string> &map) {
    std::ofstream out(path, std::ios::trunc);
    for (const auto &kv : map) {
        out << kv.first << '\t' << kv.second << '\n';
    }
}
} // namespace

PublicKeyStore::PublicKeyStore(const std::string &file_path) : file_path_(file_path) {
    ensure_initialized();
}

std::optional<std::string> PublicKeyStore::get_by_fingerprint(const std::string &fingerprint) const {
    auto map = load_map(file_path_);
    auto it = map.find(fingerprint);
    if (it == map.end()) return std::nullopt;
    return it->second;
}

void PublicKeyStore::upsert(const std::string &fingerprint, const std::string &public_key) {
    auto map = load_map(file_path_);
    map[fingerprint] = public_key;
    save_map(file_path_, map);
}

void PublicKeyStore::erase(const std::string &fingerprint) {
    auto map = load_map(file_path_);
    map.erase(fingerprint);
    save_map(file_path_, map);
}

void PublicKeyStore::ensure_initialized() const {
    std::ifstream in(file_path_);
    if (!in.good()) {
        std::ofstream out(file_path_, std::ios::app);
    }
}


