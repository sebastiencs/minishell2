/*
** about_env.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 17:23:41 2014 chapui_s
** Last update Thu Mar  6 19:55:15 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

char	*search_in_env(char **env, char *var)
{
  int	i;
  int	j;
  char	*value;
  int	size_var;

  i = 0;
  j = 0;
  value = NULL;
  if (env == NULL || env[0] == NULL)
    return (NULL);
  if ((size_var = my_strlen(var)) == 0)
    return (NULL);
  while (env && env[i] && my_strncmp(var, env[i], size_var) != 0)
    i += 1;
  if (env[i] == NULL)
    return (NULL);
  while (env[i] && env[i][j] && env[i][j] != '=')
    j += 1;
  j += 1;
  value = &(env[i][j]);
  return (value);
}
