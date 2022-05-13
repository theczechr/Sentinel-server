#pragma once
#include "console.hpp"
#include "hashing.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

bool is_empty(std::ifstream& pFile);
void create_account();
bool login_control();
void login();