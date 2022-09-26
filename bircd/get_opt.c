
#include <stdio.h>
#include <stdlib.h>
#include "bircd.h"

//ac == 2 port
//ac == 3 port + password
// TODO passwordの条件ある？
void	get_opt(t_env *e, int ac, char **av)
{
  if (ac != 2 && ac != 3)
    {
      fprintf(stderr, USAGE, av[0]);
      exit(1);
    }
  e->port = atoi(av[1]);
}

