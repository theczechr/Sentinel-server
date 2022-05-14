#pragma once
#include <iostream>

namespace utils
{
	template<typename T>
	void clog(T consoleOut)
	{
		std::cout << consoleOut << std::endl;
	}

	void cflush();
}
