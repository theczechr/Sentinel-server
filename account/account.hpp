#pragma once
#include "utils.hpp"
#include "hashing.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

class Account
{
	bool control(std::string to_check, int type, int min_length, int max_length);

	std::string registration(std::string tag, int type, int min_length, int max_length); // Replace
	void create();
	void login();
};