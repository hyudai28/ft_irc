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
	this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketFd == -1)
	{
		std::exit(1);
	}

	//ソケットを再利用可能にする？アドレスにバインドするとかなんとか
	int optVal;
	int res;
	res = setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&optVal, sizeof(optVal));
	if (res == 1)
	{
		close(this->socketFd);
		std::exit(2);
	}

	//ソケットをノンブロッキングにする
	res = ioctl(this->socketFd, FIONBIO, (char *)&optVal);
	if (res == -1)
	{
		close(this->socketFd);
		std::exit(3);
	}

	//ソケットにバインドする
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	res = bind(this->socketFd, (struct sockaddr *)&sin, sizeof(sin));
	if (res == -1)
	{
		close(this->socketFd);
		std::exit(4);
	}

	res = listen(this->socketFd, port);
	if (res == -1)
	{
		close(this->socketFd);
		std::exit(5);
	}

	this->pollFds.push_back(pollfd());
	this->pollFds.back().fd = this->socketFd;
	this->pollFds.back().events = POLLIN;
}

void	Server::deleteUser(User &user)
{
	std::vector<User *> broadcast_users = std::vector<User *>();
	broadcast_users.push_back(&user);

	for (std::vector<pollfd>::iterator it_pfd = this->pollFds.begin(); it_pfd != this->pollFds.end(); ++it_pfd)
		if ((*it_pfd).fd == user.getFd())
		{
			this->pollFds.erase(it_pfd);
			break;
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
	{
		std::exit(6);
	}
	if (res == 0)
	{
		std::exit(7);
	}
}

void	Server::addUser()
{
	int	acceptFd;
	struct sockaddr_in addr;

	acceptFd = accept(socketFd, NULL, NULL);
	if (acceptFd < 0)
	{
		if (errno != EWOULDBLOCK)
		{
			this->endServer = true;
		}
		std::exit(-1);
	}

	if (DEBUG)
		std::cout << "new connection -> [" << acceptFd << "]" << std::endl;

	this->users[acceptFd] = new User(acceptFd, addr);
	this->pollFds.push_back(pollfd());
	this->pollFds.back().fd = acceptFd;
	this->pollFds.back().events = POLLIN;
}

void	Server::checkUserStatus()
{
	std::vector<User *> users = getVectorUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if ((*it)->getIsExit() == true)
		{
			close((*it)->getFd());
			deleteUser(*(*it));
		}
	}
}

void	Server::loop()
{
	// int maxFd = this->socketFd;

	waitEvent(); //イベントが来るまで待機
	if (pollFds[0].revents == POLLIN) //socketのfdにイベントが発生した時にユーザー追加
	{
		addUser();
	}
	else //それ以外のfdから発生するイベントは受信
	{
		for (std::vector<pollfd>::iterator it = pollFds.begin(); it != pollFds.end(); ++it) {
			if ((*it).revents == POLLIN) {
				this->users[(*it).fd]->receive();
			}
		}
	}
	//ユーザーが退出したら削除する
	checkUserStatus();
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
