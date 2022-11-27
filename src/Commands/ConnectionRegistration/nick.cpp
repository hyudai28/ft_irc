#include "Server.hpp"
#include "Command.hpp"
#include "User.hpp"

void Server::nick(Command cmd, std::vector<User *>::iterator user)
{
   // printDebugMsgYellow( "nick called");
         // ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
         // ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
         // ERR_UNAVAILRESOURCE             ERR_RESTRICTED
   if (cmd.args.size() != 0)
      (*user)->setNickName(cmd.args.at(0)); 
}

/*
4.1.3 Nick

      Command: NICK
   Parameters: <nickname> <hopcount> <username> <host> <servertoken>
               <umode> <realname>

   This form of the NICK message MUST NOT be allowed from user
   connections. However, it MUST be used instead of the NICK/USER pair
   to notify other servers of new users joining the IRC network.

   This message is really the combination of three distinct messages:
   NICK, USER and MODE [IRC-CLIENT].

   The <hopcount> parameter is used by servers to indicate how far away
   a user is from its home server.  A local connection has a hopcount of
   0.  The hopcount value is incremented by each passed server.

   The <servertoken> parameter replaces the <servername> parameter of
   the USER (See section 4.1.2 for more information on server tokens).

   Examples:

   NICK syrk 5 kalt millennium.stealth.net 34 +i :Christophe Kalt ; New
                                   user with nickname "syrk", username
                                   "kalt", connected from host
                                   "millennium.stealth.net" to server
                                   "34" ("csd.bu.edu" according to the
                                   previous example).

   :krys NICK syrk                 ; The other form of the NICK message,
                                   as defined in "IRC Client Protocol"
                                   [IRC-CLIENT] and used between
                                   servers: krys changed his nickname to
                                   syrk

client
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