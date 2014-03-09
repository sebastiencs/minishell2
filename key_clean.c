/*
** key_clean.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Mar  5 18:49:51 2014 chapui_s
** Last update Sun Mar  9 12:40:58 2014 chapui_s
*/

#include <stdlib.h>
#include <term.h>
#include "minish.h"

void		clean_screen(char **env, t_read *list_read)
{
  my_tputs(tgetstr("cl", NULL));
  prompt();
  disp_list_read(list_read);
}
