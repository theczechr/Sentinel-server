#pragma once
#include "Table.hpp"
#include "Account.hpp"

class AccountsTable : public Table
{
private:
	std::string table_name = "Accounts";
	std::vector<std::pair<std::string, std::string>> columns =
	{ 
		{"uuid", "TEXT NOT NULL"}, {"pub_key_fprint", "TEXT NOT NULL"}, {"username", "TEXT NOT NULL"}, {"recovery_phrase", "TEXT"}, {"status", "INTEGER"}, {"last_login", "INTEGER NOT NULL"}
	};
public:
	AccountsTable(Database& db) : Table(db, this->table_name, this->columns)
	{

	}

	void create_account(std::string& pub_key_fprint, std::string& username, std::string& recovery_phrase, unsigned long int& last_login);
	void delete_account(boost::uuids::uuid& uuid, std::string& pub_key_fprint);
	void change_username(boost::uuids::uuid& uuid, std::string& pub_key_fprint, std::string& username);
	void change_pub_key_fprint(std::string& pub_key_fprint, std::string& recovery_phrase);
	void change_recovery_phrase(boost::uuids::uuid uuid, std::string& pub_key_fprint, std::string& recovery_phrase);
	bool login_account(std::string& pub_key_fprint, unsigned long int& last_login);

};