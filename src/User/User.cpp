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
	printDebugMsgWhite("from : " + getNickName());
	printDebugMsgWhite("===================");
	buffer[BUFFER_MAX] = '\0';
	parse(buffer);
}

void	User::parse(std::string buffer)
{
	//TODO bufferの中の要素を
	//改行ごとに要素を入れていく
	// printDebugMsgRed("in user parse, buf is \n" + buffer);

	// check buffer
	if (buffer.length() == 0)
	{
		std::cout << "no cmds";
		return ;
	}

	//TODO　改行区切りでのbufferにする
	//　改行区切りのbufferをcmdに落とし込んでいく
	std::vector<std::string> bufs_by_CR;
	std::string delim;

	delim = "\r\n";
	std::string elem;
	while(1)
	{
		elem = buffer.substr(0, buffer.find(delim));
		if (elem.size() == 0)
			break;
		buffer = buffer.erase(0, buffer.find(delim) + delim.length());
		bufs_by_CR.push_back(elem);
	}

	for (unsigned int i = 0; i < bufs_by_CR.size(); i++)
	{
		printDebugMsgRed(bufs_by_CR.at(i));
	}

	Command cmd;
	delim = " ";
	for (unsigned long i = 0; i < bufs_by_CR.size(); i++)
	{
		for (unsigned long j = 0; ; j++)
		{
			elem = bufs_by_CR.at(i).substr(0, bufs_by_CR.at(i).find(delim));
			bufs_by_CR.at(i) = bufs_by_CR.at(i).erase(0, bufs_by_CR.at(i).find(delim) + delim.length());
			if (j == 0)
			{
				cmd.cmd_name = elem;
			}
			else
			{
				cmd.args.push_back(elem);
			}
			if (elem == bufs_by_CR.at(i))
				break;
		}
		commands.push_back(cmd);
		cmd.args.clear();
	}
	// debug commands
	// for (unsigned int i = 0; i < commands.size(); i++)
	// {
	// 	std::cout <<  "cmd is " << commands.at(i).cmd_name << std::endl;
	// 	for (unsigned int j = 0; j < commands.at(i).args.size(); j++)
	// 		std::cout <<  "args elem is " << commands.at(i).args.at(j) << std::endl;
	// }
}

// TODO もっといい初期化の仕方がありそう　要レビュー
void	User::clearCommands()
{
	commands.resize(0);
}

std::string User::getNickName()
{
	return (this->nickName);
}

void	User::setNickName(std::string str)
{
	this->nickName = str;
}

bool	User::getIsExit()
{
	return (this->isExit);
}

int		User::getFd()
{
	return (this->fd);
}

// void	Command::parse(std::string buffer)
// {
// 	std::string delim = " ";

// 	if (buffer.length() == 0)
// 	{
// 		std::cout << "no cmds";
// 		return ;
// 	}
// 	//splitする
// 	std::string elem = buffer.substr(0, buffer.find(delim));
// 	//cmd_name 初期化
// 	cmd_name = "";
// 	//　スペースの一個めまでcmdに格納後、読み取った部分を消去
// 	cmd_name = elem;
// 	buffer = buffer.erase(0, buffer.find(delim) + delim.length());
// 	// prefixはとりあえず放置
// 	// とりあえずそれ以外もargsに入れていく
// 	//cmds vector 初期化
// 	args.resize(0);
// 	//
// 	while (buffer != elem)
// 	{
// 		elem = buffer.substr(0, buffer.find(delim));
// 		// std::cout << "on loop: " << elem << std::endl;
// 		args.push_back(elem);
// 		buffer = buffer.erase(0, buffer.find(delim) + delim.length());
// 	}
// 	// 	std::cout <<  "cmd is " << cmd_name << endl;
// 	// for (unsigned int i =0; i < args.size(); i++)
// 	// 	std::cout <<  "args elem is " << args.at(i) << endl;
// }