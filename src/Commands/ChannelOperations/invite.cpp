/*
3.2.7 Invite message

      Command: INVITE
   Parameters: <nickname> <channel>

	チャンネルに人をインバイトする
	チャンネルが存在する場合、チャンネルの参加者しかインバイトはできない
	チャンネルにinvite-onlyフラグが設定されている場合modしか使えない

   The INVITE command is used to invite a user to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  However, if the channel exists, only members of the channel
   are allowed to invite other users.  When the channel has invite-only
   flag set, only channel operators may issue INVITE command.
*/