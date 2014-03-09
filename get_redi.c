/*
** get_redi.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar  4 22:48:02 2014 chapui_s
** Last update Sun Mar  9 12:48:34 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

static char	*get_redi_file(char *str)
{
  unsigned int	i;
  char		*file;

  i = 0;
  while (str && str[i] && str[i] != ' ')
    i += 1;
  if ((file = (char*)malloc(i + 1)) == NULL)
    return (puterror_null("error: could not alloc\n"));
  i = 0;
  while (str && str[i] && str[i] != ' ')
  {
    file[i] = str[i];
    i += 1;
  }
  file[i] = '\0';
  return (file);
}

int		get_right_redirection(char *str, t_cmd *cmd)
{
  unsigned int	i;

  i = 0;
  if (str[0] == '>' && ++i)
    cmd->is_redi_right = 2;
  while (str[i] == ' ')
    i += 1;
  if ((cmd->redi_right = get_redi_file(str + i)) == NULL)
    return (-1);
  return (0);
}

int		get_left_redirection(char *str, t_cmd *cmd)
{
  unsigned int	i;

  i = 0;
  if (str[0] == '<' && ++i)
    cmd->is_redi_left = 2;
  while (str[i] == ' ')
    i += 1;
  if ((cmd->redi_left = get_redi_file(str + i)) == NULL)
    return (-1);
  return (0);
}

static void	rm_redi_file(char *str)
{
  unsigned int	i;

  i = 0;
  str[0] = ' ';
  if (str[1] == '>' || str[1] == '<')
    str[1] = ' ';
  while (str[i] == ' ')
    i += 1;
  while (str[i] && str[i] != ' ')
  {
    str[i] = ' ';
    i += 1;
  }
}

char		*get_str_without_redi(char *str, t_cmd *cmd)
{
  unsigned int	i;

  if (cmd->is_redi_right == 0 && cmd->is_redi_left == 0)
    return (str);
  i = 0;
  while (str[i])
  {
    if (str[i] == '>' || str[i] == '<')
      rm_redi_file(str + i);
    i += 1;
  }
  return (str);
}
