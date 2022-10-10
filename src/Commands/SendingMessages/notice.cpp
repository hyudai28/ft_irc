/*
3.3.2 Notice

      Command: NOTICE
   Parameters: <msgtarget> <text>

	NOTICEはPRIVMSGに似ている
	違いはNOTICEには自動返答が使えないこと
	これはサーバーにも適応できて、NOTICEにはエラーリターンをしない
	これは自動応答のループを避けるため

	このコマンドはサービスでも使える

	サービスとかボットによく使われる

   The NOTICE command is used similarly to PRIVMSG.  The difference
   between NOTICE and PRIVMSG is that automatic replies MUST NEVER be
   sent in response to a NOTICE message.  This rule applies to servers

   too - they MUST NOT send any error reply back to the client on
   receipt of a notice.  The object of this rule is to avoid loops
   between clients automatically sending something in response to
   something it received.

   This command is available to services as well as users.

   This is typically used by services, and automatons (clients with
   either an AI or other interactive program controlling their actions).

   See PRIVMSG for more details on replies and examples.
*/
