#include "Server.hpp"

// コマンドを実行しようとする
void	Server::tryCommand(std::vector<User *>::iterator user)
{
	// printDebugMsgYellow("tryCommand called---");
	// printDebugMsgYellow((*user)->getCommand().get_cmd_name().at(0));

	// CAP これはIRSSIが使ってる拡張で、対応する必要はないから場当たり的な処理してる
	if((*user)->getCommand().get_cmd_name().at(0) == "CAP")
	{
		// cap nick　通常のnickに追加でargを渡している
		std::string secondArg;
		if ((*user)->getCommand().get_args().size() > 1)
			secondArg = (*user)->getCommand().get_args().at(1);
		else
		{
			printDebugMsgRed("Fail arg");
			return ;
		}
		std::string elem = secondArg.substr(0, secondArg.find("\n"));
		capNick(user, elem);
		//　args.at(2) 以降をuser_argに追加し続ける
		std::vector<std::string> user_arg;
		capUser(user, (*user)->getCommand().get_args().at(2));

		std::string string = "001 * Welcome to the Internet res:lay Network kamori!kamori@127.0.0.1\n";
		if (-1 == send((*user)->getFd(), string.c_str(), string.length(), 0))
			printDebugMsgYellow("send failed!");
	}
	if((*user)->getCommand().get_cmd_name().at(0) == "PASS")
	{
		std::string string = "127.0.0.1 PASS Correct password\n";
		if (-1 == send((*user)->getFd(), string.c_str(), string.length(), 0))
			std::cout << "it is wrong!!" << std::endl;
	}
	if((*user)->getCommand().get_cmd_name().at(0) == "JOIN")
	{
		joinChannel(user);
		printDebugMsgYellow("join done");
	}
	if((*user)->getCommand().get_cmd_name().at(0) == "PRIVMSG")
	{
		privateMessages(user);
	}
	// if((*user)->getCommand().get_cmd_name().at(0) == "NICK")
	// {
	// 	return ;
	// }
	// if((*user)->getCommand().get_cmd_name().at(0) == "USER")
	// {
	// 	return ;
	// }
	// if((*user)->getCommand().get_cmd_name().at(0) == "MODE")
	// {
	// 	std::cout << "MODE called" << std::endl;
	// 	return ;
	// }
	// if((*user)->getCommand().get_cmd_name().at(0) == "WHOIS")
	// {
	// 	std::cout << "WHOIS called" << std::endl;
	// 	return ;
	// }
	return ;
}