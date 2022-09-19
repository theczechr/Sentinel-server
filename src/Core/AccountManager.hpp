#pragma once
#include "../Configuration/DatabaseTables.hpp"
#include "Account.hpp"

namespace Sentinel {

	class AccountManager {
	  public:
		AccountManager() {
			//this->table_ = sentinel::storage::table("Accounts", {{"uuid", "TEXT NOT NULL"}, {"username", "TEXT NOT NULL"}, {"pub_key_fprint", "TEXT NOT NULL"}, {"recovery_phrase", "TEXT"}, {"status", "TEXT NOT NULL"}, {"last_login", "INTEGER NOT NULL"}});
		}

		Account create(Username& username, std::string& pub_key_fprint, std::string& recovery_phrase);
		Account update_username(Account& account, Username new_username);
		Account update_pkf(Account& account, std::string new_public_key_fingerprint);
		Account update_recovery_phrase(Account& account, std::string new_recovery_phrase);
		Account get_by_uuid(UUID& uuid);
		Account get_by_pkf(std::string public_key_fingerprint);

		bool login(Account& account);
		void delete_(Account& account);

	  private:
		UUID								 uuid_;
		Configuration::DatabaseTables::Table table_;
	};

}// namespace Sentinel
