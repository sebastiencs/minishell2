/*
** list_historic.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 11:19:34 2014 chapui_s
** Last update Sun Mar  9 12:54:02 2014 chapui_s
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

static void		rm_same_cmd_in_list(t_historic **historic)
{
  t_historic		*last_add;
  t_historic		*tmp;

  last_add = *historic;
  tmp = last_add->next;
  while (tmp)
  {
    if (my_strcmp(list_to_str(tmp->list_read, 0, NULL),
		  list_to_str(last_add->list_read, 0, NULL)) == 0)
    {
      tmp->prec->next = tmp->next;
      if (tmp->next)
	tmp->next->prec = tmp->prec;
      free(tmp);
    }
    tmp = tmp->next;
  }
}

static unsigned int	get_size_historic(t_historic **historic)
{
  t_historic		*tmp;
  unsigned int		size;

  size = 0;
  tmp = *historic;
  while (tmp)
  {
    size += 1;
    tmp = tmp->next;
  }
  return (size);
}

static void		rm_last_historic(t_historic **historic)
{
  t_historic		*tmp;
  t_historic		*tmp_save;

  tmp = *historic;
  while (tmp->next)
    tmp = tmp->next;
  tmp_save = tmp->prec;
  tmp_save->next = NULL;
  free(tmp);
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
    rm_same_cmd_in_list(historic);
    if (get_size_historic(historic) == HISTORIC_SIZE_MAX + 1)
      rm_last_historic(historic);
  }
  else
    if ((*historic = create_hist(list_read)) == NULL)
      return (-1);
  return (0);
}
