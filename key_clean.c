/*
** key_clean.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Mar  5 18:49:51 2014 chapui_s
** Last update Wed Mar  5 18:54:16 2014 chapui_s
*/

#include <stdlib.h>

void	clean_screen(char **env)
{
  my_tputs(tgetstr("cl", NULL));
  prompt(env);
}
