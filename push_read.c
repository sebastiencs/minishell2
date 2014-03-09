/*
** list_read.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 18:14:44 2014 chapui_s
** Last update Sun Mar  9 12:57:53 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

int		push_at_place(t_read *tmp, char c, int place)
{
  t_read	*tmp2;
  unsigned int	i;

  i = 0;
  while (tmp->next && i++ < place - 2)
    tmp = tmp->next;
  tmp2 = tmp->next;
  if ((tmp->next = create_read(c)))
  {
    tmp->next->prec = tmp;
    if (tmp2)
    {
      tmp->next->next = tmp2;
      tmp2->prec = tmp->next;
    }
    return (0);
  }
  else
    return (-1);
}

int		push_read(t_read **list, char c, int place)
{
  t_read	*tmp;

  tmp = *list;
  if (*list)
  {
    if (place > 0)
      return (push_at_place(tmp, c, place));
    else
    {
      if ((tmp = create_read(c)))
      {
	tmp->next = *list;
	*list = tmp;
	return (0);
      }
    }
  }
  else
    if ((*list = create_read(c)))
      return (0);
  return (-1);
}
