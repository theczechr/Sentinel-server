#include "account.hpp"

void Account::change_username(std::string& old_username, std::string& new_username)
{
	LOG_INFO << "Changing username from '" << old_username << "' to '" << new_username << "'.";
	database::update_user("username", old_username, new_username);
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
