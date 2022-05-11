#include <iostream>
#include "stdlib.h"
#include "console.h"
void log(std::string consoleOut) // printing out text
{
	std::cout << consoleOut << "\n";
}
void flush() // clearing out the console
{
	std::system("CLS"); 
}
