/*
** builtin.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  6 15:50:25 2014 chapui_s
** Last update Sat Mar  8 01:42:07 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

int		is_builtin(char *str)
{
  if (my_strcmp(str, "setenv") == 0
      || my_strcmp(str, "cd") == 0
      || my_strcmp(str, "unsetenv") == 0
      || my_strcmp(str, "exit") == 0
      || my_strcmp(str, "env") == 0)
    return (1);
  return (0);
}

char		*make_path_builtin(char *str)
{
  unsigned int	i;
  char		*path;
  int		size_str;

  i = 0;
  size_str = my_strlen(str);
  if ((path = (char*)malloc(size_str + 1)) == NULL)
    return (NULL);
  while (str[i])
  {
    path[i] = str[i];
    i += 1;
  }
  path[i] = 0;
  return (path);
}

int		do_builtin(t_cmd *cmd,
			   char **environ,
			   t_pipe *list_pipe,
			   int fd_out)
{
  (list_pipe->nb_cmd_to_wait) -= 1;
  if (my_setenv(&environ, "_", cmd->filename) == -1)
    return (-1);
  return ((my_strcmp(cmd->filename, "setenv") == 0) ?
	  (my_setenv(&environ, cmd->args[1], cmd->args[2]))
	  : (my_strcmp(cmd->filename, "unsetenv") == 0) ?
	  (my_unsetenv(&environ, cmd->args[1]))
	  : (my_strcmp(cmd->filename, "env") == 0) ?
	  (my_env(environ, cmd, fd_out))
	  : (my_strcmp(cmd->filename, "cd") == 0) ?
	  (my_cd(cmd->args[1], environ))
	  : (my_strcmp(cmd->filename, "exit") == 0) ?
	  (my_exit(cmd->args[1]))
	  : (0));
}

void		usage_env(void)
{
  my_putstr("Usage: env [OPTION].. [-] [NAME=VALUE].. [COMMAND [ARG]..]\n\n");
  my_putstr("\t-i      start with an empty environment\n");
  my_putstr("\t-0      end all output line with 0 byte rather than newline\n");
  my_putstr("\t-u      remove a variable from the environment\n");
  my_putstr("\t--help  display help\n");
  my_putstr("\nIf no COMMAND, print the resulting environment.\n");
}
