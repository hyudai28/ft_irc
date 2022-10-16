#include "Command.hpp"

Command::Command()
{

}

std::string	Command::get_prefix()
{
	return (this->prefix);
}

std::vector<std::string>	Command::get_commands()
{
	return (this->commands);
}

std::vector<std::string>	Command::get_args()
{
	return (this->args);
}
