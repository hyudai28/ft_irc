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
		void	tryCommand(std::vector<User *>::iterator user);
		// bool	findCommand(std::string command);

		/* utils */
		void	waitEvent();
		void	addUser();
		void	receiveMessage();
		void	checkUserStatus();
		void	deleteUser(User &user);

		/* getter */
		std::vector<User *> getVectorUsers();
		int		getPort();
		int		getSocketFd();

		/* Error */
		void	socketHandle();
		void	setsockoptHandle();
		void	ioctlHandle();
		void	bindHandle();
		void	listenHandle();
		void	acceptHandle();
		void	pollHandle();

		/* commands */
		void	nick(std::vector<User *>::iterator user);
		void	capNick(std::vector<User *>::iterator user, std::string arg);

};

#endif /* SERVER_HPP */
