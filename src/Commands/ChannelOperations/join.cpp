#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"

bool	Server::isChannelExist(std::string newCh)
{
	for(std::vector<Channel>::size_type i = 0; i < channels.size(); i++)
	{
		// printDebugMsgYellow("checking channels!");
		if (channels.at(i).chName == newCh)
			return true;
	}
	return false;
}

void	Server::joinChannel(std::vector<User *>::iterator user)
{
	// printDebugMsgYellow("joinChannel called!");

	std::string arg_ch_name = (*user)->getCommand().get_args().at(0);

	//とりあえずここで引数出すか
	// for (int i = 0; i < (*user)->getCommand().get_args().size(); i++)
	// {
	// 	std::cout << i << ":" << (*user)->getCommand().get_args().at(i) << std::endl;
	// }
	//引数のチャンネル名が、serverのチャンネルリストのなかにあるか確認
	if (isChannelExist(arg_ch_name))
	{
	}
	else
	{
		Channel newCh;
		newCh.chName = (*user)->getCommand().get_args().at(0);
		channels.push_back(newCh);
	}
	// userがチャンネルの中にいるかを確認する　してなかったら入居
	//　該当のチャンネルを探す必要がある
	Channel *ch = getChannel(arg_ch_name);
	if (ch == NULL)
		return ;
	//
	if (ch->isUserJoined((*user)->getNickName()))
	{
		// printDebugMsgYellow("JOINED");
	}
	else
	{
		// printDebugMsgYellow("NON JOINED!");
		ch->chUsers.push_back((*user)->getNickName());
		printDebugMsgYellow("USER ADDED!");
		for (unsigned long i = 0; i < ch->chUsers.size(); i++)
			std::cout << ch->chUsers.at(i) << std::endl;
	}

	// exit(1);
}
	// std::string string = ":test JOIN #one\n";
	// if (-1 == send((*user)->getFd(), string.c_str(), string.length(), 0))
	// 	std::cout << "it is wrong!!" << std::endl;
