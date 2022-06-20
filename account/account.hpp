#pragma once
#include <trantor/utils/Logger.h>
#include "database.hpp"

class Account
{
private:
	int verion;
	bool status; // active / inactive
	std::string uuid;
	std::string username;
	std::string email_hash;
	std::string password_hash;
	std::string number_hash;
public:
	int get_version();
	void set_version(int version);

	bool get_status();
	void set_status(bool status);

	std::string get_uuid();
	void set_uuid(std::string uuid);

	std::string get_username();
	void set_username(std::string username);

	std::string get_email_hash();
	void set_email_hash(std::string email_hash);

	std::string get_password_hash();
	void set_password_hash(std::string password_hash);

	std::string get_number_hash();
	void set_number_hash(std::string number_hash);
};
