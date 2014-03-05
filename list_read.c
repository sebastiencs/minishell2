/*
** list_read.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 18:14:44 2014 chapui_s
** Last update Wed Feb 26 14:57:59 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

static t_read	*create_read(char c)
{
  t_read	*new;

  new = NULL;
  if ((new = (t_read*)malloc(sizeof(*new))))
  {
    new->c = c;
    new->is_current = 0;
    new->prec = NULL;
    new->next = NULL;
  }
  return (new);
}

int		push_read(t_read **list, char c, int place)
{
  t_read	*tmp;
  t_read	*tmp2;
  int		i;

  i = 0;
  tmp = *list;
  if (*list)
  {
    if (place > 0)
    {
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
    }
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
  puterror("error -> could not alloc\n");
  return (-1);
}

void		rm_in_list(t_read **list, int nb)
{
  t_read	*tmp;
  int		i;

  i = 0;
  tmp = *list;
  if (tmp == NULL)
    return ;
  if (nb == 0)
  {
    if (tmp->next)
    {
      tmp = tmp->next;
      free(tmp->prec);
      tmp->prec = NULL;
      *list = tmp;
    }
    else if (tmp)
    {
      free(tmp);
      *list = NULL;
    }
    return ;
  }
  while (i++ < nb && tmp)
    tmp = tmp->next;
  if (tmp == NULL)
    return ;
  tmp->prec->next = tmp->next;
  if (tmp->next)
    tmp->next->prec = tmp->prec;
  free(tmp);
}

int		get_size_list(t_read *list)
{
  t_read	*tmp;
  int		size;

  size = 0;
  tmp = list;
  while (tmp)
  {
    tmp = tmp->next;
    size += 1;
  }
  return (size);
}
