#pragma once
#include <trantor/utils/Logger.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "utils.hpp"

namespace database
{
	void create();
	void display();
	void create_account(std::string username, std::string email_hash, std::string password_hash, std::string phone_hash, std::string recovery_phrase);
	bool user_exist(std::string username, std::string email_hash, std::string password_hash, std::string phone_hash);
	void update_user(std::string data_type, std::string old_data, std::string new_data);
}