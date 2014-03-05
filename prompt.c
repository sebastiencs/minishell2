/*
** prompt.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 17:30:35 2014 chapui_s
** Last update Wed Feb 26 17:45:38 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

void	prompt(char **env)
{
  char	*user;

  if ((user = search_in_env(env, "USER=")) == NULL)
  {
    my_putstr("$> ");
  }
  else
  {
    my_putstr(user);
    my_putstr(" > ");
  }
}
