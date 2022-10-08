/*

Command: SQUERY
Parameters: <servicename> <text>

SQUERYコマンドはPRIVMSGと同様に使用されます。 
唯一の違いは、受信者がサービスでなければならないことです。 これはテキストメッセージがサービスに配信される唯一の方法です。

返信の詳細と例については、PRIVMSGを参照してください。


Examples:
SQUERY irchelp :HELP privmsg;  
ニックネームがirchelpへのサービスからのメッセージ。

SQUERY dict@irc.fr :fr2en blaireau;  
dict@irc.fr.　へのメッセージ


*/