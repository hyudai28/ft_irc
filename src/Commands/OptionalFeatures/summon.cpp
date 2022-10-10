/*
4.5 Summon message

      Command: SUMMON
   Parameters: <user> [ <target> [ <channel> ] ]

	サーバーをホストしている人にサーバー連携を持ちかけるコマンド
	対象サーバーがSUMMON可能状態かつ、ホストしているユーザーがログインしていて、サーバーのプロセスが
	user'ttyに書き込めるときに使える

	もし<server>部分が与えられていていないなら、クライアントが繋がっているサーバーからターゲットっぽい人を
	推測する

	もしSUMMON不可能なサーバーならERR_SUMMONDISABLEがくる

   The SUMMON command can be used to give users who are on a host
   running an IRC server a message asking them to please join IRC.  This
   message is only sent if the target server (a) has SUMMON enabled, (b)
   the user is logged in and (c) the server process can write to the
   user's tty (or similar).

   If no <server> parameter is given it tries to summon <user> from the
   server the client is connected to is assumed as the target.

   If summon is not enabled in a server, it MUST return the
   ERR_SUMMONDISABLED numeric.

   Numeric Replies:

           ERR_NORECIPIENT               ERR_FILEERROR
           ERR_NOLOGIN                   ERR_NOSUCHSERVER
           ERR_SUMMONDISABLED            RPL_SUMMONING


   Examples:

   SUMMON jto                      ; summon user jto on the server's
                                   host

   SUMMON jto tolsun.oulu.fi       ; summon user jto on the host which a
                                   server named "tolsun.oulu.fi" is
                                   running.

*/
