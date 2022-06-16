#pragma once
#include <fstream>
#include <random>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace utils
{
	bool file_empty(std::ifstream& file);
	bool file_exist(std::string file);
}
