#include "Server.hpp"

void	Server::tryCommand(Command cmd, std::vector<User *>::iterator user)
{
	if(cmd.cmd_name == "CAP")
	{
		// 対応外　スルースル
	}
	if(cmd.cmd_name == "PASS")
	{
		std::string string = "127.0.0.1 PASS Correct password\n";
		if (-1 == send((*user)->getFd(), string.c_str(), string.length(), 0))
			std::cout << "it is wrong!!" << std::endl;
	}
	if(cmd.cmd_name == "JOIN")
	{
		joinChannel(cmd, user);
	}
	if(cmd.cmd_name == "PRIVMSG")
	{
		privateMessages(cmd, user);
	}
	if(cmd.cmd_name == "NICK")
	{
		nick(cmd, user);
	}
	if(cmd.cmd_name == "USER")
	{
		user_cmd(cmd, user);

	}
	// if(cmd.cmd_name == "MODE")
	// {
	// 	std::cout << "MODE called" << std::endl;
	// 	return ;
	// }
	// if(cmd.cmd_name == "WHOIS")
	// {
	// 	std::cout << "WHOIS called" << std::endl;
	// 	return ;
	// }
}

// コマンドを実行しようとする
void	Server::tryCommands(std::vector<User *>::iterator user)
{
	// printDebugMsgYellow("tryCommandS called---");
	for (unsigned int i = 0; i < (*user)->commands.size(); i++)
	{
		tryCommand((*user)->commands.at(i), user);
		// printDebugMsgRed("In tryCommands");
		// std::cout <<  "cmd is " << (*user)->commands.at(i).cmd_name << std::endl;
		// for (unsigned int j = 0; j < (*user)->commands.at(i).args.size(); j++)
		// std::cout <<  "args elem is " << (*user)->commands.at(i).args.at(j) << std::endl;
	}
	return ;
}