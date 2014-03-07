/*
** my_unsetenv.c for minishell in /home/sebastien/travaux/minishell
**
** Made by Sebastien Chapuis
** Login   <sebastien@epitech.net>
**
** Started on  Wed Dec 18 19:54:06 2013 Sebastien Chapuis
** Last update Thu Mar  6 19:51:22 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

int	my_unsetenv(char ***env, char *variable)
{
  int	i;
  char	**tmp_var;

  i = 0;
  tmp_var = *env;
  if (variable == NULL)
    return (puterror("usage: unsetenv VARIABLE\n"));
  if (variable == NULL || my_strlen(variable) == 0
      || my_strchr(variable, '=') != NULL)
  {
    puterror("error -> variable is NULL or there is '=' in name\n");
    return (0);
  }
  while (tmp_var && tmp_var[i]
	 && my_strncmp(variable, tmp_var[i], my_strlen(variable)) != 0)
    i = i + 1;
  if (tmp_var[i] == NULL)
    return (0);
  while (tmp_var[i])
  {
    tmp_var[i] = tmp_var[i + 1];
    i = i + 1;
  }
  tmp_var[i] = NULL;
  return (0);
}
