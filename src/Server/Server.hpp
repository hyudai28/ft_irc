#ifndef SERVER_HPP
# define SERVER_HPP

# include "User.hpp"

# include <vector>
# include <map>
# include <poll.h>

# define DEBUG 1

class Server
{
	private:
		bool	endServer;

		int	port;
		int	socketFd;
		std::vector<struct pollfd>	pollFds;
		std::map<int, User *>	users;
	public:
		Server();
		~Server();

		void	start(int port);

		void	loop();
		void	waitEvent();
		void	addUser();
		void	checkUserStatus();

		void	deleteUser(User &user);


		std::vector<User *> getVectorUsers();
		int		getPort();
		int		getSocketFd();
};

#endif /* SERVER_HPP */
