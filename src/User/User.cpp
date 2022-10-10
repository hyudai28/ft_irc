#include "User.hpp"

#include <sys/socket.h>

User::User()
{

}

User::User(int fd)
{
	this->fd = fd;
}

User::~User()
{

}

void	User::receive()
{
	int	r;
	int	i;
	char buf[513];

	r = recv(fd, buf, 512, 0);
	std::cout << buf << std::endl;
	// if (r <= 0)
	// {
	// 	close(cs);
	// 	clean_fd(&e->fds[cs]);
	// 	printf("client #%d gone away\n", cs);
	// }
	// else
}
