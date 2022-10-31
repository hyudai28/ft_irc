#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"

bool	Server::is_channel_exist(std::string newCh)
{
	for(int i = 0; i < channels.size(); i++)
	{
		std::cout << "checking channels!" << std::endl;
		if (channels.at(i).chName == newCh)
			return true;
	}
	return false;
}

void	Server::join(std::vector<User *>::iterator user)
{
	std::cout << "join called!" << std::endl;
	std::string arg_ch_name = (*user)->getCommand().get_args().at(0);

	//とりあえずここで引数出すか
	for (int i = 0; i < (*user)->getCommand().get_args().size(); i++)
	{
		std::cout << i << ":" << (*user)->getCommand().get_args().at(i) << std::endl;
	}
	//引数のチャンネル名が、serverのチャンネルリストのなかにあるか確認
	if (is_channel_exist(arg_ch_name))
	{
		std::cout << "EXIST" << std::endl;
	}
	else
	{
		std::cout << "NON!" << std::endl;
		Channel newCh;
		newCh.chName = (*user)->getCommand().get_args().at(0);
		channels.push_back(newCh);
	}
	// userがチャンネルの中にいるかを確認する　してなかったら入居
	//　該当のチャンネルを探す必要がある
	Channel *ch;
	for (int i = 0; i < channels.size(); i++)
	{
		if (channels.at(i).chName == arg_ch_name)
			ch = &(channels.at(i));
	}
	//
	if (ch->is_user_joined((*user)->getNickName()))
	{
		std::cout << "JOINED" << std::endl;
	}
	else
	{
		std::cout << "NON JOINED!" << std::endl;
		ch->chUsers.push_back((*user)->getNickName());
		std::cout << "USER ADDED!" << std::endl;
		for (int i = 0; i < ch->chUsers.size(); i++)
			std::cout << ch->chUsers.at(i) << std::endl;
	}

	// exit(1);
}
	// std::string string = ":test JOIN #one\n";
	// if (-1 == send((*user)->getFd(), string.c_str(), string.length(), 0))
	// 	std::cout << "it is wrong!!" << std::endl;