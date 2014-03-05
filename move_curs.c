/*
** move_curs.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 15:35:54 2014 chapui_s
** Last update Wed Feb 26 20:31:19 2014 chapui_s
*/

#include <term.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

int	get_char(t_read **list_read, char *buf, int *curs_cur, int *is_rm)
{
  if (buf[1] == 0 && buf[0] >= 1 && buf[0] <= 126)
  {
    (*curs_cur) += 1;
    if ((*is_rm)++ == -1)
    curs_cur = 0;
    if ((push_read(list_read, buf[0], *curs_cur)) == -1)
      return (-1);
    write(fd_tty, &(buf[0]), 1);
    return (0);
  }
  return (1);
}

int	go_left(int *curs_cur, int *is_rm)
{
  if ((*curs_cur) > 0)
    my_tputs(tgetstr("le", NULL));
  ((*curs_cur) - 1 >= 0) ? ((*curs_cur) -= 1) : (0);
  if ((*curs_cur) == 0)
    (*is_rm) = -1;
  return (0);
}

int	rm_left(t_read **list_read, int *curs_cur)
{
  if ((*curs_cur) > 0)
  {
    my_tputs(tgetstr("le", NULL));
    my_tputs(tgetstr("dc", NULL));
    ((*curs_cur) - 1 >= 0) ? ((*curs_cur) -= 1) : (0);
    rm_in_list(list_read, *curs_cur);
  }
  return (0);
}

int	rm_cur(t_read **list_read, char *buf, int *curs_cur)
{
  if (buf[3] == 126)
  {
    my_tputs(tgetstr("dc", NULL));
    rm_in_list(list_read, *curs_cur);
  }
  return (0);
}

int	go_right(t_read **list_read, int *curs_cur, int *is_rm)
{
  if ((*curs_cur) < get_size_list(*list_read))
  {
    my_tputs2(27, 91, 67);
    *(is_rm) = 0;
    (*curs_cur) += 1;
  }
  return (0);
}
