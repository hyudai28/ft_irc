#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include "Server.hpp"

# include <vector>
# include <map>
# include <poll.h>

# define DEBUG 1

class Channel
{
	public:
		Channel();
		~Channel();
		std::string chName;
		std::vector<std::string> chUsers;
		bool	is_user_joined(std::string nickname);

};

#endif /* CHANNEL_HPP */
