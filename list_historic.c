/*
** list_historic.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 11:19:34 2014 chapui_s
** Last update Sat Mar  8 14:36:26 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

static t_historic	*create_hist(t_read *list_read)
{
  t_historic		*new;

  if ((new = (t_historic*)malloc(sizeof(*new))) != NULL)
  {
    new->list_read = list_read;
    new->is_cur = 0;
    new->prec = NULL;
    new->next = NULL;
  }
  else
    puterror("error: could not alloc\n");
  return (new);
}

int			push_historic(t_historic **historic,
				      t_read *list_read)
{
  t_historic		*tmp;

  tmp = *historic;
  if (tmp)
  {
    if (my_strcmp(list_to_str(list_read, 0, historic),
		  list_to_str(tmp->list_read, 0, historic)) == 0)
      return (0);
    if ((tmp->prec = create_hist(list_read)) == NULL)
      return (-1);
    *historic = tmp->prec;
    tmp->prec->next = tmp;
  }
  else
    if ((*historic = create_hist(list_read)) == NULL)
      return (-1);
  return (0);
}
