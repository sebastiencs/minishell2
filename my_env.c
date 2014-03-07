/*
** my_env.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  6 16:07:26 2014 chapui_s
** Last update Fri Mar  7 12:58:22 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

int	is_env(char *str, t_cmd *cmd, int i)
{
  if (my_strcmp(str, "env") == 0
      || my_strcmp(str, "-i") == 0
      || my_strcmp(str, "-0") == 0
      || my_strcmp(str, "-u") == 0
      || my_strcmp(str, "--help") == 0
      || my_strchr(str, '=') != NULL)
    return (1);
  if (my_strcmp(cmd->args[i - 1], "-u") == 0)
    return (1);
  return (0);
}

int	get_env_option(t_cmd *cmd, t_env *options_env)
{
  int	i;

  i = 0;
  while (cmd && cmd->args[i] && is_env(cmd->args[i], cmd, i) == 1)
  {
    (my_strcmp(cmd->args[i], "-i") == 0) ? (options_env->i = 1) : (0);
    (my_strcmp(cmd->args[i], "-0") == 0) ? (options_env->zero = 1) : (0);
    if (my_strcmp(cmd->args[i], "-u") == 0)
    {
      options_env->u = 1;
      if (cmd->args[i + 1] == NULL)
      {
	puterror("option -u need an argument\nPlease read --help\n");
	return (0);
      }
    }
    else if (my_strcmp(cmd->args[i], "--help") == 0)
    {
      usage_env();
      return (0);
    }
    i = i + 1;
  }
  return (i);
}

char	**dup_env(char **env)
{
  char	**new_env;
  int	i;

  i = 0;
  if (env == NULL)
    return (NULL);
  while (env[i])
    i = i + 1;
  if ((new_env = (char**)malloc(sizeof(char*) * i + 1)) == NULL)
    return (NULL);
  i = 0;
  while (env[i])
  {
    new_env[i] = env[i];
    i = i + 1;
  }
  new_env[i] = NULL;
  return (new_env);
}

int	exec_my_env(char **env, t_env *options, t_cmd *cmd, int j)
{
  int	i;

  i = 0;
  while (cmd && cmd->args[i] && i < j)
  {
    if (my_strcmp(cmd->args[i], "-i") == 0)
      return (exec_env_null(cmd, j));
    else if (my_strchr(cmd->args[i], '=') != NULL)
      prepare_setenv(&env, cmd->args[i]);
    else if (my_strcmp(cmd->args[i], "-u") == 0)
      my_unsetenv(&env, cmd->args[i + 1]);
    i = i + 1;
  }
  if (cmd->args[j] == NULL)
    disp_env(env, options, cmd);
  else if (options->zero == 0)
    exec_with_env(cmd, env, j);
  else
    puterror("env: Cannot indicate NULL with a command\nPlease read --help\n");
  free(env);
  return (0);
}

int	my_env(char **env, t_cmd *cmd, int fd_out)
{
  t_env	options_env;
  char	**new_env;
  int	fd_tty_save;
  int	ret_exec_env;
  int	j;

  fd_tty_save = fd_tty;
  fd_tty = fd_out;
  if (cmd == NULL)
    return (0);
  if ((new_env = dup_env(env)) == NULL)
    return (-1);
  options_env.i = 0;
  options_env.u = 0;
  options_env.zero = 0;
  if ((j = get_env_option(cmd, &options_env)) == 0)
    return (0);
  ret_exec_env = exec_my_env(new_env, &options_env, cmd, j);
  fd_tty = fd_tty_save;
  return (ret_exec_env);
}
