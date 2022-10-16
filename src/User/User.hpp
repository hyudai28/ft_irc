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
		std::string	user_name;
		int			socket_number;
		bool		is_access;
		bool		is_exit;
		int			fd;
	public:
		User();
		User(int fd, struct sockaddr_in addr);
		~User();
		void	receive();

		bool	get_is_exit();
		int		get_fd();
};

#endif
