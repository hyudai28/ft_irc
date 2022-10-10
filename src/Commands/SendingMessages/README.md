3.3 Sending messages

	PRIVMSGとNOTICEとSQUERYがIRCに置ける唯一のメッセージ伝達手段だ
	残りのコマンドはそれをどう実現させるかにしかすぎない

   The main purpose of the IRC protocol is to provide a base for clients
   to communicate with each other.  PRIVMSG, NOTICE and SQUERY
   (described in Section 3.5 on Service Query and Commands) are the only
   messages available which actually perform delivery of a text message
   from one client to another - the rest just make it possible and try
   to ensure it happens in a reliable and structured manner.