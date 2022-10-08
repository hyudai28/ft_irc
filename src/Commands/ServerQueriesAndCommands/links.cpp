/*

   Command: LINKS
Parameters: [ [ <remote server> ] <server mask> ]

LINKSを使うと、ユーザーは、問い合わせに答えるサーバーが知っている すべてのサーバー名をリストアップすることができます。 返されるサーバーのリストはマスクと一致しなければならず、マスクが与えられていない場合は完全なリストが返される。

<server mask> に加えて <remote server> が指定された場合、LINKS コマンドはその名前にマッチする最初のサーバに転送され、そのサーバは問い合わせに応答することが要求される。

Numeric Replies:

     ERR_NOSUCHSERVER
     RPL_LINKS                        RPL_ENDOFLINKS

Examples:

LINKS *.au                      ;  
サーバ名が*.auに一致するサーバをすべてリストアップするコマンドです。

LINKS *.edu *.bu.edu            ;  
*.bu.eduに一致するサーバーを、*.eduに一致する最初のサーバーから見た状態でリストアップするコマンドです。

*/