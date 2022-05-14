#pragma once
#include "utils.hpp"
#include "hashing.hpp"
#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>

class Account
{
	// Register
	bool valid_email(std::string email);
	bool valid_password(std::string password);
	void create();

	bool control(std::string to_check, int min_length, int max_length);
	std::string registration(std::string tag, int min_length, int max_length); // Remove and implement it in create
	void login();

	void close(); // Delete account
	void reopen(); // Only within x days
	// Add things like change username, email, password etc.
};