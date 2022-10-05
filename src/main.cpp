#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "Server.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "./ft_irc port" << std::endl;
	}
	else
	{
		Server server;
		server.server_start(6667);
		while (1)
		{
			// poll();
		}
	}
}
