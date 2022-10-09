/*

   Command: TIME
Parameters: [ <target> ]

timeコマンドは、指定されたサーバーからローカルタイムを照会するために使用されます。サーバに問い合わせるコマンドです。
 
<target> パラメータを指定しない場合、コマンドを受信したサーバーは問い合わせに応答する必要があります。

\<target> パラメーターにはワイルドカードを使用できます。


Numeric Replies:

        ERR_NOSUCHSERVER              RPL_TIME

Examples:
TIME tolsun.oulu.fi             ;  
サーバー "tolson.oulu.fi" の時刻を確認する。


*/