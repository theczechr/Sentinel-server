#pragma once
#include <trantor/utils/Logger.h>
#include <boost/uuid/uuid.hpp> // UUID class
#include <boost/uuid/uuid_generators.hpp> // UUID generator

class Account
{
private:
	boost::uuids::uuid uuid;
	/*
	 * Nebudeme storovat celej public key, ale jenom jeho fingerprint
	 * Ma mensi size a je to string takze to pro nas bude jednodussi
	 * E.g. 43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8
	*/
	std::string pub_key_fprint;
	std::string username;
	std::string recovery_phrase;
	bool status; // active / inactive
	unsigned long int last_login;
protected:
	boost::uuids::random_generator uuid_generator;
public:
	Account(std::string& pub_key_fprint, std::string& username, std::string& recovery_phrase, unsigned long int& last_login)
	{
		this->uuid = uuid_generator(); // Generate UUID
		this->pub_key_fprint = pub_key_fprint;
		this->username = username;
		this->recovery_phrase = recovery_phrase;
		this->status = true;
		this->last_login = last_login;
	}

	bool get_status() const;
	void set_status(bool status);

	boost::uuids::uuid get_uuid() const;

	std::string get_pub_key_fprint() const;
	void set_pub_key_fprint(std::string pub_key_fprint);

	std::string get_username() const;
	void set_username(std::string username);

	std::string get_recovery_phrase() const;
	void set_recovery_phrase(std::string recovery_phrase);

	long get_last_login() const;
	void set_last_login(unsigned long int last_login);
};
