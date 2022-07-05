#pragma once
#include <trantor/utils/Logger.h>
#include "database.hpp"

#include <botan/pubkey.h>
#include <botan/rng.h>
#include <botan/rsa.h>

class Account
{
private:
	bool status; // active / inactive

	std::string uuid;
	Botan::RSA_PublicKey pub_key;
	std::string username;
	std::string recovery_phrase;
	long last_login; // mozna neco jineho nez long
	// ...
public:
	bool get_status();
	void set_status(bool status);

	std::string get_uuid();
	void set_uuid(std::string uuid);

	Botan::RSA_PublicKey get_pub_key();
	void set_pub_key(Botan::RSA_PublicKey pub_key);

	std::string get_username();
	void set_username(std::string username);

	std::string get_recovery_phrase();
	void set_recovery_phrase(std::string recovery_phrase);

	long get_last_login();
	void set_last_login(long last_login);
};
