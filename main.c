/*
** main.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 17:40:22 2014 chapui_s
** Last update Sat Mar  8 00:40:21 2014 chapui_s
*/

#include <signal.h>
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

static char	**begin_env(char **env)
{
  if (access("/usr/bin", X_OK) != -1)
    if (my_setenv(&env, "PATH", "/usr/bin") == -1)
      return (NULL);
  return (env);
}

char		*get_username(char **env)
{
  unsigned int	i;
  char		*tmp;
  char		*username;

  i = 0;
  if ((tmp = search_in_env(env, "USER=")) == NULL)
    return ("");
  if ((username = (char*)malloc(my_strlen(tmp) + 1)) == NULL)
    return (puterror_null("error: could not alloc\n"));
  while (tmp[i])
  {
    username[i] = tmp[i];
    i += 1;
  }
  username[i] = '\0';
  return (username);
}

static char	**init_sh(char **env, struct termios *term_attr)
{
  if (search_in_env(env, "TERM=") != NULL)
  {
    if ((fd_tty = open("/dev/tty", O_RDWR)) == -1)
      puterror("error: could not open /dev/tty\n");
    if (init_term(env, term_attr) == -1 || fd_tty == -1)
      fd_tty = 1;
  }
  else
    fd_tty = 1;
  if (env == NULL || env[0] == NULL)
    env = begin_env(env);
  if ((username = get_username(env)) == NULL)
    return (NULL);
  return (env);
}

int			main(int argc, char **argv, char **env)
{
  struct termios	term_attr;
  int			ret_exec;

  ret_exec = 0;
  if ((env = init_sh(env, &term_attr)) == NULL)
    return (-1);
  while (ret_exec == 0)
  {
    signal(SIGINT, get_sigint);
    if ((ret_exec = exec_cmd(env)) != 0)
    {
      restore_term(&term_attr);
      return ((ret_exec == -3) ? (0) : (ret_exec));
    }
  }
  restore_term(&term_attr);
  return (0);
}
