/*
** my_puts.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 17:48:16 2014 chapui_s
** Last update Sat Mar  8 17:37:37 2014 chapui_s
*/

#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

void		*puterror_null(char *str)
{
  while (str && *str)
    write(2, str++, 1);
  return (NULL);
}

int		puterror(char *str)
{
  while (str && *str)
    write(2, str++, 1);
  return (-1);
}

int		my_putstr(char *str)
{
  while (str && *str)
    write(fd_tty, str++, 1);
  return (0);
}

void		my_tputs(char *str)
{
  if (str == NULL)
  {
    puterror("error: problem with tgetstr\n");
    exit(EXIT_FAILURE);
  }
  while (str && *str)
    write(fd_tty, str++, 1);
}

void		my_tputs2(int n1, int n2, int n3)
{
  char		tab[4];
  int		i;

  i = 0;
  tab[0] = n1;
  tab[1] = n2;
  tab[2] = n3;
  tab[3] = 0;
  while (tab[i])
    write(fd_tty, &(tab[i++]), 1);
}
