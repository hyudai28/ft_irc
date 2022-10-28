#ifndef USER_HPP
# define USER_HPP

# include "Command.hpp"

# include <string>
# include <iostream>

# define BUFFER_MAX 512

class User
{
	private:
		Command	command;
		std::string	userName;
		// int			socketNumber;
		// bool		isAccess;
		bool		isExit;
		int			fd;
	public:
		User();
		User(int fd, struct sockaddr_in addr);
		~User();
		void	receive();
		Command getCommand();
		bool	getIsExit();
		int		getFd();
};

#endif
