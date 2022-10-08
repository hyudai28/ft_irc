/*
   Command: ADMIN
Parameters: [ <target> ]

admin コマンドは、指定されたサーバー、または <target> パラメーターが省略された場合は現在のサーバーの管理者についての情報を検索するために使用されます。 各サーバーは、ADMIN メッセージを他のサーバーに転送する機能を持たなければなりません（MUST）。
<target> パラメータにはワイルドカードを使用できます。


Numeric Replies:

        ERR_NOSUCHSERVER
        RPL_ADMINME                   RPL_ADMINLOC1
        RPL_ADMINLOC2                 RPL_ADMINEMAIL

Examples:
ADMIN tolsun.oulu.fi            ; 
tolsun.oulu.fiからADMIN返信を要求する。

ADMIN syrk                      ; 
ユーザーsyrkが接続しているサーバーへのADMINリクエスト


*/