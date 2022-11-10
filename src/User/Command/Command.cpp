#include "Command.hpp"
#include <strings.h>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

Command::Command()
{

}

void	Command::parse(std::string buffer)
{
	std::string delim = " ";

	if (buffer.length() == 0)
	{
		std::cout << "no cmds";
		return ;
	}
	//splitする
	std::string elem = buffer.substr(0, buffer.find(delim));
	//cmds vector 初期化
	cmd_name.resize(0);
	//　スペースの一個めまでcmdに格納後、読み取った部分を消去
	cmd_name.push_back(elem);
	buffer = buffer.erase(0, buffer.find(delim) + delim.length());
	// prefixはとりあえず放置
	// とりあえずそれ以外もargsに入れていく
	//cmds vector 初期化
	args.resize(0);
	//
	while (buffer != elem)
	{
		elem = buffer.substr(0, buffer.find(delim));
		// std::cout << "on loop: " << elem << std::endl;
		args.push_back(elem);
		buffer = buffer.erase(0, buffer.find(delim) + delim.length());
	}
	// for (unsigned int i =0; i < cmd_name.size(); i++)
	// 	std::cout <<  "cmds elem is " << cmd_name.at(i) << endl;
	// for (unsigned int i =0; i < args.size(); i++)
	// 	std::cout <<  "args elem is " << args.at(i) << endl;
}

std::string	Command::get_prefix()
{
	return (this->prefix);
}

std::vector<std::string>	Command::get_cmd_name()
{
	return (this->cmd_name);
}

void	Command::set_cmds_vector(std::vector<std::string> arg_vector)
{
	this->cmd_name = arg_vector;
}

void	Command::set_arg_vector(std::vector<std::string> arg_vector)
{
	this->args = arg_vector;
}

std::vector<std::string>	Command::get_args()
{
	return (this->args);
}


// TODO もっといい初期化の仕方がありそう　要レビュー
void	Command::clearCommand()
{
	if (cmd_name.size() == 0)
		return ;
	cmd_name.resize(0);
}
