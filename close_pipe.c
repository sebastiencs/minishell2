/*
** close_pipe.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 18:56:40 2014 chapui_s
** Last update Sun Mar  9 12:57:38 2014 chapui_s
*/

#include <unistd.h>
#include "minish.h"

void		close_pipe(t_pipe *list_pipe, int nb_cmd_pipe)
{
  unsigned int	i;

  i = 0;
  while (i < 2 * (nb_cmd_pipe - 1))
  {
    close(list_pipe->list_fd[i]);
    i += 1;
  }
}
