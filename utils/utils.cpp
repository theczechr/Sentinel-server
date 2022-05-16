#include "utils.hpp"

bool utils::file_empty(std::ifstream& file) // not needed, CRT default function should be used
{
	return file.peek() == std::ifstream::traits_type::eof();
}
