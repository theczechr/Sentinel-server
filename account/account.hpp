#pragma once
#include <trantor/utils/Logger.h>
#include "database.hpp"

class Account
{
public:
	void change_username(std::string old_username, std::string new_username);
	void change_email_hash(std::string old_hash, std::string new_hash);
	void change_password_hash(std::string old_hash, std::string new_hash);

	void create(const std::string& username, const std::string& email, const std::string& password, const std::string& phone_number, const std::string& recovery_phrase);
	void login(const std::string& username, std::string password) const;
	void close(); // Delete account
	void reopen(); // Only within x days ?
};
