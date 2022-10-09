/*
3.1.4 Oper message

      Command: OPER
   Parameters: <name> <password>

	オペレーターじゃないノーマルユーザーがオペレーターになるためのコマンド。
	成功時にはMODEメッセージが帰ってくる

   A normal user uses the OPER command to obtain operator privileges.
   The combination of <name> and <password> are REQUIRED to gain
   Operator privileges.  Upon success, the user will receive a MODE
   message (see section 3.1.5) indicating the new user modes.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              RPL_YOUREOPER
           ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

   Example:

   OPER foo bar                    ; Attempt to register as an operator
                                   using a username of "foo" and "bar"
                                   as the password.


*/