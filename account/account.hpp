#pragma once
#include <trantor/utils/Logger.h>

#include <botan/pubkey.h>
#include <botan/rng.h>
#include <botan/rsa.h>

class Account
{
private:
	std::string uuid;
	Botan::RSA_PublicKey pub_key;
	std::string username;
	std::string recovery_phrase;
	bool status; // active / inactive
	unsigned long int last_login; // mozna neco jineho nez long
	// ...
public:
	bool get_status() const;
	void set_status(bool status);

	std::string get_uuid() const;
	void set_uuid(std::string uuid);

	Botan::RSA_PublicKey get_pub_key() const;
	void set_pub_key(Botan::RSA_PublicKey pub_key);

	std::string get_username() const;
	void set_username(std::string username);

	std::string get_recovery_phrase() const;
	void set_recovery_phrase(std::string recovery_phrase);

	long get_last_login() const;
	void set_last_login(unsigned long int last_login);
};
