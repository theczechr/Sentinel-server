#pragma once
#include "Table.hpp"
#include "UUID.hpp"
#include "UNIX_TS.hpp"

class AccountsTable : public Table
{
public:
	AccountsTable() : Table("Accounts",
		{
			{"uuid", "TEXT NOT NULL"},
			{"pub_key_fprint", "TEXT NOT NULL"},
			{"username", "TEXT NOT NULL"},
			{"recovery_phrase", "TEXT"},
			{"status", "INTEGER"},
			{"last_login", "INTEGER NOT NULL"}
		}
	) {}

	void create_account(std::string& pub_key_fprint, std::string& username, std::string& recovery_phrase, Core::UNIX_TS& last_login);
	void delete_account(Core::UUID& uuid, std::string& pub_key_fprint);
	void change_username(Core::UUID& uuid, std::string& pub_key_fprint, std::string& username);
	void change_pub_key_fprint(std::string& old_pub_key_fprint, std::string& new_pub_key_fprint);
	void change_recovery_phrase(Core::UUID uuid, std::string& pub_key_fprint, std::string& recovery_phrase);
	bool login_account(std::string& pub_key_fprint, Core::UNIX_TS& last_login);
};