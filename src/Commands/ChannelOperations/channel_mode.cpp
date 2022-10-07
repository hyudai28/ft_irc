
/*
3.2.3 Channel mode message

      Command: MODE
   Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

	MODEコマンドはチャンネルのモードを編集するためにある。
	RFCの"Internet Relay Chat: Channel Management"にもっと情報が書いてあるよ
	このコマンドで送れる編集できる箇所は3個だけ

   The MODE command is provided so that users may query and change the
   characteristics of a channel.  For more details on available modes
   and their uses, see "Internet Relay Chat: Channel Management" [IRC-
   CHAN].  Note that there is a maximum limit of three (3) changes per
   command for modes that take a parameter.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_KEYSET
           ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
           ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
           RPL_CHANNELMODEIS
           RPL_BANLIST                     RPL_ENDOFBANLIST
           RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
           RPL_INVITELIST                  RPL_ENDOFINVITELIST
           RPL_UNIQOPIS

	この続きの例文はMODEコマンドを理解するためにあるけど、IRC-CHANをみた方がいいよ
   The following examples are given to help understanding the syntax of
   the MODE command, but refer to modes defined in "Internet Relay Chat:
   Channel Management" [IRC-CHAN].

   Examples:

	invite-onlyの＃Finnishチャンネルを作り、
	ホストネームに*.fiがつく人を自動招待する
   MODE #Finnish +imI *!*@*.fi     ; Command to make #Finnish channel
                                   moderated and 'invite-only' with user
                                   with a hostname matching *.fi
                                   automatically invited.

	#Finnishでのchanop権限をKilroyをあげる
   MODE #Finnish +o Kilroy         ; Command to give 'chanop' privileges
                                   to Kilroy on channel #Finnish.

	Wizくんがspeakできるようにする
   MODE #Finnish +v Wiz            ; Command to allow WiZ to speak on
                                   #Finnish.
	#Finsチャンネルからsecretフラッグを取り除く
   MODE #Fins -s                   ; Command to remove 'secret' flag
                                   from channel #Fins.

	"oulu"をチャンネルのkeyとしてセット
   MODE #42 +k oulu                ; Command to set the channel key to
                                   "oulu".

	"oulu"をチャンネルのkeyから解除
   MODE #42 -k oulu                ; Command to remove the "oulu"
                                   channel key on channel "#42".
	
	#eu-opers"の参加人数上限を１０人にセット
	MODE #eu-opers +l 10            ; Command to set the limit for the
                                   number of users on channel
                                   "#eu-opers" to 10.

	ユーザーのWizが#eu-opers"の参加人数上限を削除
   :WiZ!jto@tolsun.oulu.fi MODE #eu-opers -l
                                   ; User "WiZ" removing the limit for
                                   the number of users on channel "#eu-
                                   opers".

	&ouluにセットされたban masksをリスト表示する
   MODE &oulu +b                   ; Command to list ban masks set for
                                   the channel "&oulu".

	&ouluに誰も参加できなくする
   MODE &oulu +b *!*@*             ; Command to prevent all users from
                                   joining.

	&ouluに.eduをホストネームとして持つ人を参加不能にする、.bu.eduは例外でok
   MODE &oulu +b *!*@*.edu +e *!*@*.bu.edu
                                   ; Command to prevent any user from a
                                   hostname matching *.edu from joining,
                                   except if matching *.bu.edu

	#buに*.eduがマッチする人を参加不能に、*.bu..eduは例外でok
   MODE #bu +be *!*@*.edu *!*@*.bu.edu
                                   ; Comment to prevent any user from a
                                   hostname matching *.edu from joining,
                                   except if matching *.bu.edu

	#meditationチャンネルに設定されたexception masksをリスト表示
   MODE #meditation e              ; Command to list exception masks set
                                   for the channel "#meditation".

	#meditationのinvitationマスクをリスト表示
   MODE #meditation I              ; Command to list invitations masks
                                   set for the channel "#meditation".
	#!12345ircd"チャンネルの解説者を表示する
   MODE !12345ircd O               ; Command to ask who the channel
                                   creator for "!12345ircd" is
*/