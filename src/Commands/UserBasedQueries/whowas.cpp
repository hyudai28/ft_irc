/*
      Command: WHOWAS
   Parameters: <nickname> *( "," <nickname> ) [ <count> [ <target> ] ]

	もう存在しないニックネームの情報を取得する
	nicknameを変えた場合、IRCを去った場合の二つの状況がある
	クエリーに反応するため、サーバーはnickname historyを検索する
	historyは逆順にサーチされ、近い順から返していく
	複数マッチした場合は<count>も帰ってくる
	もし正の値が帰って来なくなったらfull searchが終わったってこと

	targetにwildcard使用可能

   Whowas asks for information about a nickname which no longer exists.
   This may either be due to a nickname change or the user leaving IRC.
   In response to this query, the server searches through its nickname
   history, looking for any nicks which are lexically the same (no wild
   card matching here).  The history is searched backward, returning the
   most recent entry first.  If there are multiple entries, up to
   <count> replies will be returned (or all of them if no <count>
   parameter is given).  If a non-positive number is passed as being
   <count>, then a full search is done.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

           ERR_NONICKNAMEGIVEN           ERR_WASNOSUCHNICK
           RPL_WHOWASUSER                RPL_WHOISSERVER
           RPL_ENDOFWHOWAS

   Examples:

   WHOWAS Wiz                      ; return all information in the nick
                                   history about nick "WiZ";

   WHOWAS Mermaid 9                ; return at most, the 9 most recent
                                   entries in the nick history for
                                   "Mermaid";

   WHOWAS Trillian 1 *.edu         ; return the most recent history for
                                   "Trillian" from the first server
                                   found to match "*.edu".

*/
