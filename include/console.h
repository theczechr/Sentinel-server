#pragma once
#include <iostream>

template<typename T>
void clog(T consoleOut) { // Tady to nejde definovat v .cpp skrz ten template.. snazil jsem se to nejak fixnout, ale bohuzel neuspesne. Muzem se o tom pobavit
	std::cout << consoleOut << std::endl;
}
void flush(); // clearing out the console | console log
