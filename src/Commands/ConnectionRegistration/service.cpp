/*
3.1.6 Service message

      Command: SERVICE
   Parameters: <nickname> <reserved> <distribution> <type>
               <reserved> <info>

	SERVICEコマンドは新しいサービスを登録するときに使う。
	引数でサービスの、nickname, ditribution, type, infoを指定する。
	<distribution>引数はサービスの可視性を指定する。
	サーバーの名前と引数がマッチングしたときだけサービス対象になる。
	サービス対象のサーバーがサービスを知るため、サーバーと、サービスが登録されている
	サーバーとのネットワークパスはマスクに一致するサーバーで構成されてなければいけない。

	<type>は将来的に使う予定だけど今は特に使われてない。

   The SERVICE command to register a new service.  Command parameters
   specify the service nickname, distribution, type and info of a new
   service.

   The <distribution> parameter is used to specify the visibility of a
   service.  The service may only be known to servers which have a name
   matching the distribution.  For a matching server to have knowledge
   of the service, the network path between that server and the server
   on which the service is connected MUST be composed of servers which
   names all match the mask.

   The <type> parameter is currently reserved for future usage.

   Numeric Replies:

           ERR_ALREADYREGISTRED            ERR_NEEDMOREPARAMS
           ERR_ERRONEUSNICKNAME
           RPL_YOURESERVICE                RPL_YOURHOST
           RPL_MYINFO

   Example:

   SERVICE dict * *.fr 0 0 :French Dictionary ; Service registering
                                   itself with a name of "dict".  This
                                   service will only be available on
                                   servers which name matches "*.fr".

*/