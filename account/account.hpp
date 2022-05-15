#pragma once
#include "utils.hpp"
#include "hashing.hpp"
#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>

class Account
{
	size_t username;
	size_t email;
	size_t password;
	// Mozna zmenit datatyp ? ^
	int phone_number;

	bool valid_username(std::string username);
	bool valid_email(std::string email);
	bool valid_password(std::string password);
	void create(std::string username, std::string email, std::string password, int phone_number);

	void login();

	void change_username();
	void change_email();
	void change_password();

	void close(); // Delete account
	void reopen(); // Only within x days ?
};

// Mozna zvlast funkce na registraci a v te funkci by se proste vytvarel Account
// Musime se o tom pobavit, ale podle me to bude lepsi
// Premyslel jsem nad tim vic a ztratil jsem se v tom..