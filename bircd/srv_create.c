
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include "bircd.h"

void			srv_create(t_env *e, int port)
{
  int			s;
  struct sockaddr_in	sin;
  struct protoent	*pe;

 //getprotobyname("tcp"):データベースからtcpのエントリーを取ってきてる
 // TODO エントリーってなんだよ
  pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname");
  //socket通信のエンドポイントを作成,通信方式としてはSOCK_STREAM
  s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
  //アドレスファミリーによってソケット API で使用するアドレス構造の形式が決まる
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);
  X(-1, bind(s, (struct sockaddr*)&sin, sizeof(sin)), "bind");
  X(-1, listen(s, 42), "listen");
  e->fds[s].type = FD_SERV;
  e->fds[s].fct_read = srv_accept;
}
