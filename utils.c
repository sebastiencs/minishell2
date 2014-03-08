/*
** utils.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 18:18:00 2014 chapui_s
** Last update Sat Mar  8 17:46:41 2014 chapui_s
*/

#include <stdlib.h>

int		my_strcmp(char *s1, char *s2)
{
  if (s1 == NULL && s2 != NULL)
    return (1);
  return ((*s1 == *s2 && *s1) ? (my_strcmp(++s1, ++s2)) : (*s1 - *s2));
}

int		my_strncmp(char *s1, char *s2, int n)
{
  int		i;

  i = 0;
  while (i < n)
  {
    if (s1[i] != s2[i])
      return (s1[i] - s2[i]);
    else if (s1[i] == '\0')
      return (0);
    i = i + 1;
  }
  return (0);
}

int		my_strlen(char *str)
{
  int		size;

  size = 0;
  while (str && str[size])
    size += 1;
  return (size);
}

void		buf_zero(char *buf, int size)
{
  int		i;

  i = 0;
  while (i < size)
  {
    buf[i] = 0;
    i += 1;
  }
}

char		*get_term(char **env)
{
  int		i;

  i = 0;
  if (env == NULL || *env == NULL)
    return (NULL);
  while (env[i])
  {
    if (my_strncmp("TERM=", env[i], 5) == 0)
      return (&(env[i][5]));
    i = i + 1;
  }
  return (NULL);
}
