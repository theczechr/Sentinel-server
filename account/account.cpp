#include "account.hpp"

bool account::authorize(std::string uuid)
{
	LOG_INFO << "Authorizing '" << uuid << "'";

	if (database::item_exist("id", uuid))
	{
		return false;
	}
	return true;
}

void account::change_username(std::string old_username, std::string new_username)
{
	LOG_INFO << "Changing username from '" << old_username << "' to '" << new_username << "'";
	database::update_user("username", old_username, new_username);
}

void account::change_email_hash(std::string old_hash, std::string new_hash)
{
	LOG_INFO << "Changing email hash from '" << old_hash << "' to '" << new_hash << "'";
	database::update_user("email_hash", old_hash, new_hash);
}

void account::change_password_hash(std::string old_hash, std::string new_hash)
{
	LOG_INFO << "Changing password hash from '" << old_hash << "' to '" << new_hash << "'";
	database::update_user("password_hash", old_hash, new_hash);
}

bool account::create(std::string uuid, std::string username, std::string email_hash, std::string password_hash, std::string phone_hash, std::string recovery_phrase)
{
	if (database::user_exist_full(uuid, username, email_hash, password_hash, phone_hash))
	{
		return false;
	}
	database::create_account(uuid, username, email_hash, password_hash, phone_hash, recovery_phrase);

	return true;
}

bool account::login(std::string username, std::string password_hash)
{
	if (!database::user_exist(username, password_hash))
	{
		return false;
	}
	return true;
}
