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
	std::string string = "127.0.0.1 PASS Correct password\n";
	if (-1 == send(fd, string.c_str(), string.length(), 0))
		std::cout << "it is wrong!!" << std::endl;
	string = "001 * Welcome to the Internet Relay Network kamori!kamori@127.0.0.1\n";
	if (-1 == send(fd, string.c_str(), string.length(), 0))
		std::cout << "it is wrong!!" << std::endl;
	// string = ":kirari JOIN #one\n";
	// if (-1 == send(fd, string.c_str(), string.length(), 0))
	// 	std::cout << "it is wrong!!" << std::endl;
	string = ":kirari PRIVMSG #one :hello~~\n";
	if (-1 == send(fd, string.c_str(), string.length(), 0))
		std::cout << "it is wrong!!" << std::endl;
	std::cout << "res: " << res << std::endl;
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
	std::cout << "===================" << std::endl;
	std::cout << buffer;
	std::cout << "===================" << std::endl;
	buffer[BUFFER_MAX] = '\0';
	//サーバーにメンバーが入った時にもrecvが反応してparseをしてしまう。弾く方法を考える必要あり
	command.parse(buffer);
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