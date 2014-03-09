/*
** signal_funct.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 00:36:56 2014 chapui_s
** Last update Sun Mar  9 13:00:09 2014 chapui_s
*/

#include "minish.h"

void		get_sigint(int sig)
{
  (void)sig;
  my_putstr("\n");
  prompt();
}
