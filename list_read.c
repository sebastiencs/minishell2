/*
** list_read.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 18:14:44 2014 chapui_s
** Last update Sun Mar  9 12:45:29 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

t_read		*create_read(char c)
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
  else
    puterror("error: could not alloc\n");
  return (new);
}

static int	rm_begin(t_read **list)
{
  t_read	*tmp;

  tmp = *list;
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
  return (0);
}

int		rm_in_list(t_read **list, int nb)
{
  t_read	*tmp;
  int		i;

  i = 0;
  tmp = *list;
  if (tmp == NULL)
    return (0);
  if (nb == 0)
    return (rm_begin(list));
  while (i++ < nb && tmp)
    tmp = tmp->next;
  if (tmp == NULL)
    return (0);
  tmp->prec->next = tmp->next;
  if (tmp->next)
    tmp->next->prec = tmp->prec;
  free(tmp);
  return (0);
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
