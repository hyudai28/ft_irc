// #include <iostream>
// #include <stdlib.h>
// #include <netdb.h>
// #include <sys/socket.h>
// #include <sys/types.h>

#include "Server.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>

#define SERVER_PORT  6667

#define TRUE             1
#define FALSE            0

// int	main(int argc, char *argv[])
// {
	// int r;
	// int fd;
	// fd_set fd_read, fd_write;

	// if (argc != 2)
	// {
	// 	std::cout << "./ft_irc port" << std::endl;
	// }
	// else
	// {
	// 	Server server;
	// 	server.server_start(6667);
	// 	server.loop();
	// 	// while (1)
	// 	// {
	// 	// 	server.loop();
	// 	// }
	// }

int	main (int argc, char *argv[])
{
    Server server;

    server.start(6667);
	server.loop();
}
