/*
** builtins_complem.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  6 19:09:45 2014 chapui_s
** Last update Sun Mar  9 12:53:18 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

char		*left_egale(char *str)
{
  int		i;
  char		*new_str;
  int		size_str;

  i = 0;
  size_str = 0;
  while (str && str[size_str] && str[size_str] != '=')
    size_str = size_str + 1;
  if ((new_str = (char*)malloc(size_str +1)) == NULL)
    return (NULL);
  while (i < size_str)
  {
    new_str[i] = str[i];
    i = i + 1;
  }
  new_str[i] = 0;
  return (new_str);
}

char		*right_egale(char *str)
{
  int		i;
  char		*new_str;
  int		size_str;

  i = 0;
  size_str = 0;
  while (str && str[i] != '=')
    i = i + 1;
  i = i + 1;
  while (str[i + size_str])
    size_str = size_str + 1;
  if ((new_str = (char*)malloc(size_str + 1)) == NULL)
    return (NULL);
  size_str = 0;
  while (str[i + size_str])
  {
    new_str[size_str] = str[i + size_str];
    size_str = size_str + 1;
  }
  new_str[size_str] = 0;
  return (new_str);
}

int		my_exit(char *str)
{
  unsigned char	num_exit;
  int		i;

  i = 0;
  my_putstr("exit\n");
  if (str == NULL || my_strcmp(str, "0") == 0)
    return (-3);
  while (str && str[i])
  {
    if (!((str[i] >= '0' && str[i] <= '9')) && str[i] != '-')
    {
      puterror("exit: argument numeric necessary\n");
      return (255);
    }
    i = i + 1;
  }
  num_exit = (unsigned char)my_atoi(str);
  return (num_exit);
}
