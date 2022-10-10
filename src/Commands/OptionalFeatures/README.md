4. Optional features
	実装する必要はとくにない

	USERHOSTとISONがserviceに使える

   This section describes OPTIONAL messages.  They are not required in a
   working server implementation of the protocol described herein.  In
   the absence of the feature, an error reply message MUST be generated
   or an unknown command error.  If the message is destined for another
   server to answer then it MUST be passed on (elementary parsing
   REQUIRED) The allocated numerics for this are listed with the
   messages below.

   From this section, only the USERHOST and ISON messages are available
   to services.