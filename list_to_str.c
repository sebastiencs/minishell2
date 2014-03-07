/*
** list_to_str.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 18:09:44 2014 chapui_s
** Last update Fri Mar  7 21:03:45 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

static char	*clean_str_begin_end(char *str)
{
  unsigned int	i;

  while (str[0] == ' ' && str[1])
  {
    i = 0;
    while (str[i])
    {
      str[i] = str[i + 1];
      i += 1;
    }
  }
  i = 0;
  while (str[i])
    i += 1;
  if (i > 0 && str[i - 1] == ' ')
    str[i - 1] = 0;
  return (str);
}

char		*clean_str(char *str)
{
  unsigned int	i;
  unsigned int	j;

  i = 0;
  while (str[i])
  {
    j = i;
    if (str[i] && str[i] == ' ' && str[i + 1] == ' ')
    {
      while (str[j])
      {
	str[j] = str[j + 1];
	j += 1;
      }
      i -= 1;
    }
    i += 1;
  }
  str = clean_str_begin_end(str);
  return (str);
}

char		*list_to_str(t_read *list_read, int is_clean)
{
  char		*str;
  t_read	*tmp;
  int		i;

  i = 0;
  tmp = list_read;
  if ((str = (char*)malloc(get_size_list(list_read) + 1)) == NULL)
    return (puterror_null("error: could not alloc\n"));
  while (tmp)
  {
    str[i] = tmp->c;
    i += 1;
    tmp = tmp->next;
  }
  str[i] = 0;
  if (is_clean == 1)
    str = clean_str(str);
  return (str);
}
