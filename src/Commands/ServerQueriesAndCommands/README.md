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


---
## [Lusers message](#lusers)


---
## [Stats message](#stats)


---
## [Links message](#links)


---
## [Time message](#time)


---
## [Connect message](#connect)


---
## [Trace message](#trace)


---
## [Admin message](#admin)


---
## [Info message](#info)




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
## [Stats message](#stats_EN)

   Command: VERSION
```
Parameters: [ <target> ]
```

The VERSION command is used to query the version of the server
program.  An optional parameter \<target> is used to query the version
of the server program which a client is not directly connected to.

Wildcards are allowed in the \<target> parameter.

```
Numeric Replies:
        ERR_NOSUCHSERVER                RPL_VERSION

Examples:
VERSION tolsun.oulu.fi          ; Command to check the version of
                                server "tolsun.oulu.fi".
```



---
## [Links message](#links_EN)
```
Command: STATS
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

It is also RECOMMENDED that client and server access configuration be
published this way.

```
Numeric Replies:

        ERR_NOSUCHSERVER
        RPL_STATSLINKINFO                RPL_STATSUPTIME
        RPL_STATSCOMMANDS                RPL_STATSOLINE
        RPL_ENDOFSTATS

Examples:

STATS m                         ; Command to check the command usage
                                for the server you are connected to
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