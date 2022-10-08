IRCサーバーに対してコネクト、ディスコネするためのコマンド群
PASSコマンドは絶対必要とはされていないけど順番的に、NICK/USERかSERVICE
コマンドの前にやらなければいけない

クライアントの認証プロセスでおすすめなのは以下の通り
                1. Pass message
2. Nick message                 2. Service message
3. User message

　成功時には、クライアントの識別子を含んだRPL＿WELCOMEとRPL＿YOURSERVICEメッセージが送られる

3.1 Connection Registration

   The commands described here are used to register a connection with an
   IRC server as a user as well as to correctly disconnect.

   A "PASS" command is not required for a client connection to be
   registered, but it MUST precede the latter of the NICK/USER
   combination (for a user connection) or the SERVICE command (for a
   service connection). The RECOMMENDED order for a client to register
   is as follows:

                           1. Pass message
           2. Nick message                 2. Service message
           3. User message

   Upon success, the client will receive an RPL_WELCOME (for users) or
   RPL_YOURESERVICE (for services) message indicating that the
   connection is now registered and known the to the entire IRC network.
   The reply message MUST contain the full client identifier upon which
   it was registered.