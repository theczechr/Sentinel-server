#include "utils.hpp"

bool utils::file_empty(std::ifstream& file) // not needed, CRT default function should be used
{
	return file.peek() == std::ifstream::traits_type::eof();
}

bool utils::file_exist(std::string file)
{
	std::ifstream ifile;
	ifile.open(file);
	if (!ifile)
		return false;
	return true;
}