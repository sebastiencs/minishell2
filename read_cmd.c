/*
** read_cmd.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Feb 26 17:52:40 2014 chapui_s
** Last update Tue Mar  4 23:37:47 2014 chapui_s
*/

#include <term.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

static int	gmd(char *buf, int n1, int n2, int n3)
{
  if (buf[0] == n1 && buf[1] == n2 && buf[2] == n3)
    return (1);
  return (0);
}

char		*read_cmd(char **env, int is_prompt)
{
  t_read	*list_read;
  int		size_read;
  int		curs_cur;
  char		buf[128];
  int		is_rm;

  curs_cur = 0;
  is_rm = 0;
  list_read = NULL;
  buf_zero(buf, 128);
  my_tputs(tgetstr("im", NULL));
  (is_prompt == 1) ? (prompt(env)) : (0);
  while ((size_read = read(fd_tty, &buf, 10)) > 0 && buf[0] != '\n')
  {
    if ((get_char(&list_read, buf, &curs_cur, &is_rm)) == -1)
      return (NULL);
    ((gmd(buf, 27, 91, 68))) ? (go_left(&curs_cur, &is_rm)) : (0);
    ((gmd(buf, 27, 91, 67))) ? (go_right(&list_read, &curs_cur, &is_rm)) : (0);
    ((gmd(buf, 127, 0, 0))) ? (rm_left(&list_read, &curs_cur)) : (0);
    ((gmd(buf, 27, 91, 51))) ? (rm_cur(&list_read, buf, &curs_cur)) : (0);
    buf_zero(buf, 128);
  }
  if (size_read == -1)
    return (puterror_null("error: could not read\n"));
  return (list_to_str(list_read));
}
