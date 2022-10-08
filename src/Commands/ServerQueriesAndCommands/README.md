# 3.4 Server queries and commands JPN

サーバー照会コマンド群は、ネットワークに接続されたあらゆるサーバーの情報を返 ネットワークに接続されているすべてのサーバに関する情報を返すように設計されています。

これらの問い合わせでは、パラメータが <target> のように表示される場合、ワイルドカード マスクは通常有効である。

しかし、各パラメータに対して、1つのクエリ と返信のセットだけが生成されます。 ほとんどの場合、もしニックネーム が指定された場合、それはユーザが接続しているサーバを意味します。

これらのメッセージは通常サービスにとってほとんど価値がありません。したがって、サービスがこれらを使うことを禁止することが推奨されます(RECOMMENDED)。

このディレクトリには以下のコマンドが該当します。
 - [Motd message](#motd)
 - [Lusers message](#lusers)
 - [Version message](#version)
 - [Stats message](#stats)
 - [Links message](#links)
 - [Time message](#time)
 - [Connect message](#connect)
 - [Trace message](#trace)
 - [Admin command](#admin)
 - [Info command](#info)


---
## [Motd](#motd)
   Command: MOTD
```
   Parameters: [ <target> ]
```
MOTDコマンドは、指定されたサーバーの"今日の日付"を取得するためのものです。  
\<target>が省略された場合は現在のサーバー。

\<target>パラメータにはワイルドカードが使用できます。
```
   Numeric Replies:
           RPL_MOTDSTART                   RPL_MOTD
           RPL_ENDOFMOTD                   ERR_NOMOTD
```


---
## [Lusers message](#lusers)
Command: LUSERS
```
   Parameters: [ <mask> [ <target> ] ]
```
LUSERS コマンドは、IRC ネットワークのサイズに関する統計を取るために使用されます。パラメータを指定しない場合は、ネットワーク全体について回答します。

\<mask> が指定された場合、そのマスクに一致するサーバによって形成されるネットワークの一部のみに関する返答がある。

最後に、\<target> パラメータが指定されると、要求をそのサーバに転送し、そのサーバが応答を生成する。

\<target> パラメータにはワイルドカードを使用できます。
```
   Numeric Replies:

           RPL_LUSERCLIENT                 RPL_LUSEROP
           RPL_LUSERUNKOWN                 RPL_LUSERCHANNELS
           RPL_LUSERME                     ERR_NOSUCHSERVER
```

---
## [Version message](#version)
   Command: VERSION
```
Parameters: [ <target> ]
```

VERSIONコマンドは、サーバープログラムのバージョンを照会するために使用します。
プログラムのバージョンを照会します。 オプションのパラメータ \<target> は、クライアントが直接接続していないサーバ・プログラムのバージョンを照会するために使用します。

\<target> パラメータにはワイルドカードを使用できる。

```
Numeric Replies:
        ERR_NOSUCHSERVER                RPL_VERSION

Examples:
VERSION tolsun.oulu.fi          ;   
サーバー「tolsun.oulu.fi」のバージョンを確認するコマンドです。
```

---
## [Stats message](#stats)


   Command: STATS
```
Parameters: [ <query> [ <target> ] ]
```

stats コマンドは、特定のサーバの統計情報を取得するために使用されます。 もし
\<パラメータを省略した場合は、統計情報の末尾のみを返信します。
を返します。

クエリーは1文字でも可能で、その文字は送信先のサーバーでのみチェックされ、それ以外は中間サーバーに渡されます。
のみチェックされ、それ以外は中間サーバーで無視されます。
は無視され、変更されない。

\<target> パラメータにはワイルドカードを使用できます。

以下のものを除き、有効なクエリのリストは実装に依存します。
実装に依存します。 以下の標準的なクエリーは、サーバーでサポートされるべきです（SHOULD）。
以下の標準的なクエリーはサーバーでサポートされるべきです。

```
         l - サーバーのコネクションのリストを返し、各コネクションの確立時間、コネクション上のトラフィックをKbytesとメッセージで各方向に表示します。
         m - サーバーがサポートしている各コマンドの使用回数を返します。使用回数が 0 のコマンドは省略可能です。
         o - 構成された特権ユーザーのリストを返します。
         u - サーバーが稼働している時間を示す文字列を返します。
```
また、クライアントやサーバーのアクセス設定もこの方法で公開することが推奨されます（RECOMMENDED）。

```
Numeric Replies:

        ERR_NOSUCHSERVER
        RPL_STATSLINKINFO                RPL_STATSUPTIME
        RPL_STATSCOMMANDS                RPL_STATSOLINE
        RPL_ENDOFSTATS
```
```
Examples:

STATS m                         ; 
接続中のサーバーのコマンド使用状況を確認するコマンド
```


---
## [Links message](#links)
```
   Command: LINKS
Parameters: [ [ <remote server> ] <server mask> ]
```

LINKSを使うと、ユーザーは、問い合わせに答えるサーバーが知っている すべてのサーバー名をリストアップすることができます。 返されるサーバーのリストはマスクと一致しなければならず、マスクが与えられていない場合は完全なリストが返される。

<server mask> に加えて <remote server> が指定された場合、LINKS コマンドはその名前にマッチする最初のサーバに転送され、そのサーバは問い合わせに応答することが要求される。

```
Numeric Replies:

     ERR_NOSUCHSERVER
     RPL_LINKS                        RPL_ENDOFLINKS

Examples:

LINKS *.au                      ;  
サーバ名が*.auに一致するサーバをすべてリストアップするコマンドです。

LINKS *.edu *.bu.edu            ;  
*.bu.eduに一致するサーバーを、*.eduに一致する最初のサーバーから見た状態でリストアップするコマンドです。
```




---
## [Time message](#time)
   Command: TIME
```
Parameters: [ <target> ]
```

timeコマンドは、指定されたサーバーからローカルタイムを照会するために使用されます。サーバに問い合わせるコマンドです。
 
<target> パラメータを指定しない場合、コマンドを受信したサーバーは問い合わせに応答する必要があります。

\<target> パラメーターにはワイルドカードを使用できます。


```
Numeric Replies:

        ERR_NOSUCHSERVER              RPL_TIME

Examples:
TIME tolsun.oulu.fi             ;  
サーバー "tolson.oulu.fi" の時刻を確認する。
```


---
## [Connect message](#connect)
   Command: CONNECT
```
Parameters: <target server> <port> [ <remote server> ]
```

CONNECTコマンドは、サーバーが他のサーバーとの新しい接続を直ちに試行するよう要求するために使用されます。CONNECT コマンドは、他のサーバとの新しい接続を直ちに確立するようサーバに要求するために使用されます。
CONNECT は特権的なコマンドで、IRC Operator のみが使用できるようにすべきです。

もし、 \<remote server>が与えられ、そのマスクが解析サーバーの名前と一致しない場合、CONNECTの試みは最初に一致したリモートサーバーに送られます。
それ以外の場合は、リクエストを処理するサーバーによってCONNECTの試行が行われます。

リモートCONNECTコマンドを受信したサーバーは、CONNECTコマンドに対応するWALLOPSメッセージを生成するべきである(SHOULD)。WALLOPSメッセージを生成するべきである。


```
Numeric Replies:

        ERR_NOSUCHSERVER              ERR_NOPRIVILEGES
        ERR_NEEDMOREPARAMS

Examples:

CONNECT tolsun.oulu.fi 6667     ; 
ローカルサーバーからポート6667のtolsun.ulu.fiへの接続を試行するコマンド
```


---
## [Trace message](#trace)
   Command: TRACE
```
Parameters: [ \<target> ]
```

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

```
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
```


---
## [Admin message](#admin)
   Command: ADMIN
```
Parameters: [ <target> ]
```

admin コマンドは、指定されたサーバー、または \<target> パラメーターが省略された場合は現在のサーバーの管理者についての情報を検索するために使用されます。 各サーバーは、ADMIN メッセージを他のサーバーに転送する機能を持たなければなりません（MUST）。

\<target> パラメータにはワイルドカードを使用できます。

```
Numeric Replies:

        ERR_NOSUCHSERVER
        RPL_ADMINME                   RPL_ADMINLOC1
        RPL_ADMINLOC2                 RPL_ADMINEMAIL

Examples:

ADMIN tolsun.oulu.fi            ; 
tolsun.oulu.fiからADMIN返信を要求する。

ADMIN syrk                      ; 
ユーザーsyrkが接続しているサーバーへのADMINリクエスト
```

---
## [Info message](#info)
   Command: INFO
```
Parameters: [ <target> ]
```

INFOコマンドは、サーバーに関する情報を返すために必要です。
バージョン、コンパイルされた時期、パッチレベル、起動時期、その他 起動時、その他関連すると思われる雑多な情報。関連すると思われるその他の情報です。

\<target> パラメータにはワイルドカードを使用できます。

```
Numeric Replies:

        ERR_NOSUCHSERVER
        RPL_INFO                      RPL_ENDOFINFO

Examples:

INFO csd.bu.edu                 ; 
csd.bu.eduからINFOの返信を要求する。

INFO Angel                      ; 
Angelが接続されているサーバーに情報を要求します。
```



---
# 3.4 Server queries and commands EN

The server query group of commands has been designed to return
information about any server which is connected to the network.

In these queries, where a parameter appears as <target>, wildcard
masks are usually valid.  For each parameter, however, only one query
and set of replies is to be generated.  In most cases, if a nickname
is given, it will mean the server to which the user is connected.

These messages typically have little value for services, it is
therefore RECOMMENDED to forbid services from using them.


The following commands correspond to this directory.
 - [Motd message](#motd_EN)
 - [Lusers message](#lusers_EN)
 - [Version message](#version_EN)
 - [Stats message](#stats_EN)
 - [Links message](#links_EN)
 - [Time message](#time_EN)
 - [Connect message](#connect_EN)
 - [Trace message](#trace_EN)
 - [Admin command](#admin_EN)
 - [Info command](#info_EN)


---
## [Motd](#motd_EN)
Command: MOTD
```
Parameters: [ <target> ]
```

The MOTD command is used to get the "Message Of The Day" of the given
server, or current server if \<target> is omitted.

Wildcards are allowed in the \<target> parameter.
```
   Numeric Replies:
           RPL_MOTDSTART                   RPL_MOTD
           RPL_ENDOFMOTD                   ERR_NOMOTD
```

---
## [Lusers message](#lusers_EN)
Command: LUSERS
```
   Parameters: [ <mask> [ <target> ] ]
```
The LUSERS command is used to get statistics about the size of the IRC network. If no parameter is given, the reply will be about the whole net. 

If a \<mask> is specified, then the reply will only concern the part of the network formed by the servers matching the mask.

Finally, if the \<target> parameter is specified, the request is forwarded to that server which will generate the reply.

Wildcards are allowed in the \<target> parameter.
```
   Numeric Replies:

           RPL_LUSERCLIENT                 RPL_LUSEROP
           RPL_LUSERUNKOWN                 RPL_LUSERCHANNELS
           RPL_LUSERME                     ERR_NOSUCHSERVER
```


---
## [Version message](#version_EN)
Command: VERSION
```
Parameters: [ <target> ]
```

The VERSION command is used to query the version of the server program.  
An optional parameter <target> is used to query the version of the server program which a client is not directly connected to.
  
Wildcards are allowed in the <target> parameter.

```
Numeric Replies:

        ERR_NOSUCHSERVER                RPL_VERSION

Examples:

VERSION tolsun.oulu.fi          ; 
Command to check the version of server "tolsun.oulu.fi".
```



---
## [Stats message](#stats_EN)

   Command: STATS
```
Parameters: [ <query> [ <target> ] ]
```

The stats command is used to query statistics of certain server.  If
\<query> parameter is omitted, only the end of stats reply is sent
back.

A query may be given for any single letter which is only checked by
the destination server and is otherwise passed on by intermediate
servers, ignored and unaltered.

Wildcards are allowed in the \<target> parameter.

Except for the ones below, the list of valid queries is
implementation dependent.  The standard queries below SHOULD be
supported by the server:
```
         l - returns a list of the server's connections, showing how
             long each connection has been established and the
             traffic over that connection in Kbytes and messages for
             each direction;
         m - returns the usage count for each of commands supported
             by the server; commands for which the usage count is
             zero MAY be omitted;
         o - returns a list of configured privileged users,
             operators;
         u - returns a string showing how long the server has been
             up.
```
It is also RECOMMENDED that client and server access configuration be
published this way.
```
Numeric Replies:

        ERR_NOSUCHSERVER
        RPL_STATSLINKINFO                RPL_STATSUPTIME
        RPL_STATSCOMMANDS                RPL_STATSOLINE
        RPL_ENDOFSTATS
```
```
Examples:

STATS m                         ; 
Command to check the command usage for the server you are connected to
```

---
## [Links message](#links_EN)
```
   Command: LINKS
Parameters: [ [ <remote server> ] <server mask> ]
```

With LINKS, a user can list all servernames, which are known by the
server answering the query.  The returned list of servers MUST match
the mask, or if no mask is given, the full list is returned.

If \<remote server> is given in addition to \<server mask>, the LINKS
command is forwarded to the first server found that matches that name
(if any), and that server is then required to answer the query.

```
Numeric Replies:

     ERR_NOSUCHSERVER
     RPL_LINKS                        RPL_ENDOFLINKS

Examples:

LINKS *.au                      ;  
Command to list all servers which have a name that matches *.au;

LINKS *.edu *.bu.edu            ;  
Command to list servers matching *.bu.edu as seen by the first server matching *.edu.
```


---
## [Time message](#time_EN)

   Command: TIME
```
Parameters: [ <target> ]
```

The time command is used to query local time from the specified
server. If the \<target> parameter is not given, the server receiving
the command must reply to the query.

Wildcards are allowed in the \<target> parameter.

```
Numeric Replies:

        ERR_NOSUCHSERVER              RPL_TIME

Examples:
TIME tolsun.oulu.fi             ; check the time on the server
                                "tolson.oulu.fi"
```

---
## [Connect message](#connect_EN)

   Command: CONNECT
   ```
Parameters: <target server> <port> [ <remote server> ]
```

The CONNECT command can be used to request a server to try to
establish a new connection to another server immediately.
CONNECT is a privileged command and SHOULD be available only to IRC Operators.

If a \<remote server> is given and its mask doesn't match name of the parsing server, the CONNECT attempt is sent to the first match of remote server.
Otherwise the CONNECT attempt is made by the server processing the request.

The server receiving a remote CONNECT command SHOULD generate a
WALLOPS message describing the source and target of the request.
```
Numeric Replies:

        ERR_NOSUCHSERVER              ERR_NOPRIVILEGES
        ERR_NEEDMOREPARAMS

Examples:

CONNECT tolsun.oulu.fi 6667     ; Command to attempt to connect local
                                server to tolsun.oulu.fi on port 6667
```

---
## [Trace message](#trace_EN)
   Command: TRACE
```
Parameters: [ \<target> ]
```

TRACE command is used to find the route to specific server and
information about its peers.  Each server that processes this command
MUST report to the sender about it.  The replies from pass-through
links form a chain, which shows route to destination.  After sending
this reply back, the query MUST be sent to the next server until
given \<target> server is reached.

TRACE command is used to find the route to specific server.  Each
server that processes this message MUST tell the sender about it by
sending a reply indicating it is a pass-through link, forming a chain
of replies.  After sending this reply back, it MUST then send the
TRACE message to the next server until given server is reached.  If
the \<target> parameter is omitted, it is RECOMMENDED that TRACE
command sends a message to the sender telling which servers the local
server has direct connection to.

If the destination given by \<target> is an actual server, the
destination server is REQUIRED to report all servers, services and
operators which are connected to it; if the command was issued by an
operator, the server MAY also report all users which are connected to
it.  If the destination given by \<target> is a nickname, then only a
reply for that nickname is given.  If the \<target> parameter is
omitted, it is RECOMMENDED that the TRACE command is parsed as
targeted to the processing server.

Wildcards are allowed in the \<target> parameter.

```
Numeric Replies:

        ERR_NOSUCHSERVER

   If the TRACE message is destined for another server, all
   intermediate servers must return a RPL_TRACELINK reply to indicate
   that the TRACE passed through it and where it is going next.

        RPL_TRACELINK

   A TRACE reply may be composed of any number of the following
   numeric replies.

        RPL_TRACECONNECTING           RPL_TRACEHANDSHAKE
        RPL_TRACEUNKNOWN              RPL_TRACEOPERATOR
        RPL_TRACEUSER                 RPL_TRACESERVER
        RPL_TRACESERVICE              RPL_TRACENEWTYPE
        RPL_TRACECLASS                RPL_TRACELOG
        RPL_TRACEEND

Examples:

TRACE *.oulu.fi                 ; TRACE to a server matching
                                *.oulu.fi
```

---
## [Admin message](#admin_EN)

   Command: ADMIN
```
Parameters: [ <target> ]
```

The admin command is used to find information about the administrator
of the given server, or current server if \<target> parameter is
omitted.  Each server MUST have the ability to forward ADMIN messages
to other servers.

Wildcards are allowed in the \<target> parameter.

```
Numeric Replies:

        ERR_NOSUCHSERVER
        RPL_ADMINME                   RPL_ADMINLOC1
        RPL_ADMINLOC2                 RPL_ADMINEMAIL

Examples:

ADMIN tolsun.oulu.fi            ; request an ADMIN reply from
                                tolsun.oulu.fi

ADMIN syrk                      ; ADMIN request for the server to
                                which the user syrk is connected
```

---
## [Info message](#info_EN)

   Command: INFO
```
Parameters: [ <target> ]
```

The INFO command is REQUIRED to return information describing the
server: its version, when it was compiled, the patchlevel, when it
was started, and any other miscellaneous information which may be
considered to be relevant.

Wildcards are allowed in the \<target> parameter.

```
Numeric Replies:

        ERR_NOSUCHSERVER
        RPL_INFO                      RPL_ENDOFINFO

Examples:

INFO csd.bu.edu                 ; request an INFO reply from
                                csd.bu.edu

INFO Angel                      ; request info from the server that
                                Angel is connected to.
```