#pragma once
#include <trantor/utils/Logger.h>
#include "database.hpp"

namespace account
{
	bool authorize(std::string uuid);

	void change_username(std::string old_username, std::string new_username);
	void change_email_hash(std::string old_hash, std::string new_hash);
	void change_password_hash(std::string old_hash, std::string new_hash);

	bool create(std::string uuid, std::string username, std::string email_hash, std::string password_hash, std::string phone_hash, std::string recovery_phrase);
	bool login(std::string username, std::string password_hash);
	void close(); // Delete account
	void reopen(); // Only within x days ?
};
