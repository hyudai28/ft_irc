/*

   Command: TRACE
Parameters: [ \<target> ]

TRACEコマンドは、特定のサーバへの経路とそのピアの情報を見つけるために使用されます。  
このコマンドを処理する各サーバは、それについて送信者に報告しなければならない(MUST)。 パススルーリンクからの応答は、デスティネーションへの経路を示す鎖を形成する。 この応答を送り返した後、与えられた<target>サーバに到達するまで、次のサーバに問い合わせを送らなければならない(MUST)。

TRACEコマンドは、特定のサーバへの経路を見つけるために使われる。 
このメッセージを処理する各サーバは、それがパススルーリンクであることを示す応答を送信することによって送信者にそれを伝え、応答の連鎖を形成しなければならない（MUST）。
この応答を送り返した後、次のサーバにTRACEメッセージを送らなければならない(MUST)。TRACEメッセージを次のサーバに送らなければならない。
もし を省略した場合、TRACEコマンドは送信者にメッセージを送信することが推奨されます（RECOMMENDED）。
コマンドは、ローカルサーバがどのサーバに直接接続しているかを示すメッセージを送信者に送信することが推奨されます。


もし、"the destination "が実際のサーバである場合、"the destination server is REQUIRED "となります。を報告することが要求されます。オペレータによって発行されたコマンドの場合、サーバーは、それに接続されているすべてのサーバー、サー コマンドを発行したのがオペレータの場合、サーバはそれに接続されているすべてのユーザーを報告してもよい(MAY) を報告してもかまいません。
サーバーは、コマンドがオペレーターによって発行された場合、接続しているすべてのユーザーを報告してもよいです。を返します。 
を省略した場合、そのニックネームに対する応答のみが行われます。を省略した場合、TRACE コマンドは処理サーバを対象として解析されることが推奨されま す（RECOMMENDED）。として解析されることが推奨されます。

\<target> パラメータにはワイルドカードを使用することができます。

Numeric Replies:

     ERR_NOSUCHSERVER

TRACEメッセージが他のサーバに向けられたものである場合、すべての中間サーバはRPL_TRACELINK応答を返す必要があります。
中間サーバーは、RPL_TRACELINK応答を返して、TRACEがそのサーバーを通過し、次にどこへ行くかを示さなければなりません。
TRACEが通過したことと、次の行き先を示すために、すべての中間サーバはRPL_TRACELINK応答を返す必要があります。

     RPL_TRACELINK

TRACE応答は、以下の数値応答からいくつでも構成することができる。

     RPL_TRACECONNECTING           RPL_TRACEHANDSHAKE
     RPL_TRACEUNKNOWN              RPL_TRACEOPERATOR
     RPL_TRACEUSER                 RPL_TRACESERVER
     RPL_TRACESERVICE              RPL_TRACENEWTYPE
     RPL_TRACECLASS                RPL_TRACELOG
     RPL_TRACEEND

Examples:

TRACE *.oulu.fi                 ; 
TRACEで*.oulu.fiに一致するサーバーに接続


*/