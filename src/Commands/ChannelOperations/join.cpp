#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"

bool	Server::isChannelExist(std::string newCh)
{
	for(std::vector<Channel>::size_type i = 0; i < channels.size(); i++)
	{
		if (channels.at(i).chName == newCh)
			return true;
	}
	return false;
}

void	Server::joinChannel(Command cmd, std::vector<User *>::iterator user)
{
	// printDebugMsgYellow("joinChannel called!");

	//　引数
	// for (int i = 0; i < (*user)->getCommand().get_args().size(); i++)
	// {
	// 	std::cout << i << ":" << (*user)->getCommand().get_args().at(i) << std::endl;
	// }
	std::string argChName = (cmd.get_args().at(0));
	//引数のチャンネル名が、serverのチャンネルリストのなかにあるか確認
	if (isChannelExist(argChName))
	{
	}
	else
	{
		Channel newCh;
		newCh.chName = argChName;
		channels.push_back(newCh);
	}
	// userがチャンネルの中にいるかを確認する　してなかったら入居
	//　該当のチャンネルを探す必要がある
	Channel *ch = getChannel(argChName);
	if (ch == NULL)
		return ;
	if (ch->isUserJoined((*user)->getNickName()))
	{
		printDebugMsgYellow("ALREADY JOINED");
	}
	else
	{
		printDebugMsgYellow("NOT JOINED YET!");
		ch->chUsers.push_back((*user)->getNickName());
		printDebugMsgYellow("USER ADDED!");
		for (unsigned long i = 0; i < ch->chUsers.size(); i++)
			std::cout << ch->chUsers.at(i) << std::endl;
	}
}

// 3.2.1 Join message

//       Command: JOIN
//    Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
//                / "0"

//    The JOIN command is used by a user to request to start listening to
//    the specific channel.  Servers MUST be able to parse arguments in the
//    form of a list of target, but SHOULD NOT use lists when sending JOIN
//    messages to clients.

//    Once a user has joined a channel, he receives information about
//    all commands his server receives affecting the channel.  This
//    includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
//    This allows channel members to keep track of the other channel
//    members, as well as channel modes.

//    If a JOIN is successful, the user receives a JOIN message as
//    confirmation and is then sent the channel's topic (using RPL_TOPIC) and
//    the list of users who are on the channel (using RPL_NAMREPLY), which
//    MUST include the user joining.

//    Note that this message accepts a special argument ("0"), which is
//    a special request to leave all channels the user is currently a member
//    of.  The server will process this message as if the user had sent
//    a PART command (See Section 3.2.2) for each channel he is a member
//    of.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//            ERR_CHANNELISFULL               ERR_BADCHANMASK
//            ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//            ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
//            RPL_TOPIC

//    Examples:

//    JOIN #foobar                    ; Command to join channel #foobar.

//    JOIN &foo fubar                 ; Command to join channel &foo using
//                                    key "fubar".



// Kalt                         Informational                     [Page 16]
// 
// RFC 2812          Internet Relay Chat: Client Protocol        April 2000


//    JOIN #foo,&bar fubar            ; Command to join channel #foo using
//                                    key "fubar" and &bar using no key.

//    JOIN #foo,#bar fubar,foobar     ; Command to join channel #foo using
//                                    key "fubar", and channel #bar using
//                                    key "foobar".

//    JOIN #foo,#bar                  ; Command to join channels #foo and
//                                    #bar.

//    JOIN 0                          ; Leave all currently joined
//                                    channels.

//    :WiZ!jto@tolsun.oulu.fi JOIN #Twilight_zone ; JOIN message from WiZ
//                                    on channel #Twilight_zone