/*
** seperate_dot_comma.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 20:18:53 2014 chapui_s
** Last update Thu Mar  6 15:12:35 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

static unsigned int	get_nb_sep(char *str, char separator)
{
  unsigned int		i;
  unsigned int		nb;

  nb = 1;
  i = 0;
  while (str && str[i])
  {
    if (str[i] == separator)
      nb += 1;
    i += 1;
  }
  return (nb);
}

static char	*dup_str(char *str, char *new_str, char separator)
{
  unsigned int	i;
  unsigned int	j;

  i = 0;
  j = 0;
  if (str[i] == ' ')
    i += 1;
  while (str[i] && str[i] != separator)
  {
    new_str[j] = str[i];
    j += 1;
    i += 1;
  }
  new_str[j] = 0;
  if (new_str[j - 1] == ' ')
    new_str[j - 1] = 0;
  return (new_str);
}

static char	*get_n_str(char *str, unsigned int i, char separator)
{
  unsigned int	size;
  unsigned int	cur;
  unsigned int	j;
  char		*new_str;

  j = 0;
  cur = 0;
  size = 0;
  while (str[cur] && j < i)
  {
    if (str[cur] == separator)
      j += 1;
    cur += 1;
  }
  while (str[cur + size] && str[cur + size] != separator)
    size += 1;
  if ((new_str = (char*)malloc(size + 1)) == NULL)
    return (puterror_null("error: could not alloc\n"));
  return (dup_str(str + cur, new_str, separator));
}

char		**seperate_wordtab(char *str, char separator)
{
  char		**str_tab;
  unsigned int	nb_sep;
  unsigned int	i;

  i = 0;
  nb_sep = get_nb_sep(str, separator);
  if ((str_tab = (char**)malloc(sizeof(*str_tab) * (nb_sep + 1))) == NULL)
    return (puterror_null("error: could not alloc\n"));
  while (i < nb_sep)
  {
    str_tab[i] = get_n_str(str, i, separator);
    i += 1;
  }
  str_tab[i] = NULL;
  /* free(str); */
  return (str_tab);
}
