/*
** historic.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 16:39:00 2014 chapui_s
** Last update Sun Mar  9 11:28:57 2014 chapui_s
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

static void		clean_line(void)
{
  my_tputs(tgetstr("dl", NULL));
  my_tputs(tgoto(tgetstr("ch", NULL), 0, 0));
  prompt();
}

t_read			*move_in_historic(char *buf,
					  t_historic **historic,
					  t_read *list_read,
					  int *curs_cur)
{
  t_read		*to_return;

  if (*historic == NULL)
    return (list_read);
  if (gmd(buf, 27, 91, 65) == 1 || gmd(buf, 27, 91, 66) == 1)
  {
    clean_line();
    if (buf[2] == 65)
      to_return = find_up_hist(historic);
    else
    {
      if ((to_return = find_down_hist(historic)) == list_read)
      {
	*curs_cur = 0;
	return (NULL);
      }
    }
    if (to_return)
    {
      disp_list_read(to_return);
      *curs_cur = get_size_list(to_return);
    }
    return (to_return);
  }
  return (list_read);
}
