/*
** my_env_disp.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar  7 18:47:06 2014 chapui_s
** Last update Sun Mar  9 12:58:43 2014 chapui_s
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minish.h"

void		putstr_fd(char *str, int fd)
{
  while (str && *str)
    write(fd, str++, 1);
}

void		disp_env_son(t_pipe *list_pipe,
			     t_env *options,
			     char **env,
			     t_cmd *cmd)
{
  int		fd;
  int		i;

  i = 0;
  fd = do_redirections(list_pipe, 0, env, 0);
  while (env[i])
  {
    if (cmd->is_redi_right != 0)
    {
      putstr_fd(env[i], 1);
      if (options->zero == 0)
	putstr_fd("\n", 1);
    }
    else
    {
      my_putstr(env[i]);
      if (options->zero == 0)
	my_putstr("\n");
    }
    i = i + 1;
  }
  close(fd);
  free(list_pipe->cmd);
  free(list_pipe);
  exit(0);
}

int		disp_env(char **env, t_env *options, t_cmd *cmd)
{
  t_pipe	*list_pipe;
  int		pid;
  int		status;

  status = 0;
  if ((list_pipe = (t_pipe*)malloc(sizeof(*list_pipe))) == NULL
      || (list_pipe->cmd = (t_cmd**)malloc(sizeof(t_cmd*) * 2)) == NULL)
    return (puterror("error : could not alloc\n"));
  list_pipe->cmd[0] = cmd;
  list_pipe->cmd[1] = NULL;
  if ((pid = fork()) == 0)
    disp_env_son(list_pipe, options, env, cmd);
  else if (pid > 0)
    wait(&status);
  else if (pid == -1)
    return (my_putstr("error: fork\n"));
  free(list_pipe->cmd);
  free(list_pipe);
  return (0);
}
