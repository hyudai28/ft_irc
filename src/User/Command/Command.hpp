#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>
# include <iostream>

#include "Debug.hpp"


class Command
{
	private:
		std::string	prefix;
	public:
		// std::vector<std::string>	cmd_name;
		std::string	cmd_name;
		std::vector<std::string>	args;

		Command();

		std::string					get_prefix();
		std::vector<std::string>	get_args();
		// for cap ls
		void						set_arg_vector(std::vector<std::string> arg_vector);

};

#endif
