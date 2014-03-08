/*
** check_str.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 20:11:19 2014 chapui_s
** Last update Sat Mar  8 18:11:48 2014 chapui_s
*/

#include "minish.h"

int		check_str_redi(char *str)
{
  unsigned int	i;

  i = 0;
  while (str[i])
  {
    if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
	|| (str[i] == '>' && str[i + 1] == ' ' && str[i + 2] == '>'))
      return (puterror("error: expression expected near '>'.\n"));
    if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
	|| (str[i] == '<' && str[i + 1] == ' ' && str[i + 2] == '<'))
      return (puterror("error: expression expected near '<'.\n"));
    if ((str[i] == '>' || str[i] == '<')
	&& (str[i + 1] == '|' || str[i + 1] == '\0'
	    || (str[i + 1] == ' '
		&& (str[i + 2] == '\0' || str[i + 2] == '|'))))
      return (puterror("error: expression expected near '<' or '>'.\n"));
    if ((str[i] == '>' && str[i + 1] == '<')
	|| (str[i] == '<' && str[i + 1] == '>'))
      return (puterror("error: expression expected near '<' or '>'.\n"));
    i += 1;
  }
  return (0);
}

int		check_str(char *str)
{
  unsigned int	i;

  i = 0;
  if (check_str_redi(str) == -1)
    return (-1);
  if (str[0] == ';' || str[0] == '|')
    return (puterror("error: expression expected near ';' or '|'.\n"));
  while (str[i])
  {
    if ((str[i] == ';' || str[i] == '|')
	&& ((str[i + 1] == ';' || str[i + 1] == '|')
	    || (str[i + 1] == ' '
		&& (str[i + 2] == ';' || str[i + 2] == '|'))))
    {
      puterror("error: expression expected between ';' or '|'.\n");
      return (-1);
    }
    i += 1;
  }
  if (str[i - 1] == ';' || str[i - 1] == '|')
    return (puterror("error: expression expected near ';' or '|'.\n"));
  return (0);
}
