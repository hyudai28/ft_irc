#include "Server.hpp"
#include "User.hpp"

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
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

void	Server::start(int port)
{
	//クライアントと通信するソケットの作成
	this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socket_fd == -1)
	{
		exit (1);
	}

	//ソケットを再利用可能にする？アドレスにバインドするとかなんとか
	int	opt_val;
	int	res;
	res = setsockopt(this->socket_fd, SOL_SOCKET,  SO_REUSEADDR, (char *)&opt_val, sizeof(opt_val));
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
	struct sockaddr_in	sin;
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
}

#define FALSE 0
#define TRUE 1

void	Server::loop()
{
	int	close_conn;
	int	res;
	int	accept_fd;
	int	readable, end_server = FALSE;
	struct sockaddr_in	addr;

	fd_set              master_set, working_set;
	int	max_fd = this->socket_fd;
	FD_ZERO(&master_set);
	FD_SET(socket_fd, &master_set);
	struct timeval	timeout;
	timeout.tv_sec  = 3 * 60;
	timeout.tv_usec = 0;
	do
	{
		memcpy(&working_set, &master_set, sizeof(master_set));
		res = select(max_fd + 1, &working_set, NULL, NULL, &timeout);
		if (res == -1)
		{
			exit (6);
		}
		if (res == 0)
		{
			exit (7);
		}
		readable = res;
		for (int i = 0; i <= max_fd  &&  readable > 0; i++)
		{
			if (FD_ISSET(i, &working_set))
			{
				readable -= 1;
				if (i == socket_fd)
				{
					do
					{
						accept_fd = accept(socket_fd, NULL, NULL);
						if (accept_fd < 0)
						{
							if (errno != EWOULDBLOCK)
							{
								end_server = TRUE;
							}
							break;
						}
						std::cout << "new connection -> [" << i << "]" << std::endl;
						FD_SET(accept_fd, &master_set);
						if (accept_fd > max_fd)
							max_fd = accept_fd;
					} while (accept_fd != -1);
				}
				else
				{
					close_conn = FALSE;
					do
					{
						char	buffer[512];
						res = recv(i, buffer, sizeof(buffer), 0);
						if (res < 0)
						{
							if (errno != EWOULDBLOCK)
							{
								close_conn = TRUE;
							}
							break;
						}
						std::cout << buffer;
						if (res == 0)
						{
							close_conn = TRUE;
							break;
						}

						res = send(i, buffer, res, 0);
						if (res < 0)
						{
							close_conn = TRUE;
							break;
						}

					} while (TRUE);

					if (close_conn)
					{
						close(i);
						FD_CLR(i, &master_set);
						if (i == max_fd)
						{
							while (FD_ISSET(max_fd, &master_set) == FALSE)
								max_fd -= 1;
						}
					}
				}
			}
		}

	} while (end_server == FALSE);

	/*************************************************************/
	/* Clean up all of the sockets that are open                 */
	/*************************************************************/
	for (int i=0; i <= max_fd; ++i)
	{
		if (FD_ISSET(i, &master_set))
			close(i);
	}
}


int		Server::get_port()
{
	return (this->port);
}

int		Server::get_socket_fd()
{
	return (this->socket_fd);
}
