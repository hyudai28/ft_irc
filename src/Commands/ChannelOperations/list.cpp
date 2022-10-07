////////
// 3.2.6 List message
//       Command: LIST
//    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
//    The list command is used to list channels and their topics.  If the
//    <channel> parameter is used, only the status of that channel is
//    displayed.

//   チャンネル群の名前と、そのtopicを表示
//   引数でチャンネルが指定されているなら、そのチャンネルについてだけの情報を表示。

//    If the <target> parameter is specified, the request is forwarded to
//    that server which will generate the reply.
//    targetが指定されているならリクエストはtargetのサーバーに対して行われる
//    targetでwildcardsを使えます

//    Numeric Replies:
//            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
//            RPL_LIST                        RPL_LISTEND

//    Examples:

//    LIST                            ; Command to list all channels.

//    LIST #twilight_zone,#42         ; Command to list channels
//                                    #twilight_zone and #42

////////