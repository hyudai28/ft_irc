#include "Command.hpp"
#include <strings.h>
#include <cstdlib>
#include <iostream>

Command::Command()
{

}

#include <vector>
using namespace std;

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
	commands.resize(0);
	//　スペースの一個めまでcmdに格納後、読み取った部分を消去
	commands.push_back(elem);
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
	// for (unsigned int i =0; i < commands.size(); i++)
	// 	std::cout <<  "cmds elem is " << commands.at(i) << endl;
	// for (unsigned int i =0; i < args.size(); i++)
	// 	std::cout <<  "args elem is " << args.at(i) << endl;
}

std::string	Command::get_prefix()
{
	return (this->prefix);
}

std::vector<std::string>	Command::get_commands()
{
	return (this->commands);
}

void	Command::set_cmds_vector(std::vector<std::string> arg_vector)
{
	this->commands = arg_vector;
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
	if (commands.size() == 0)
		return ;
	commands.resize(0);
}

// void    Command::parse(std::string buffer)
// {
//     // std::cout << buffer;
//     std::string delim = " ";

//     if (buffer.length() == 0)
//     {
//         std::cout << "no cmds";
//         return ;
//     }
//     //splitする
//     std::string elem = buffer.substr(0, buffer.find(delim));
// 	std::cout << "elem: " << elem << std::endl;
//     //cmds vector 初期化
//     commands.resize(0);
//     //　スペースの一個めまでcmdに格納後、読み取った部分を消去
//     commands.push_back(elem);
//     buffer = buffer.erase(0, buffer.find(delim) + delim.length());
//     // prefixはとりあえず放置
//     // とりあえずそれ以外もargsに入れていく
//     //cmds vector 初期化
//     args.resize(0);
//     //bufferは51行目のeraseでスペースまでを削除して、最終的に両方消えるまで
//     while (buffer != elem)
//     {
//         elem = buffer.substr(0, buffer.find(delim));
//         std::cout << "on loop: " << elem << std::endl;
//         args.push_back(elem);
//         buffer = buffer.erase(0, buffer.find(delim) + delim.length());
//     }
//     for (unsigned int i =0; i < commands.size(); i++)
//         std::cout <<  "cmds elem is " << commands.at(i) << std::endl;
//     for (unsigned int i =0; i < args.size(); i++)
//         std::cout <<  "args elem is " << args.at(i) << std::endl;
// }