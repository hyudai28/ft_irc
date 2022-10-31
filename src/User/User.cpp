#include "User.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <cstdlib>

#include "User.hpp"

User::User()
{

}

User::User(int fd, struct sockaddr_in addr)
{
	(void)addr;
	this->fd = fd;
	this->isExit = false;
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
	// std::cout << "res: " << res << std::endl;
	if (res < 0)
	{
		std::exit (7);
	}
	else if (res == 0)
	{
		std::cout << "hello" << std::endl;
		std::cout << "disconnect: " << this->fd << std::endl;
		this->isExit = true;
		// exit (8);
	}
	printDebugMsgWhite("=MSG RECEIVED======");
	printDebugMsgWhite(buffer);
	printDebugMsgWhite("===================");
	buffer[BUFFER_MAX] = '\0';
	//サーバーにメンバーが入った時にもrecvが反応してparseをしてしまう。弾く方法を考える必要あり
	command.parse(buffer);
}

std::string User::getNickName()
{
	return (this->nickName);
}

void	User::setNickName(std::string str)
{
	this->nickName = str;
}


Command	User::getCommand()
{
	return (this->command);
}

bool	User::getIsExit()
{
	return (this->isExit);
}

int		User::getFd()
{
	return (this->fd);
}