3.6 User based queries

	ユーザーとかグループユーザーの詳細情報を知るためのコマンド群
	ワイルドカードを使った場合、使用者が認識可能なユーザーの情報が帰ってくる

	サービスには使えない

   User queries are a group of commands which are primarily concerned
   with finding details on a particular user or group users.  When using
   wildcards with any of these commands, if they match, they will only
   return information on users who are 'visible' to you.  The visibility
   of a user is determined as a combination of the user's mode and the
   common set of channels you are both on.

   Although services SHOULD NOT be using this class of message, they are
   allowed to.