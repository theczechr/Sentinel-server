#pragma once
#include "Storage/DatabaseTable.hpp"
#include "Account.hpp"

#include <unordered_map>
#include "Storage/PublicKeyStore.hpp"

namespace sentinel {

	class account_manager {
	  public:
		account_manager() : key_store_{"keys.db"} {
			// this->table_ = sentinel::storage::table(
			// 	"Accounts", {
			// 		{"uuid", "TEXT NOT NULL"},
			// 		{"username", "TEXT NOT NULL"},
			// 		{"pub_key_fprint", "TEXT NOT NULL"},
			// 		{"recovery_phrase", "TEXT"},
			// 		{"status", "TEXT NOT NULL"},
			// 		{"last_login", "INTEGER NOT NULL"}
			// 	});
		}

		account create(std::string &username, std::string &pub_key_fprint, std::string &recovery_phrase);
		account update_username(account &account, std::string new_username);
		account update_pkf(account &account, std::string new_public_key_fingerprint);
		account update_recovery_phrase(account &account, std::string new_recovery_phrase);
		account get_by_uuid(sentinel::utils::UUID &uuid);
		account get_by_pkf(std::string public_key_fingerprint);

		bool login(account &account);
		void delete_(account &account);

		// New helpers for E2E key discovery (persisted)
		std::optional<std::string> get_public_key_by_pkf(const std::string &public_key_fingerprint) const;
		void upsert_public_key_for_pkf(const std::string &public_key_fingerprint, const std::string &public_key);
		void erase_public_key_for_pkf(const std::string &public_key_fingerprint);

	  private:
		sentinel::utils::UUID	 uuid_;
		// sentinel::storage::table table_;

		// In-memory index for accounts (PoC)
		std::unordered_map<std::string, account> pkf_to_account_;
		storage::PublicKeyStore key_store_;
	};

}// namespace sentinel
