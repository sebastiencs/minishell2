/*
** my_env_exec.c for minishell in /home/sebastien/travaux/minishell
**
** Made by Sebastien Chapuis
** Login   <sebastien@epitech.net>
**
** Started on  Sat Dec 21 13:18:59 2013 Sebastien Chapuis
** Last update Fri Mar  7 12:59:42 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

int	exec_env_null(t_cmd *cmd, int j)
{
  t_cmd	*new_cmd;
  char	*str;
  int	i;

  i = 0;
  /* if (cmd->args[j] == NULL) */
  /*   return (0); */
  /* if ((str = cmd_to_str(cmd, j)) == NULL) */
  /*   return (-1); */
  /* if ((new_cmd = str_to_cmd(str, NULL)) == NULL) */
  /*   return (-1); */
  /* if ((exec_it(new_cmd, NULL, NULL, str)) == -2) */
  /*   return (-2); */
  return (0);
}

void		putstr_fd(char *str, int fd)
{
  while (str && *str)
    write(fd, str++, 1);
}

int		disp_env(char **env, t_env *options, t_cmd *cmd)
{
  t_pipe	*list_pipe;
  int		fd_to_close;
  int		pid;
  int		status;
  int		i;

  i = 0;
  if (env == NULL)
    return ;
  if ((list_pipe = (t_pipe*)malloc(sizeof(*list_pipe))) == NULL
      || (list_pipe->cmd = (t_cmd**)malloc(sizeof(t_cmd*) * 2)) == NULL)
    return (puterror("error : could not alloc\n"));
  list_pipe->cmd[0] = cmd;
  list_pipe->cmd[1] = NULL;

  if ((pid = fork()) == 0)
  {

    fd_to_close = do_redirections(list_pipe, 0, env, 0);

    while (env[i])
    {
      putstr_fd(env[i], 1);
      if (options->zero == 0)
	putstr_fd("\n", 1);
      /* my_putstr(env[i]); */
      /* if (options->zero == 0) */
      /*   write(fd_tty, "\n", 1); */
      i = i + 1;
    }
    close(fd_to_close);
    free(list_pipe->cmd);
    free(list_pipe);
    exit(0);
  }
  else if (pid > 0)
  {
    wait(status);
  }

}
int		exec_with_env(t_cmd *cmd, char **env, int j)
{
  t_cmd		*new_cmd;
  t_pipe	*list_pipe;
  char		*str;
  int		i;
  int		status;

  i = 0;
  if (cmd->args[j] == NULL)
    return (0);
  if ((new_cmd = (t_cmd*)malloc(sizeof(*new_cmd))) == NULL)
    return (puterror("error: could not alloc\not"));
  new_cmd->filename = cmd->args[j];
  new_cmd->args = &(cmd->args[j]);
  new_cmd->cmd_path = find_cmd(new_cmd->args[0], env, 0, NULL);
  if (new_cmd->cmd_path == NULL
      && (cmd_null(new_cmd, new_cmd->filename)) == -1)
    return (-1);
  new_cmd->is_redi_right = cmd->is_redi_right;
  new_cmd->redi_right = cmd->redi_right;
  new_cmd->is_redi_left = cmd->is_redi_left;
  new_cmd->redi_left = cmd->redi_left;
  if ((list_pipe = (t_pipe*)malloc(sizeof(*list_pipe))) == NULL
      || (list_pipe->cmd = (t_cmd**)malloc(sizeof(*cmd) * 2)) == NULL)
    return (puterror("error: could not alloc\not"));
  list_pipe->cmd[1] = NULL;
  list_pipe->cmd[0] = new_cmd;
  list_pipe->nb_cmd_to_wait = 1;
  loop_exec_pipe(1, list_pipe, env, 0);
  wait_proc(1, &status, NULL, list_pipe);
  free(new_cmd);
  free(list_pipe);
  return (0);
}

int	prepare_setenv(char ***env, char *str)
{
  char	*left;
  char	*right;

  if ((left = left_egale(str)) == NULL)
    return (-1);
  if ((right = right_egale(str)) == NULL)
    return (-1);
  if ((my_setenv(env, left, right)) == -1)
    return (-1);
  free(left);
  free(right);
  return (0);
}
