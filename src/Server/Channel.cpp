#include "Channel.hpp"

Channel::Channel()
{

}

Channel::~Channel()
{

}

bool	Channel::is_user_joined(std::string nickname)
{
	for(int i = 0; i < chUsers.size(); i++)
	{
		std::cout << "checking channels!" << std::endl;
		if (chUsers.at(i) == nickname)
			return true;
	}
	return false;
}