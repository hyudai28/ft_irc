#include "Channel.hpp"

Channel::Channel()
{

}

Channel::~Channel()
{

}

bool	Channel::isUserJoined(std::string nickname)
{
	for(std::vector<std::basic_string<char> >::size_type i = 0; i < chUsers.size(); i++)
	{
		// std::cout << "checking channels!" << std::endl;
		if (chUsers.at(i) == nickname)
			return true;
	}
	return false;
}
