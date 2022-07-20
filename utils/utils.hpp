#pragma once
#include <fstream>

namespace utils
{
	bool file_empty(std::ifstream& file);
	bool file_exist(std::string file);
}
