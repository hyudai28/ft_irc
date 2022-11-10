#include "Command.hpp"
#include <strings.h>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

Command::Command()
{

}

std::string	Command::get_prefix()
{
	return (this->prefix);
}

void	Command::set_arg_vector(std::vector<std::string> arg_vector)
{
	this->args = arg_vector;
}

std::vector<std::string>	Command::get_args()
{
	return (this->args);
}
