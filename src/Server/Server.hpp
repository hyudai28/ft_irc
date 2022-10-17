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
		std::vector<struct pollfd>	poll_fds;
		std::map<int, User *>	users;
	public:
		Server();
		~Server();

		void	start(int port);
		void	loop();
		void	delete_user(User &user);


		std::vector<User *> get_vector_users();
		int		get_port();
		int		get_socket_fd();
};

#endif /* SERVER_HPP */
