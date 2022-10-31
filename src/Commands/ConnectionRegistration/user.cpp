#include "Server.hpp"
#include "Command.hpp"
#include "User.hpp"

//TODO 中身の実装をしていない

void Server::user(std::vector<User *>::iterator user)
{
   std::cout << (*user)->getCommand().get_args().at(0) << std::endl;
   std::cout << "user called" << std::endl;
   // exit(1);
}

void Server::capUser(std::vector<User *>::iterator user, std::string arg)
{
   // (*user)->setNickName(arg);  
   std::cout << "capUser done" << std::endl;
   // exit(1);
}

/*
3.1.3 User message

      Command: USER
   Parameters: <user> <mode> <unused> <realname>


	USERコマンドはコネクションの最初に、新規ユーザーに
	権限　, hostname, realnameを指定するするために使われる

	mode引数は数字でなければいけない、そしてサーバーに自動で設定されうる
	この引数は2bitのbitmaskで、
	bit2: w
	bit3: i
	がセットされる

	realnameにはスペースが含まれる可能性がある

   The USER command is used at the beginning of connection to specify
   the username, hostname and realname of a new user.

   The <mode> parameter should be a numeric, and can be used to
   automatically set user modes when registering with the server.  This
   parameter is a bitmask, with only 2 bits having any signification: if
   the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
   set, the user mode 'i' will be set.  (See Section 3.1.5 "User
   Modes").

   The <realname> may contain space characters.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

   USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan".

   USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan", and asking to be set
                                   invisible.
*/