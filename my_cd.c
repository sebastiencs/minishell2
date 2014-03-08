/*
** my_cd.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  6 19:18:56 2014 chapui_s
** Last update Sat Mar  8 01:34:43 2014 chapui_s
*/

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "minish.h"

static char	*get_path_prec(char **env)
{
  unsigned int	max;
  unsigned int	i;
  char		*new_path;
  char		*tmp;

  i = 0;
  max = 0;
  tmp = search_in_env(env, "OLDPWD");
  if ((new_path = (char*)malloc(my_strlen(tmp) + 1)) == NULL)
    return (NULL);
  while (tmp[max])
    max += 1;
  while (max > 0 && tmp[max] != '/')
    max -= 1;
  while (i < max)
  {
    new_path[i] = tmp[i];
    i += 1;
  }
  if (i == 0)
    new_path[0] = '/';
  new_path[(i != 0) ? (i) : (1)] = '\0';
  if ((my_setenv(&env, "PWD", new_path)) == -1)
    return (NULL);
  return (new_path);
}

static char	*get_complete_path(char **env, char *path)
{
  unsigned int	size;
  unsigned int	i;
  unsigned int	j;
  char		*old_pwd;
  char		*new_path;

  i = 0;
  j = 0;
  if (path && path[0] == '/')
    return (path);
  old_pwd = search_in_env(env, "OLDPWD");
  size = my_strlen(old_pwd) + my_strlen(path) + 2;
  if ((new_path = (char*)malloc(size)) == NULL)
    return (NULL);
  while (old_pwd[i])
    new_path[i] = old_pwd[i++];
  (new_path[i - 1] == '/' && path[0] == '/') ? (j += 1) : (0);
  (new_path[i - 1] != '/' && path[0] != '/') ? (new_path[i++] = '/') : (0);
  while (path[j])
    new_path[i + j] = path[j++];
  new_path[i + j] = '\0';
  return (new_path);
}

static int	save_path(char *path, char **env)
{
  char		*pwd;

  if ((pwd = search_in_env(env, "PWD=")) != NULL)
    if ((my_setenv(&env, "OLDPWD", pwd)) == -1)
      return (-1);
  if (search_in_env(env, "OLDPWD") != NULL && my_strcmp(path, "..") == 0)
  {
    if ((get_path_prec(env)) == NULL)
      return (-1);
  }
  else if (search_in_env(env, "OLDPWD") != NULL)
  {
    if ((path = get_complete_path(env, path)) == NULL)
      return (-1);
    if ((my_setenv(&env, "PWD", path) == -1))
      return (-1);
  }
  return (0);
}

int		my_cd(char *path, char **env)
{
  if (path == NULL || my_strcmp(path, "~") == 0)
    path = search_in_env(env, "HOME=");
  if (path && path[0] == '-' && path[1] == '\0')
    path = search_in_env(env, "OLDPWD=");
  if (access(path, F_OK) == -1)
    return (my_putstr("error: Folder doesn't exist\n"));
  else if (access(path, X_OK) == -1)
    return (my_putstr("error: Check your rights on the folder\n"));
  if (path)
  {
    if ((save_path(path, env)) == -1)
      return (-1);
    if ((chdir(path)) == -1)
      return (my_putstr("error: Can't access\n"));
  }
  return (0);
}
