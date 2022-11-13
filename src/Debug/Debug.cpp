#include "Debug.hpp"

void	printDebugMsgRed(std::string msg)
{
	std::cout << "\033[1;31m" << msg << "\033[0m\n" << std::endl;
}

void	printDebugMsgYellow(std::string msg)
{
	std::cout << "\033[1;33m" << msg << "\033[0m\n" << std::endl;
}

void	printDebugMsgWhite(std::string msg)
{
	std::cout << msg << std::endl;
}