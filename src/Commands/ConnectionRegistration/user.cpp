#include "Server.hpp"
#include "Command.hpp"
#include "User.hpp"

#include "replies.cpp"

void Server::user_cmd(Command cmd, std::vector<User *>::iterator user)
{
	// if (-1 == shortSend((*user)->getFd(), RPL_WELCOME("kamori!kamori@127.0.0.1\n")))
	// 	printDebugMsgYellow("send failed!");
   // printDebugMsgYellow(cmd.get_args().at(0));
   (*user)->userName = cmd.get_args().at(0);
   printDebugMsgYellow("user done (done nothing actually)");
   std::string string = "001 " + (*user)->nickName +  " Welcome to the Internet Network "
   + (*user)->nickName + "!" + (*user)->userName + "@" + (*user)->hostAddr + "\n";
	if (-1 == send((*user)->getFd(), string.c_str(), string.length(), 0))
		printDebugMsgYellow("send failed!");
}

/*
3.1.3 User message

      Command: USER
   Parameters: <username> <mode> <unused> <realname>


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