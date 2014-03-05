/*
** str_to_cmd.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar  3 14:45:46 2014 chapui_s
** Last update Tue Mar  4 22:39:05 2014 chapui_s
*/

#include <stdlib.h>
#include "minish.h"

char		*get_redirection(char *str, t_cmd *cmd)
{
  unsigned int	i;

  i = 0;
  cmd->is_redi_right = 0;
  cmd->is_redi_left = 0;
  while (str[i])
  {
    if (str[i] == '>')
    {
      cmd->is_redi_right = 1;
      get_right_redirection(str + i + 1, cmd);
      (str[i + 1] == '>') ? (i += 1) : (0);
    }
    if (str[i] == '<')
    {
      cmd->is_redi_left = 1;
      get_left_redirection(str + i + 1, cmd);
      (str[i + 1] == '<') ? (i += 1) : (0);
    }
    i += 1;
  }
  str = get_str_without_redi(str, cmd);
  return (str);
}

t_cmd		*str_to_cmd(char *str, char **env)
{
  t_cmd		*cmd;
  int		i;
  int		j;

  i = 0;
  j = 0;
  if ((cmd = (t_cmd*)malloc(sizeof(t_cmd))) == NULL)
    return (puterror_null("error: could not alloc\n"));
  str = get_redirection(str, cmd);
  while (str[i] && str[i] == ' ')
    i = i + 1;
  while (str[i + j] && str[i + j++] != ' ');
  if ((cmd->filename = (char*)malloc(sizeof(char) * (j + 1))) == NULL)
    return (puterror_null("error: could not alloc\n"));
  cmd->cmd_path = NULL;
  cmd->args = NULL;
  j = 0;
  while (str[i + j] && str[i + j] != ' ')
    cmd->filename[j] = str[i + j++];
  cmd->filename[j] = 0;
  if ((cmd->args = my_str_to_wordtab(str + i)) == NULL)
    return (NULL);
  cmd->cmd_path = find_cmd(cmd->args[0], env, 0, NULL);
  return (cmd);
}
