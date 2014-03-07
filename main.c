/*
** main.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 17:40:22 2014 chapui_s
** Last update Fri Mar  7 20:51:58 2014 chapui_s
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include "minish.h"

void		free_list_str_pipe(t_pipe *list_pipe, char **str_pipe)
{
  unsigned int	i;

  i = 0;
  free(list_pipe->status);
  free(list_pipe->list_in);
  free(list_pipe->list_out);
  free(list_pipe->list_fd);
  while (list_pipe->cmd[i])
  {
    free(list_pipe->cmd[i]->filename);
    free(list_pipe->cmd[i++]);
  }
  free(list_pipe->cmd[i]);
  free(list_pipe->cmd);
  free(list_pipe);
  i = 0;
  while (str_pipe[i])
    free(str_pipe[i++]);
  free(str_pipe[i]);
  free(str_pipe);
}

void		free_str_tab(char **str_tab)
{
  unsigned int	i;

  i = 0;
  while (str_tab[i])
    free(str_tab[i++]);
  free(str_tab[i]);
  free(str_tab);
}

int			main(int argc, char **argv, char **env)
{
  struct termios	term_attr;
  int			ret_exec;

  ret_exec = 0;
  term_attr.c_lflag = 1;
  if (search_in_env(env, "TERM") != NULL)
  {
    if ((fd_tty = open("/dev/tty", O_RDWR)) == -1)
      return (puterror("error: could not open /dev/tty\n"));
    if (init_term(env, &term_attr) == -1)
      return (-1);
  }
  else
    fd_tty = 1;
  while (ret_exec == 0)
  {
    if ((ret_exec = exec_cmd(env)) != 0)
    {
      restore_term(&term_attr);
      return ((ret_exec == -3) ? (0) : (ret_exec));
    }
  }
  restore_term(&term_attr);
  return (0);
}
