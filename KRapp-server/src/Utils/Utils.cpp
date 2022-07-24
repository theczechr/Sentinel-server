#include "utils.hpp"

bool utils::file_exist(std::string file)
{
	std::ifstream ifile;
	ifile.open(file);
	if (!ifile)
		return false;
	return true;
}