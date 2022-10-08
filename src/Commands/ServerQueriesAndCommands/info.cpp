/*

   Command: CONNECT
Parameters: <target server> <port> [ <remote server> ]

CONNECTコマンドは、サーバーが他のサーバーとの新しい接続を直ちに試行するよう要求するために使用されます。CONNECT コマンドは、他のサーバとの新しい接続を直ちに確立するようサーバに要求するために使用されます。
CONNECT は特権的なコマンドで、IRC Operator のみが使用できるようにすべきです。

もし、 \<remote server>が与えられ、そのマスクが解析サーバーの名前と一致しない場合、CONNECTの試みは最初に一致したリモートサーバーに送られます。
それ以外の場合は、リクエストを処理するサーバーによってCONNECTの試行が行われます。

リモートCONNECTコマンドを受信したサーバーは、CONNECTコマンドに対応するWALLOPSメッセージを生成するべきである(SHOULD)。WALLOPSメッセージを生成するべきである。


Numeric Replies:

        ERR_NOSUCHSERVER              ERR_NOPRIVILEGES
        ERR_NEEDMOREPARAMS

Examples:

CONNECT tolsun.oulu.fi 6667     ; 
ローカルサーバーからポート6667のtolsun.ulu.fiへの接続を試行するコマンド

*/