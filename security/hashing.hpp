#pragma once
#include <string>
#include "../vendor/bcrypt/include/crypt.h"

size_t hash(const std::string& to_hash);