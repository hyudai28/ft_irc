# 3.5 Service Query and Commands

サービス問い合わせコマンド群は、ネットワークに接続されているあらゆるサービスの情報を返すように設計されています。

このディレクトリには以下のコマンドが含まれます。
 - [Servlist_message](#servlist)
 - [Squery](#squery)


---
## [Servlist message](#servlist)

Command: SERVLIST
```
Parameters: [ <mask> [ <type> ] ]
```

SERVLIST コマンドは、現在ネットワークに接続され、コマンドを発行したユー ザーが見ることができるサービスをリストアップするために使用されます。 
オプションのパラメータを使用すると、クエリーの結果を制限することができます（一致するサービス名とサービスタイプに）。

```
Numeric Replies:
        RPL_SERVLIST                  RPL_SERVLISTEND
```


---
## [Squery](#squery)

Command: SQUERY
```
Parameters: <servicename> <text>
```

SQUERYコマンドはPRIVMSGと同様に使用されます。 
唯一の違いは、受信者がサービスでなければならないことです。 これはテキストメッセージがサービスに配信される唯一の方法です。

返信の詳細と例については、PRIVMSGを参照してください。


Examples:
```
SQUERY irchelp :HELP privmsg;  
ニックネームがirchelpへのサービスからのメッセージ。

SQUERY dict@irc.fr :fr2en blaireau;  
dict@irc.fr.　へのメッセージ
```



---
# 3.5 Service Query and Commands

The service query group of commands has been designed to return
information about any service which is connected to the network.

The following commands correspond to this directory.
 - [Servlist message](#servlist_EN)
 - [Squery](#squery_EN)


---
## [Servlist message](#servlist_EN)

Command: SERVLIST
```
Parameters: [ <mask> [ <type> ] ]
```

The SERVLIST command is used to list services currently connected to
the network and visible to the user issuing the command.  The
optional parameters may be used to restrict the result of the query
(to matching services names, and services type).

```
Numeric Replies:
        RPL_SERVLIST                  RPL_SERVLISTEND
```


---
## [Squery](#squery_EN)

Command: SQUERY
```
Parameters: <servicename> <text>
```

The SQUERY command is used similarly to PRIVMSG.  The only difference
is that the recipient MUST be a service.  This is the only way for a
text message to be delivered to a service.

See PRIVMSG for more details on replies and example.


Examples:
```
SQUERY irchelp :HELP privmsg;  
Message to the service with nickname irchelp.

SQUERY dict@irc.fr :fr2en blaireau;  
Message to the service with name dict@irc.fr.
```