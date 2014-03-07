/*
** my_cd.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  6 19:18:56 2014 chapui_s
** Last update Fri Mar  7 16:55:52 2014 chapui_s
*/

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "minish.h"

static int	save_path(char *path, char **env)
{
  char		*pwd;

  if ((pwd = search_in_env(env, "PWD=")) != NULL)
    if ((my_setenv(&env, "OLDPWD", pwd)) == -1)
      return (-1);
  if ((my_setenv(&env, "PWD", path)) == -1)
    return (-1);
  return (0);
}

int	my_cd(char *path, char **env)
{
  if (path == NULL)
    path = search_in_env(env, "HOME=");
  if (path && path[0] == '-' && path[1] == '\0')
    path = search_in_env(env, "OLDPWD=");
  if (access(path, F_OK) == -1)
    return (puterror("error: Folder doesn't exist\n"));
  else if (access(path, X_OK) == -1)
    return (puterror("error: Check your rights on the folder\n"));
  if (path)
  {
    if ((save_path(path, env)) == -1)
      return (-1);
    if ((chdir(path)) == -1)
      return (puterror("error: Can't access\n"));
  }
  return (0);
}
