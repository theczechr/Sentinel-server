#pragma once
#include "console.hpp"
#include "hashing.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Register
{
private:
	bool is_empty(std::ifstream& pFile);
	bool control(std::string to_check, int type, int min_length, int max_length);
	bool login_control();
public:
	std::string registration(std::string tag, int type, int min_length, int max_length);
	void create_account();
	void login();
};