/*

Command: LUSERS
   Parameters: [ <mask> [ <target> ] ]
LUSERS コマンドは、IRC ネットワークのサイズに関する統計を取るために使用されます。パラメータを指定しない場合は、ネットワーク全体について回答します。

<mask> が指定された場合、そのマスクに一致するサーバによって形成されるネットワークの一部のみに関する返答がある。

最後に、<target> パラメータが指定されると、要求をそのサーバに転送し、そのサーバが応答を生成する。

<target> パラメータにはワイルドカードを使用できます。
   Numeric Replies:

           RPL_LUSERCLIENT                 RPL_LUSEROP
           RPL_LUSERUNKOWN                 RPL_LUSERCHANNELS
           RPL_LUSERME                     ERR_NOSUCHSERVER

*/