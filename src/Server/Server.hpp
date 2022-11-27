#ifndef SERVER_HPP
# define SERVER_HPP

# include "User.hpp"

# include <vector>
# include <map>
# include <poll.h>
# include "Channel.hpp"
#include "Server.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include <cerrno>

#include <iostream>
#include <vector>
#include <algorithm>


#include "Command.hpp"

#include "Debug.hpp"

#include "sender.hpp"

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
		std::vector<class Channel> channels;

		Server();
		~Server();

		void	start(int port);
		void	loop();
		void	tryCommand(Command cmd, std::vector<User *>::iterator user);
		void	tryCommands(std::vector<User *>::iterator user);
		// bool	findCommand(std::string command);

		/* utils */
		void	waitEvent();
		
		void	addUser();
		void	receiveMessage();
		void	checkUserStatus();
		void	deleteUser(User &user);
		Channel* getChannel(std::string string);
		User* getUserByName(std::string name);


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
		// Channel　Operations
		bool	isChannelExist(std::string newCh);
		void	joinChannel(Command cmd, std::vector<User *>::iterator user);

		// connection registration
		void	nick(Command cmd, std::vector<User *>::iterator user);
		void	user_cmd(Command cmd, std::vector<User *>::iterator user);

		//  sending messages
		void	privateMessages(Command cmd, std::vector<User *>::iterator user);
};

#endif /* SERVER_HPP */
