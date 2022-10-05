#include "Server.hpp"

#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>

Server::Server()
{
	std::cout << "server start" << std::endl;
}

Server::~Server()
{
	std::cout << "server stop" << std::endl;
}

void	Server::server_start(int port)
{
	this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socket_fd == 0)
	{
		exit (1); //error
	}
	// int data;
	// setsockopt(\this->socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &data, sizeof(data);
	// fcntl(fd, F_SETFL, O_NONBLOCK);

	struct sockaddr_in	sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	if (bind(this->socket_fd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		exit (1); //error
	}
	if (listen(this->socket_fd, sin.sin_port) == 1)
	{
		exit (1); //error
	}
	// pollfd()?;
}

int		Server::get_port()
{
	return (this->port);
}
