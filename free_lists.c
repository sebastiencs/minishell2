/*
** free_lists.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 17:32:50 2014 chapui_s
** Last update Sat Mar  8 17:32:55 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

void		free_list_str_pipe(t_pipe *list_pipe, char **str_pipe)
{
  unsigned int	i;

  i = 0;
  free(list_pipe->status);
  free(list_pipe->list_in);
  free(list_pipe->list_out);
  free(list_pipe->list_fd);
  while (list_pipe->cmd[i])
  {
    free(list_pipe->cmd[i]->filename);
    free(list_pipe->cmd[i++]);
  }
  free(list_pipe->cmd[i]);
  free(list_pipe->cmd);
  free(list_pipe);
  i = 0;
  while (str_pipe[i])
    free(str_pipe[i++]);
  free(str_pipe[i]);
  free(str_pipe);
}

void		free_str_tab(char **str_tab)
{
  unsigned int	i;

  i = 0;
  while (str_tab[i])
    free(str_tab[i++]);
  free(str_tab[i]);
  free(str_tab);
}
