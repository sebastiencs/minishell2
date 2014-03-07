/*
** mod_term.c for allum1 in /home/sebastien/travaux/allum1
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Feb  6 12:50:26 2014 chapui_s
** Last update Fri Mar  7 21:35:51 2014 chapui_s
*/

#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "minish.h"

int	init_term(char **env,
		  struct termios *term_attr)
{
  char  term_buf[TERM_BUF_SIZE];
  char  *term_name;

  if ((term_name = get_term(env)) == NULL)
    return (puterror("error: could not determine your terminal\n"));
  if ((tgetent(term_buf, term_name)) <= 0)
  {
    puterror("error: could not find termcap database or \"");
    puterror(term_name);
    puterror("\" is not specified\n");
    return (-1);
  }
  if (tcgetattr(fd_tty, term_attr) < 0)
    return (puterror("error: could not get term values\n"));
  term_attr->c_lflag &= ~ICANON;
  term_attr->c_lflag &= ~ECHO;
  term_attr->c_cc[VMIN] = 1;
  term_attr->c_cc[VTIME] = 0;
  if ((tcsetattr(fd_tty, TCSANOW, term_attr)) < 0)
    return (puterror("error: could not set term values\n"));
  return (0);
}

int	restore_term_after_redi(struct termios *term_attr)
{
  if (fd_tty != 1)
  {
    term_attr->c_lflag &= ~ICANON;
    term_attr->c_lflag &= ~ECHO;
    if ((tcsetattr(fd_tty, TCSANOW, term_attr)) < 0)
      return (puterror("error: could not set term values\n"));
  }
  return (0);
}

int	restore_term(struct termios *term_attr)
{
  if (fd_tty != 1)
  {
    term_attr->c_lflag |= ICANON;
    term_attr->c_lflag |= ECHO;
    if ((tcsetattr(fd_tty, TCSANOW, term_attr)) == -1)
      return (puterror("error: could not set term values\n"));
  }
  return (0);
}
