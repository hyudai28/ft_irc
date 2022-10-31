#include "Server.hpp"
#include "Command.hpp"
#include "User.hpp"

void Server::nick(std::vector<User *>::iterator user)
{
   // printDebugMsgYellow( "nick called");
   // exit(1);
}

void Server::capNick(std::vector<User *>::iterator user, std::string arg)
{
   (*user)->setNickName(arg);   
   // printDebugMsgYellow("capNick done");
}

/*
3.1.2 Nick message


      Command: NICK
   Parameters: <nickname>

	ニックネームの付与、変更

   NICK command is used to give user a nickname or change the existing
   one.

   Numeric Replies:

           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
           ERR_UNAVAILRESOURCE             ERR_RESTRICTED

   Examples:

   NICK Wiz                ; Introducing new nick "Wiz" if session is
                           still unregistered, or user changing his
                           nickname to "Wiz"

   :WiZ!jto@tolsun.oulu.fi NICK Kilroy
                           ; Server telling that WiZ changed his
                           nickname to Kilroy.
*/