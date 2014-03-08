/*
** read_cmd.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 17:52:40 2014 chapui_s
** Last update Sat Mar  8 15:50:43 2014 chapui_s
*/

#include <term.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

static int	gmd(char *buf, int n1, int n2, int n3)
{
  if (buf[0] == 4 && buf[1] == 0 && buf[2] == 0)
  {
    my_putstr("\n");
    return (1);
  }
  if (buf[0] == n1 && buf[1] == n2 && buf[2] == n3)
    return (1);
  return (0);
}

static int	get_key(t_read **list_read,
			int *curs_cur,
			char *buf,
			int *is_rm)
{
  if ((get_char(list_read, buf, curs_cur, is_rm)) == -1)
    return (-1);
  ((gmd(buf, 27, 91, 68))) ? (go_left(curs_cur, is_rm)) : (0);
  ((gmd(buf, 27, 91, 67))) ? (go_right(list_read, curs_cur, is_rm)) : (0);
  ((gmd(buf, 127, 0, 0))) ? (rm_left(list_read, curs_cur)) : (0);
  ((gmd(buf, 27, 91, 51))) ? (rm_cur(list_read, buf, curs_cur)) : (0);
  return (0);
}

void	my_putchar(char c)
{
  write(fd_tty, &c, 1);
}

void	disp_historic(t_historic *historic)
{
  t_historic	*tmp;
  t_read	*tmp_read;

  tmp = historic;
  while (tmp)
  {
    tmp_read = tmp->list_read;
    while (tmp_read)
    {
      my_putchar(tmp_read->c);
      tmp_read = tmp_read->next;
    }
    my_putstr("\n");
    tmp = tmp->next;
  }
}

void	disp_list_read(t_read *list_read)
{
  t_read	*tmp;

  tmp = list_read;
  while (tmp)
  {
    my_putchar(tmp->c);
    tmp = tmp->next;
  }
}

static t_read	*find_up_hist(t_historic **historic)
{
  t_historic	*tmp;

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

static t_read	*find_down_hist(t_historic **historic)
{
  t_historic	*tmp;

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

static void	clean_line(t_read *list_read)
{
  t_read	*tmp;

  tmp = list_read;
  while (tmp)
  {
    my_tputs(tgetstr("le", NULL));
    my_tputs(tgetstr("dc", NULL));
    tmp = tmp->next;
  }
}

static t_read	*move_in_historic(char *buf,
				  t_historic **historic,
				  t_read *list_read,
				  int *curs_cur)
{
  t_read	*to_return;

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

static void	re_init_historic(t_historic *historic)
{
  t_historic	*tmp;

  tmp = historic;
  while (tmp)
  {
    tmp->is_cur = 0;
    tmp = tmp->next;
  }
}

static char	*read_cmd(char **env, int is_prompt, t_historic **historic)
{
  t_read	*list_read;
  int		size_read;
  int		curs_cur;
  char		buf[128];
  int		is_rm;

  curs_cur = 0;
  is_rm = 0;
  list_read = NULL;
  buf_zero(buf, 128);
  my_tputs(tgetstr("im", NULL));
  (is_prompt == 1) ? (prompt()) : (0);
  while ((size_read = read(fd_tty, &buf, 10)) > 0 && buf[0] != '\n')
  {
    if (gmd(buf, 4, 0, 0) == 1
	|| (get_key(&list_read, &curs_cur, buf, &is_rm)) == -1)
      return (NULL);
    ((gmd(buf, 12, 0, 0))) ? (clean_screen(env)) : (0);
    if (gmd(buf, 27, 91, 65) == 1 || gmd(buf, 27, 91, 66) == 1)
      list_read = move_in_historic(buf, historic, list_read, &curs_cur);
    buf_zero(buf, 128);
  }
  if (size_read == -1)
    return (puterror_null("error: could not read\n"));
  return (list_to_str(list_read, is_prompt, historic));
}

char			*chose_read(char **env, int is_prompt)
{
  static t_historic	*historic;
  char			*str;

  if (fd_tty == 1)
  {
    if (is_prompt == 1)
      prompt();
    str = get_next_line(0);
    if (str != NULL && is_prompt == 1)
      str = clean_str(str);
    else if (is_prompt == 1)
      my_putstr("\n");
    return (str);
  }
  else
  {
    if ((str = read_cmd(env, is_prompt, &historic)) != NULL)
      my_putstr("\n");
    re_init_historic(historic);
    return (str);
  }
}
