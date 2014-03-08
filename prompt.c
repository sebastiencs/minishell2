/*
** prompt.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 17:30:35 2014 chapui_s
** Last update Sat Mar  8 17:41:19 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

void		prompt(void)
{
  char		*user;

  if (my_strlen(username) == 0)
  {
    my_putstr("$> ");
  }
  else
  {
    my_putstr(username);
    my_putstr(" > ");
  }
}
