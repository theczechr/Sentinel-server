#pragma once
#include "utils.hpp"
#include "hashing.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Account
{
private:
	bool is_empty(std::ifstream& pFile); // Replace
	bool control(std::string to_check, int type, int min_length, int max_length);
	bool login_control();
	// Merge control and login_control
public:
	std::string registration(std::string tag, int type, int min_length, int max_length); // Replace
	void create();
	void login();
};