/*
** disp_historic.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 16:40:27 2014 chapui_s
** Last update Sat Mar  8 17:28:55 2014 chapui_s
*/

#include <unistd.h>
#include "minish.h"

void		my_putchar(char c)
{
  write(fd_tty, &c, 1);
}

void		disp_list_read(t_read *list_read)
{
  t_read	*tmp;

  tmp = list_read;
  while (tmp)
  {
    my_putchar(tmp->c);
    tmp = tmp->next;
  }
}
