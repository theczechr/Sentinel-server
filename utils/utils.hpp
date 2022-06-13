#pragma once
#include <fstream>
#include <random>

namespace utils
{
	bool file_empty(std::ifstream& file);
	bool file_exist(std::string file);
	size_t gen_id();
}
