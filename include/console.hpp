#pragma once
#include <iostream>

template<typename T>
void clog(T consoleOut)
{
	std::cout << consoleOut << std::endl;
}
void flush(); // clearing out the console | console log
