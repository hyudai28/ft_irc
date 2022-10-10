/*
3.6.2 Whois query

      Command: WHOIS
   Parameters: [ <target> ] <mask> *( "," <mask> )

	特定ユーザーの情報を引き出すのに使う
	サーバーはマスクにマッチした複数の数字メッセージを返答する
	もしワイルドカードが<mask>にない場合、nickに関係する閲覧可能な情報がみられる

	もし<target>が指定されているなら、クエリが指定されたサーバーに飛ぶ
	あるユーザーがどれだけ離席しているかはローカルサーバーだけが知っている？

	targetにwildcard使用可能

   This command is used to query information about particular user.
   The server will answer this command with several numeric messages
   indicating different statuses of each user which matches the mask (if
   you are entitled to see them).  If no wildcard is present in the
   <mask>, any information about that nick which you are allowed to see
   is presented.

   If the <target> parameter is specified, it sends the query to a
   specific server.  It is useful if you want to know how long the user
   in question has been idle as only local server (i.e., the server the
   user is directly connected to) knows that information, while
   everything else is globally known.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

           ERR_NOSUCHSERVER              ERR_NONICKNAMEGIVEN
           RPL_WHOISUSER                 RPL_WHOISCHANNELS
           RPL_WHOISCHANNELS             RPL_WHOISSERVER
           RPL_AWAY                      RPL_WHOISOPERATOR
           RPL_WHOISIDLE                 ERR_NOSUCHNICK
           RPL_ENDOFWHOIS

   Examples:

   WHOIS wiz                       ; return available user information
                                   about nick WiZ

   WHOIS eff.org trillian          ; ask server eff.org for user
                                   information  about trillian
*/
