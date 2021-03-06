/*
** find_cmd.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar  3 14:57:11 2014 chapui_s
** Last update Sun Mar  9 12:48:05 2014 chapui_s
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "minish.h"

static char	**path_to_wordtab(char *str)
{

  char		**paths;
  int		i;

  i = 0;
  while (i < 5)
    str[i++] = ' ';
  if ((paths = my_str_to_wordtab(str)) == NULL)
    return (NULL);
  free(str);
  return (paths);
}

static char	*free_paths(char **paths, int i)
{
  char		*good_paths;
  int		j;

  j = 0;
  if (paths == NULL || paths[i] == NULL)
    return (NULL);
  if ((good_paths = (char*)malloc(my_strlen(paths[i]) + 1)) == NULL)
    return (NULL);
  while (paths[i][j])
    good_paths[j] = paths[i][j++];
  good_paths[j] = 0;
  i = 0;
  while (paths[i])
  {
    if (paths[i] != NULL)
      free(paths[i]);
    i = i + 1;
  }
  free(paths[i]);
  free(paths);
  return (good_paths);
}

static char	*is_path_good(char *str)
{
  if (access(str, X_OK) == 0)
    return (str);
  return (NULL);
}

char		*find_it(char *str, char **environ, int i, char *tmp)
{
  char		**paths;

  while (environ[i] && my_strncmp("PATH=", environ[i], 5) != 0)
    i = i + 1;
  if (environ[i] == NULL)
    return (NULL);
  if ((paths = path_to_wordtab(my_strdup(environ[i]))) == NULL)
    return (NULL);
  i = 0;
  while (paths[i])
  {
    tmp = paths[i];
    if ((paths[i] = str_cat(paths[i], str)) == NULL)
      return (NULL);
    free(tmp);
    if (access(paths[i], X_OK) == 0)
      return (free_paths(paths, i));
    i += 1;
  }
  return (NULL);
}

char		*find_cmd(char *str, char **environ, int i, char *tmp)
{
  if (is_builtin(str) == 1)
    return (make_path_builtin(str));
  else if (str && str[0] != '.' && str[0] != '/' && environ)
    return (find_it(str, environ, i, tmp));
  else
    return (is_path_good(str));
}
