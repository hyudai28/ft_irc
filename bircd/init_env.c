#include <stdlib.h>
#include <sys/resource.h>
#include "bircd.h"

//　env構造体に　ファイル上限数、maxfd、fdsを書き込む

void		init_env(t_env *env)
{
  int		i;
  struct rlimit	rlp;

//　RLIMIT_NOFILE 開けるファイルの数 + 1　制限をかける
//　x でやってること　＝　関数がエラー値だったらexitしてる
  X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");
//　TODO maxfdはどこで使うのか？何が７なのか
  env->maxfd = rlp.rlim_cur;
  env->fds = (t_fd*)Xv(NULL, malloc(sizeof(*env->fds) * env->maxfd), "malloc");
  i = 0;
  while (i < env->maxfd)
    {
      clean_fd(&env->fds[i]);
      i++;
    }
}