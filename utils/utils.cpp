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

std::string utils::gen_uuid()
{
	return std::string();
}

std::string gen_uuid()
{
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	return boost::lexical_cast<std::string>(uuid); // remake
}