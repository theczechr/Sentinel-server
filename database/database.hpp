#pragma once
#include <trantor/utils/Logger.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "utils.hpp"

namespace database
{
	void create();
	void display();
	void create_account(std::string username, std::string email_hash, std::string password_hash, std::string phone_hash, std::string recovery_phrase);
	std::string get(std::string item);
}