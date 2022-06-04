#include "account.hpp"

void Account::change_username(std::string& old_username, std::string& new_username)
{
	LOG_INFO << "Changing username from '" << old_username << "' to '" << new_username << "'";
	if (database::item_exist("username", old_username))
	{
		LOG_ERROR << "Username '" << old_username << "' already exist";
		return;
	}
	database::update_user("username", old_username, new_username);
}

void Account::change_email_hash(std::string& old_hash, std::string& new_hash)
{
	LOG_INFO << "Changing email hash from '" << old_hash << "' to '" << new_hash << "'";
	if (database::item_exist("email_hash", old_hash))
	{
		LOG_ERROR << "Email hash '" << old_hash << "' already exist";
		return;
	}
	database::update_user("email_hash", old_hash, new_hash);
}

void Account::change_password_hash(std::string& old_hash, std::string& new_hash)
{
	LOG_INFO << "Changing password hash from '" << old_hash << "' to '" << new_hash << "'";
	if (database::item_exist("password_hash", old_hash))
	{
		LOG_ERROR << "Email hash '" << old_hash << "' already exist";
		return;
	}
	database::update_user("password_hash", old_hash, new_hash);
}

void Account::create(const std::string& username, const std::string& email, const std::string& password, const std::string& phone_number, const std::string& recovery_phrase)
{
	if (database::user_exist_full(username, email, password, phone_number))
	{
		LOG_ERROR << "Cannot create account, because account already exist.";
		return;
	}
	database::create_account(username, email, password, phone_number, recovery_phrase);
	LOG_INFO << "Registered successufully!";
}

void Account::login(const std::string& username, std::string password) const
{
	if (!database::user_exist(username, password))
	{
		LOG_ERROR << "User doesnt exist, please register.";
		return;
	}
	LOG_INFO << "Logged successufully!";
}
