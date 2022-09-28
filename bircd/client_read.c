#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

# include <stdio.h>

void	client_read(t_env *e, int cs)
{
  int	r;
  int	i;

  r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
  printf("%s", e->fds[cs].buf_read);
  for (int i=0; e->fds[cs].buf_read[i] != '\0'; i++)
  {
    if (e->fds[cs].buf_read[i + 1] == '\0')
    {
      printf("[%3d]", e->fds[cs].buf_read[i]);
      break ;
    }
    printf("[%3d]", e->fds[cs].buf_read[i]);
  }
  printf("\n");
  for (int i=0; e->fds[cs].buf_read[i] != '\0'; i++)
  {
    if (e->fds[cs].buf_read[i] == 13)
      printf("[ CR]");
    else if (e->fds[cs].buf_read[i] == 10)
      printf("[ LF]");
    else
      printf("[ %c ]", e->fds[cs].buf_read[i]);
  }
  printf("\n\n");

  if (r <= 0)
    {
      close(cs);
      clean_fd(&e->fds[cs]);
      printf("client #%d gone away\n", cs);
    }
  else
    {
      i = 0;
      while (i < e->maxfd)
	{
	  if ((e->fds[i].type == FD_CLIENT) &&
	      (i != cs))
	    send(i, e->fds[cs].buf_read, r, 0);
	  i++;
	}
    }
}
