#pragma once
#include <trantor/utils/Logger.h>
#include <optional> // std::optional
#include "UUID.hpp"
#include "UNIX_TS.hpp"

class Account
{
public:
	Account() { this->status = true; }

	Utils::UUID get_uuid() const;
	void set_uuid(Utils::UUID uuid);

	std::string get_username() const;
	void set_username(std::string username);

	std::string get_pub_key_fprint() const;
	void set_pub_key_fprint(std::string pub_key_fprint);

	std::optional<std::string> get_recovery_phrase() const;
	void set_recovery_phrase(std::string recovery_phrase);

	std::string get_status() const;
	void set_status(std::string status);
private:
	Utils::UUID uuid;
	std::string username;
	/*
	 * Nebudeme storovat celej public key, ale jenom jeho fingerprint
	 * Ma mensi size a je to string takze to pro nas bude jednodussi
	 * E.g. 43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8
	*/
	std::string pub_key_fprint;
	bool recovery_enabled = true;
	std::string recovery_phrase;
	bool status; // active / inactive

	void require_active();
};