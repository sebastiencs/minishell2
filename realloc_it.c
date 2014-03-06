/*
** realloc_it.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar  4 23:09:08 2014 chapui_s
** Last update Wed Mar  5 18:39:49 2014 chapui_s
*/

#include "minish.h"
#include <stdlib.h>

char		*realloc_it(char *dest, char *src)
{
  char		*new_str;
  unsigned int	i;
  unsigned int	j;

  i = 0;
  j = 0;
  while (dest && dest[i])
    i += 1;
  while (src && src[j])
    j += 1;
  if ((new_str = (char*)malloc(i + j + 2)) == NULL)
    return (puterror_null("error: could not alloc\n"));
  i = 0;
  j = 0;
  while (dest && dest[i])
    new_str[i] = dest[i++];
  if (dest)
    new_str[i++] = '\n';
  while (src && src[j])
    new_str[i + j] = src[j++];
  new_str[i + j] = '\0';
  free(dest);
  free(src);
  return (new_str);
}
