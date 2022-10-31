#ifndef USER_HPP
# define USER_HPP

# include "Command.hpp"

# include <string>
# include <iostream>

#include "Debug.hpp"


# define BUFFER_MAX 512

class User
{
	private:
		Command	command;
		std::string nickName;
		std::string	userName;
		// realname();
		// hostname();
		// int			socketNumber;
		// bool		isAccess;
		bool		isExit;
		int			fd;
	public:
		User();
		User(int fd, struct sockaddr_in addr);
		~User();
		void	receive();
		std::string getNickName();
		void	setNickName(std::string nickName);
		void	setRealName(std::string nickName);
		void	setHostName(std::string nickName);
		Command getCommand();
		bool	getIsExit();
		int		getFd();
};

#endif
