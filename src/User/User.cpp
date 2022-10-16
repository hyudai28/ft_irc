#include "User.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

User::User()
{

}

User::User(int fd, struct sockaddr_in addr)
{
	this->fd = fd;
	this->is_exit = false;
}

User::~User()
{

}

void	User::receive()
{
	char	buffer[BUFFER_MAX + 1];
	int		res = 0;

	bzero(buffer, BUFFER_MAX);
	res = recv(fd, &buffer, BUFFER_MAX, 0);
	if (res < 0)
	{
		exit (7);
	}
	else if (res == 0)
	{
		std::cout << "disconnect: " << this->fd << std::endl;
		this->is_exit = true;
		// exit (8);
	}
	std::cout << buffer;
	buffer[BUFFER_MAX] = '\0';

	// command.parse(buffer);
}

bool	User::get_is_exit()
{
	return (this->is_exit);
}

int		User::get_fd()
{
	return (this->fd);
}
