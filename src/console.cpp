#include <iostream>
#include "stdlib.h"
#include "console.h"
template<typename T>
void log(T consoleOut) // printing out texts
{
	std::cout << consoleOut << "\n";
}
void flush() // clearing out the console
{
	std::system("CLS"); 
}