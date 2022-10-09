#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>

class User
{
	private:
		std::string userName;
		int			socketNumber;
		bool		isAccess;
		int			fd;
	public:
		User();
		User(int fd);
		~User();
		void	receive();
};

#endif
