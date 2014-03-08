/*
** utils2.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar  3 15:01:21 2014 chapui_s
** Last update Sat Mar  8 17:44:09 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

int		is_only_spaces(char *str)
{
  int		i;

  i = 0;
  while (str && str[i])
  {
    if (str[i] != ' ')
      return (0);
    i += 1;
  }
  return (1);
}

static int	is_one_backlash_n(char *str)
{
  unsigned int	i;

  i = 0;
  while (str && str[i])
  {
    if (str[i] == '\n')
      return (1);
    i += 1;
  }
  return (0);
}

int		is_good_string_redi(char *str, char *good_string)
{
  unsigned int	i;
  unsigned int	j;

  i = 0;
  if (str == NULL || is_one_backlash_n(str) == 0
      || my_strcmp("\n", str) == 0)
    return (0);
  while (str[i])
    i += 1;
  i -= 2;
  while (i > 0 && str[i] != '\n')
    i -= 1;
  i += 1;
  j = 0;
  while (str[i + j] && str[i + j] == good_string[j])
    j += 1;
  if (good_string[j] == '\0')
    return (1);
  return (0);
}

char		*rm_good_string(char *str)
{
  unsigned int	i;

  i = 0;
  while (str[i])
    i += 1;
  i -= 2;
  while (str[i] != '\n')
    i -= 1;
  i += 1;
  while (str[i])
  {
    str[i] = '\0';
    i += 1;
  }
  return (str);
}

int		cmd_null(t_cmd *cmd, char *str)
{
  if (str && str[0] != '\0' && is_only_spaces(str) == 0)
  {
    puterror("Cannot find the command '");
    if (cmd && cmd->args)
      puterror(cmd->args[0]);
    puterror("'...\n");
  }
  return (-1);
}
