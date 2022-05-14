#pragma once
#include <iostream>
#include <fstream>

namespace utils
{
	template<typename T>
	void clog(T consoleOut)
	{
		std::cout << consoleOut << std::endl;
	}

	void cflush();
	bool is_file_empty(std::ifstream& file); // rename ?
}
