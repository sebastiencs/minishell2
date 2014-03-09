/*
** my_env_exec.c for minishell in /home/sebastien/travaux/minishell
**
** Made by Sebastien Chapuis
** Login   <sebastien@epitech.net>
**
** Started on  Sat Dec 21 13:18:59 2013 Sebastien Chapuis
** Last update Sun Mar  9 12:56:14 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

int		make_new_cmd(t_cmd *cmd, char **env, t_cmd *new_cmd, int j)
{
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
  return (0);
}

int		exec_with_env(t_cmd *cmd,
			      char **env,
			      int j,
			      int null)
{
  t_cmd		*new_cmd;
  t_pipe	*list_pipe;
  int		status;

  if (cmd->args[j] == NULL)
    return (0);
  if ((new_cmd = (t_cmd*)malloc(sizeof(*new_cmd))) == NULL)
    return (puterror("error: could not alloc\not"));
  if ((make_new_cmd(cmd, env, new_cmd, j)) == -1)
    return (0);
  if ((list_pipe = (t_pipe*)malloc(sizeof(*list_pipe))) == NULL
      || (list_pipe->cmd = (t_cmd**)malloc(sizeof(*cmd) * 2)) == NULL)
    return (puterror("error: could not alloc\not"));
  list_pipe->cmd[1] = NULL;
  list_pipe->cmd[0] = new_cmd;
  list_pipe->nb_cmd_to_wait = 1;
  if ((loop_exec_pipe(1, list_pipe, (null == 1) ? (NULL) : (env), 0)) == - 1)
    return (-1);
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
