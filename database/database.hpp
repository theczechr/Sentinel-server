#pragma once
#include <trantor/utils/Logger.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "utils.hpp"

namespace database
{
	// uuid | username | email_hash | password_hash | phone_hash | recovery_hash | active
	void create();
	bool item_exist(std::string name, std::string value);
	void create_account(std::string uuid, std::string username, std::string email_hash, std::string password_hash, std::string phone_hash, std::string recovery_hash);
	bool user_exist(std::string email_hash, std::string phone_hash);
	//bool user_exist(std::string username, std::string password_hash);
	void update(std::string data_type, std::string old_data, std::string new_data);
}