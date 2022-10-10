/*
3.7.2 Ping message

      Command: PING
   Parameters: <server1> [ <server2> ]

	アクティブなクライアントとサーバーの存在をテストする。
	サーバーはPINGを、接続先から何も活動が送られていていないとき、一定間隔で送る
	もし接続がPINGに対して、一定時間内に返答できなかった場合コネクションはクローズされる

	PINGが受け取られた後、適切なPONGメッセージが<server1>への返答として送られなければならない
	もし<server2>が指定されている場合、それはpingのtargetを指していて、
	メッセージはそこに向かう

   The PING command is used to test the presence of an active client or
   server at the other end of the connection.  Servers send a PING
   message at regular intervals if no other activity detected coming
   from a connection.  If a connection fails to respond to a PING
   message within a set amount of time, that connection is closed.  A
   PING message MAY be sent even if the connection is active.

   When a PING message is received, the appropriate PONG message MUST be
   sent as reply to <server1> (server which sent the PING message out)
   as soon as possible.  If the <server2> parameter is specified, it
   represents the target of the ping, and the message gets forwarded
   there.

   Numeric Replies:

           ERR_NOORIGIN                  ERR_NOSUCHSERVER

   Examples:

   PING tolsun.oulu.fi             ; Command to send a PING message to
                                   server

   PING WiZ tolsun.oulu.fi         ; Command from WiZ to send a PING
                                   message to server "tolsun.oulu.fi"

   PING :irc.funet.fi              ; Ping message sent by server
                                   "irc.funet.fi"
*/