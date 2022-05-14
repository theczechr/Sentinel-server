#include "utils.hpp"

void utils::cflush() // clearing out the console
{
	std::system("CLS"); // this works only for windows
}

bool utils::is_file_empty(std::ifstream& file) // not needed, CRT default function should be used
{
	return file.peek() == std::ifstream::traits_type::eof();
}
