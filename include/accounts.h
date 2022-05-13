#pragma once
#include "Console.h"
#include "hashing.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


bool is_empty(std::ifstream& pFile);
void createAccount();
bool logincontrol();
void login();