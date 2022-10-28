#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>
# include <iostream>

class Command
{
	private:
		std::string	prefix;
		std::vector<std::string>	commands;
		std::vector<std::string>	args;

	public:
		Command();

		void		parse(std::string buffer);

		std::string					get_prefix();
		std::vector<std::string>	get_commands();
		std::vector<std::string>	get_args();
};

#endif
