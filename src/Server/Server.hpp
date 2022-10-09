#ifndef SERVER_HPP
# define SERVER_HPP

# include "User.hpp"

# include <vector>
# include <map>
# include <poll.h>

class Server
{
	private:
		int	port;
		int	socket_fd;
		std::vector<pollfd>	pollfds;
		std::map<int, User *>	users;
	public:
		Server();
		~Server();

		void	start(int port);
		void	loop();

		int		get_port();
		int		get_socket_fd();
};

#endif /* SERVER_HPP */
