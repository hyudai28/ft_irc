#include "Server.hpp"

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
	// TODO やるべきこと、checkUserStatusの中身が入っているならそこで出すこと
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
		// std::cout << "poll time out" << std::endl;
}

void	Server::checkUserStatus()
{
	std::vector<User *> users = getVectorUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if ((*it)->getCommand().get_commands().size() == 1)
		{
			tryCommand(it);
		}
		if ((*it)->getIsExit() == true)
		{
			close((*it)->getFd());
			deleteUser(*(*it));
		}
	}
}


// コマンドを実行しようとする
void	Server::tryCommand(std::vector<User *>::iterator user)
{
	// printDebugMsgYellow((*user)->getCommand().get_commands().at(0));

	//TODO 渡されたコマンドを実行しようとする
	// CAP これはIRSSIが使ってる拡張機能で、対応する必要はないから
	// 場当たり的な処理をしている
	if((*user)->getCommand().get_commands().at(0) == "CAP")
	{
		// cap nick　通常のnickに追加でargを渡している
		capNick(user, (*user)->getCommand().get_args().at(2));

		// cap user
		//　args.at(2) 以降をuser_argに追加し続ける
		std::vector<std::string> user_arg;
		capUser(user, (*user)->getCommand().get_args().at(2));

		std::string string = "001 * Welcome to the Internet res:lay Network kamori!kamori@127.0.0.1\n";
		if (-1 == send((*user)->getFd(), string.c_str(), string.length(), 0))
			printDebugMsgYellow("send failed!");
		return ;
	}
	// passwordがあってるかを確認する
	// 今はこういう形だけどそのうち
	// if (command == pass)
	// {
	// 	pass(user);
	// }
	// という形式にする　以下全てのコマンドも同様
	if((*user)->getCommand().get_commands().at(0) == "PASS")
	{
		std::string string = "127.0.0.1 PASS Correct password\n";
		if (-1 == send((*user)->getFd(), string.c_str(), string.length(), 0))
			std::cout << "it is wrong!!" << std::endl;
		return ;
	}
	if((*user)->getCommand().get_commands().at(0) == "JOIN")
	{
		join(user);
		printDebugMsgYellow("join done");
		return ;
	}
	if((*user)->getCommand().get_commands().at(0) == "PRIVMSG")
	{
		privateMessages(user);
		return ;
	}
	// if((*user)->getCommand().get_commands().at(0) == "NICK")
	// {
	// 	return ;
	// }
	// if((*user)->getCommand().get_commands().at(0) == "USER")
	// {
	// 	return ;
	// }
	// if((*user)->getCommand().get_commands().at(0) == "MODE")
	// {
	// 	std::cout << "MODE called" << std::endl;
	// 	return ;
	// }
	// if((*user)->getCommand().get_commands().at(0) == "WHOIS")
	// {
	// 	std::cout << "WHOIS called" << std::endl;
	// 	return ;
	// }

	// コマンドを掃除する
	(*user)->getCommand().get_commands().resize(0);
}

// bool	Server::findCommand(std::string command)
// {
// }

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
