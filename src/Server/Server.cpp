#include "Server.hpp"
#include "User.hpp"

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <unistd.h>
#include <netinet/in.h>

Server::Server()
{
	std::cout << "server start" << std::endl;
}

Server::~Server()
{
	std::cout << "server stop" << std::endl;
}

void Server::start(int port)
{
	//クライアントと通信するソケットの作成
	this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socket_fd == -1)
	{
		exit(1);
	}

	//ソケットを再利用可能にする？アドレスにバインドするとかなんとか
	int opt_val;
	int res;
	res = setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt_val, sizeof(opt_val));
	if (res == 1)
	{
		close(this->socket_fd);
		exit(2);
	}

	//ソケットをノンブロッキングにする
	res = ioctl(this->socket_fd, FIONBIO, (char *)&opt_val);
	if (res == -1)
	{
		close(this->socket_fd);
		exit(3);
	}

	//ソケットにバインドする
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	res = bind(this->socket_fd, (struct sockaddr *)&sin, sizeof(sin));
	if (res == -1)
	{
		close(this->socket_fd);
		exit(4);
	}

	//ﾍｰｲ ﾘｯｽﾝ
	res = listen(this->socket_fd, port);
	if (res == -1)
	{
		close(this->socket_fd);
		exit(5);
	}

	this->poll_fds.push_back(pollfd());
	this->poll_fds.back().fd = this->socket_fd;
	this->poll_fds.back().events = POLLIN;
}

#define FALSE 0
#define TRUE 1

void Server::loop()
{
	int res;
	int accept_fd;
	int readable, end_server = FALSE;
	struct sockaddr_in addr;

	fd_set master_set, working_set;
	int max_fd = this->socket_fd;
	int timeout = (3 * 60 * 1000);

	// std::cout << "wait poll()" << std::endl;
	res = poll(&this->poll_fds[0], this->poll_fds.size(), timeout);
	if (res == -1)
	{
		exit(6);
	}
	if (res == 0)
	{
		exit(7);
	}
	if (this->poll_fds[0].revents == POLLIN)
	{
		accept_fd = accept(socket_fd, NULL, NULL);
		if (accept_fd < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				end_server = TRUE;
			}
			exit(-1);
		}
		// std::cout << "new connection -> [" << accept_fd << "]" << std::endl;
		this->users[accept_fd] = new User(accept_fd, addr);
		this->poll_fds.push_back(pollfd());
		this->poll_fds.back().fd = accept_fd;
		this->poll_fds.back().events = POLLIN;

		if (accept_fd > max_fd)
			max_fd = accept_fd;
	}
	else
	{
		for (std::vector<pollfd>::iterator it = this->poll_fds.begin(); it != this->poll_fds.end(); ++it)
		{
			if ((*it).revents == POLLIN)
			{
				this->users[accept_fd]->receive();
			}
		}
	}

	/*************************************************************/
	/* Clean up all of the sockets that are open                 */
	/*************************************************************/
	for (int i = 0; i <= max_fd; ++i)
	{
		if (FD_ISSET(i, &master_set))
			close(i);
	}
}

int Server::get_port()
{
	return (this->port);
}

int Server::get_socket_fd()
{
	return (this->socket_fd);
}
