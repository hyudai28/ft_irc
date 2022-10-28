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
#include <vector>

#include <cerrno>

#include "Command.hpp"


Server::Server()
{
	std::cout << "server start" << std::endl;
}

Server::~Server()
{
	users.erase(users.begin(), users.end());
	std::cout << "server stop" << std::endl;
}

void	Server::start(int port)
{
	//クライアントと通信するソケットの作成
	this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketFd == -1)
		socketHandle();

	//ソケットを再利用可能にする？アドレスにバインドするとかなんとか
	int optVal;
	int res;
	res = setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&optVal, sizeof(optVal));
	if (res == 1)
		setsockoptHandle();

	//ソケットをノンブロッキングにする
	res = ioctl(this->socketFd, FIONBIO, (char *)&optVal);
	if (res == -1)
		ioctlHandle();

	//ソケットにバインドする
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	res = bind(this->socketFd, (struct sockaddr *)&sin, sizeof(sin));
	if (res == -1)
		bindHandle();

	res = listen(this->socketFd, port);
	if (res == -1)
		listenHandle();

	this->pollFds.push_back(pollfd());
	this->pollFds.back().fd = this->socketFd;
	this->pollFds.back().events = POLLIN;
}

void	Server::loop()
{
	// int maxFd = this->socketFd;

	waitEvent(); //イベントが来るまで待機
	if (pollFds[0].revents == POLLIN) //socketのfdにイベントが発生した時にユーザー追加
	{
		addUser();
		if (this->endServer == true)
			acceptHandle();
	}
	else //それ以外のfdから発生するイベントは受信
	{
		receiveMessage();
	}
	//ユーザーが退出したら削除する
	checkUserStatus();
}

void	Server::addUser()
{
	int	acceptFd;
	struct sockaddr_in addr;

	acceptFd = accept(socketFd, NULL, NULL);
	if (acceptFd == -1 && errno != EWOULDBLOCK)
	{
		this->endServer = true;
		return ;
	}
	if (DEBUG)
		std::cout << "new connection -> [" << acceptFd << "]" << std::endl;
	this->users[acceptFd] = new User(acceptFd, addr);
	this->pollFds.push_back(pollfd());
	this->pollFds.back().fd = acceptFd;
	this->pollFds.back().events = POLLIN;
}

void	Server::deleteUser(User &user)
{
	std::vector<User *> broadcast_users = std::vector<User *>();
	broadcast_users.push_back(&user);

	for (std::vector<pollfd>::iterator ite = this->pollFds.begin(); ite != this->pollFds.end(); ++ite)
	{
		if ((*ite).fd == user.getFd())
		{
			this->pollFds.erase(ite);
			break;
		}
	}
	users.erase(user.getFd());
	delete &user;
}

void	Server::waitEvent()
{
	int	timeout = (3 * 60 * 1000);
	int	res;

	res = poll(&this->pollFds[0], this->pollFds.size(), timeout);
	if (res == -1)
		pollHandle();
	// if (res == 0) //timeout
	// 	std::cout << "poll time out" << std::endl;
}

void	Server::checkUserStatus()
{
	std::vector<User *> users = getVectorUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if ((*it)->getCommand().get_commands().size() == 1)
		{
			std::cout << "we got" << std::endl;
			std::cout << (*it)->getCommand().get_commands().at(0) << std::endl;
		}
		// if ((*it)->getIsExit() == true)
		// {
		// 	close((*it)->getFd());
		// 	deleteUser(*(*it));
		// }
	}
}

void	Server::receiveMessage()
{
	for (std::vector<pollfd>::iterator it = pollFds.begin(); it != pollFds.end(); ++it)
	{
		if ((*it).revents == POLLIN)
		{
			this->users[(*it).fd]->receive();
		}
	}
}

std::vector<User *> Server::getVectorUsers()
{
	std::vector<User *> users = std::vector<User *>();
	for (std::map<int, User *>::iterator it = this->users.begin(); it != this->users.end(); ++it)
	{
		users.push_back(it->second);
	}
	return (users);
}

int	Server::getPort()
{
	return (this->port);
}

int	Server::getSocketFd()
{
	return (this->socketFd);
}
