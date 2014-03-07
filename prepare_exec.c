/*
** prepare_exec.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar  7 19:39:21 2014 chapui_s
** Last update Fri Mar  7 20:45:52 2014 chapui_s
*/

#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

int		get_nb_cmd_pipe(char *str)
{
  int		nb;
  int		i;

  nb = 1;
  i = 0;
  while (str && str[i])
  {
    if (str[i] == '|')
      nb += 1;
    i += 1;
  }
  return (nb);
}

int		prepare_pipe(int nb_cmd_pipe,
			     int *list_in,
			     int *list_out,
			     int *list_fd)
{
  unsigned int	i;
  unsigned int	j;
  int		fd[2];

  i = 0;
  while (i < nb_cmd_pipe)
  {
    list_out[i] = -1;
    list_in[i] = -1;
    i += 1;
  }
  i = 0;
  j = 0;
  while (i < nb_cmd_pipe - 1)
  {
    if ((pipe(fd)) == -1)
      return (puterror("error: pipe\n"));
    list_out[i] = fd[1];
    list_in[i + 1] = fd[0];
    list_fd[j] = fd[0];
    list_fd[j + 1] = fd[1];
    i += 1;
    j += 2;
  }
  return (0);
}

static void	init_status(int *status, int nb_cmd_pipe)
{
  unsigned int	i;

  i = 0;
  while (i < nb_cmd_pipe)
  {
    status[i] = 0;
    i += 1;
  }
}

t_pipe		*malloc_pipe_struct(t_pipe *list_pipe,
				    int nb_cmd_pipe,
				    char **str_pipe,
				    char **env)
{
  unsigned int	i;

  i = 0;
  while (str_pipe[i])
    i += 1;
  if ((list_pipe->status = (int*)malloc(sizeof(int) * nb_cmd_pipe)) == NULL
      || (list_pipe->list_in = (int*)malloc(sizeof(int) * nb_cmd_pipe)) == NULL
      || (list_pipe->list_out
	  = (int*)malloc(sizeof(int) * nb_cmd_pipe)) == NULL
      || (list_pipe->list_fd
	  = (int*)malloc(sizeof(int) * ((nb_cmd_pipe - 1) * 2))) == NULL
      || (list_pipe->cmd = (t_cmd**)malloc(sizeof(t_cmd*) * (i + 1))) == NULL)
    return (puterror_null("error: could not alloc\n"));
  i = 0;
  init_status(list_pipe->status, nb_cmd_pipe);
  while (str_pipe[i])
  {
    if ((list_pipe->cmd[i] = str_to_cmd(str_pipe[i], env)) == NULL)
      return (NULL);
    i += 1;
  }
  list_pipe->cmd[i] = NULL;
  return (list_pipe);
}

int		find_all_cmd(char **str_pipe, t_pipe *list_pipe)
{
  unsigned int	i;

  i = 0;
  while (str_pipe[i])
  {
    if (list_pipe->cmd[i]->cmd_path == NULL
	&& (cmd_null(list_pipe->cmd[i], str_pipe[i])) == -1)
      return (0);
    i += 1;
  }
  return (1);
}
