/*
** my_strchr.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  6 16:03:06 2014 chapui_s
** Last update Thu Mar  6 16:03:08 2014 chapui_s
*/

#include <stdlib.h>

char	*my_strchr(char *s, int c)
{
  int	i;

  i = 0;
  while (s[i])
  {
    if (s[i] == c)
      return (s + i);
    i = i + 1;
  }
  return (NULL);
}
