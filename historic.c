/*
** historic.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 16:39:00 2014 chapui_s
** Last update Sat Mar  8 17:25:09 2014 chapui_s
*/

#include <stdlib.h>
#include <term.h>
#include "minish.h"

static t_read		*find_up_hist(t_historic **historic)
{
  t_historic		*tmp;

  tmp = *historic;
  while (tmp)
  {
    if (tmp->is_cur == 1)
    {
      if (tmp->next)
      {
	tmp->is_cur = 0;
	tmp->next->is_cur = 1;
	return (tmp->next->list_read);
      }
      else
	return (tmp->list_read);
    }
    tmp = tmp->next;
  }
  (*historic)->is_cur = 1;
  return ((*historic)->list_read);
}

static t_read		*find_down_hist(t_historic **historic)
{
  t_historic		*tmp;

  tmp = *historic;
  while (tmp)
  {
    if (tmp->is_cur == 1)
    {
      tmp->is_cur = 0;
      if (tmp->prec)
      {
	tmp->prec->is_cur = 1;
	return (tmp->prec->list_read);
      }
      else
	return (tmp->list_read);
    }
    tmp = tmp->next;
  }
  (*historic)->is_cur = 0;
  return (NULL);
}

static void		clean_line(t_read *list_read)
{
  t_read		*tmp;

  tmp = list_read;
  while (tmp)
  {
    my_tputs(tgetstr("le", NULL));
    my_tputs(tgetstr("dc", NULL));
    tmp = tmp->next;
  }
}

t_read			*move_in_historic(char *buf,
					  t_historic **historic,
					  t_read *list_read,
					  int *curs_cur)
{
  t_read		*to_return;

  if (*historic == NULL)
    return (list_read);
  clean_line(list_read);
  if (buf[2] == 65)
    to_return = find_up_hist(historic);
  else
  {
    if ((to_return = find_down_hist(historic)) == list_read)
      return (NULL);
  }
  if (to_return)
  {
    disp_list_read(to_return);
    *curs_cur = get_size_list(to_return);
  }
  return (to_return);
}
