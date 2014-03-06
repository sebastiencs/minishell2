/*
** main.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 17:40:22 2014 chapui_s
** Last update Wed Mar  5 18:43:08 2014 chapui_s
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include "minish.h"

int	get_nb_cmd_pipe(char *str)
{
  int	nb;
  int	i;

  nb = 1;
  i = 0;
  while (str && str[i])
  {
    if (str[i] == '|')
      nb += 1;
    i += 1;
  }
  return (nb);
}

int		prepare_pipe(int nb_cmd_pipe,
			     int *list_in,
			     int *list_out,
			     int *list_fd)
{
  unsigned int	i;
  unsigned int	j;
  int		fd[2];

  i = 0;
  while (i < nb_cmd_pipe)
  {
    list_out[i] = -1;
    list_in[i] = -1;
    i += 1;
  }
  i = 0;
  j = 0;
  while (i < nb_cmd_pipe - 1)
  {
    if ((pipe(fd)) == -1)
      return (puterror("error: pipe\n"));
    list_out[i] = fd[1];
    list_in[i + 1] = fd[0];
    list_fd[j] = fd[0];
    list_fd[j + 1] = fd[1];
    i += 1;
    j += 2;
  }
  return (0);
}

int		loop_exec_pipe(int nb_cmd_pipe,
			       t_pipe *list_pipe,
			       char **env)
{
  unsigned int	i;
  unsigned int	j;
  pid_t		pid;

  i = 0;
  j = 0;
  while (i < nb_cmd_pipe)
  {
    if ((pid = fork()) == 0)
    {
      j = 0;
      do_redirections(list_pipe, i, env);
      while (j < 2 * (nb_cmd_pipe - 1))
      	close(list_pipe->list_fd[j++]);
      if ((execve(list_pipe->cmd[i]->cmd_path,
		  list_pipe->cmd[i]->args, env)) == -1)
	return (puterror("error: execve\n"));
    }
    else if (pid == -1)
      return (puterror("error: fork\n"));
    i += 1;
  }
}

void		wait_proc(int nb_cmd_pipe, int *status, int *list_fd)
{
  unsigned int	i;

  i = 0;
  while (i < 2 * (nb_cmd_pipe - 1))
    close(list_fd[i++]);
  i = 0;
  while (i < nb_cmd_pipe)
  {
    wait(&(status[i]));
    if (WIFSIGNALED(status[i]))
    {
      if (WTERMSIG(status[i]) == 11)
	puterror("Segfault !\n");
      else if (WTERMSIG(status[i]) == 8)
	puterror("Arithmetic error !\n");
      else
	puterror("Killed\n");
    }
    else if (WIFSTOPPED(status[i]))
      puterror("Stopped\n");
    i += 1;
  }
}

t_pipe		*malloc_pipe_struct(t_pipe *list_pipe,
				    int nb_cmd_pipe,
				    char **str_pipe,
				    char **env)
{
  unsigned int	i;

  i = 0;
  while (str_pipe[i])
    i += 1;
  if ((list_pipe->status = (int*)malloc(sizeof(int) * nb_cmd_pipe)) == NULL
      || (list_pipe->list_in = (int*)malloc(sizeof(int) * nb_cmd_pipe)) == NULL
      || (list_pipe->list_out
	  = (int*)malloc(sizeof(int) * nb_cmd_pipe)) == NULL
      || (list_pipe->list_fd
	  = (int*)malloc(sizeof(int) * ((nb_cmd_pipe - 1) * 2))) == NULL
      || (list_pipe->cmd = (t_cmd**)malloc(sizeof(t_cmd*) * (i + 1))) == NULL)
    return (puterror_null("error: could not alloc\n"));
  i = 0;
  while (str_pipe[i])
  {
    if ((list_pipe->cmd[i] = str_to_cmd(str_pipe[i++], env)) == NULL)
      return (NULL);
    if (list_pipe->cmd[i - 1]->cmd_path == NULL
	&& (cmd_null(list_pipe->cmd[i - 1], str_pipe[i - 1])) == -1)
      return (NULL);
  }
  list_pipe->cmd[i] = NULL;
  return (list_pipe);
}

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

int		exec_tab(char *str,
			 char **env,
			 int nb_cmd_pipe,
			 char **str_pipe)
{
  t_pipe	*list_pipe;

  if ((list_pipe = (t_pipe*)malloc(sizeof(*list_pipe))) == NULL)
    return (puterror("error: could not alloc\n"));
  if ((str_pipe = seperate_wordtab(str, '|')) == NULL)
    return (-1);
  if ((list_pipe = malloc_pipe_struct(list_pipe, nb_cmd_pipe,
				      str_pipe, env)) == NULL)
    return (-1);
  if ((prepare_pipe(nb_cmd_pipe, list_pipe->list_in,
  		    list_pipe->list_out, list_pipe->list_fd)) == -1)
    return (-1);
  if ((loop_exec_pipe(nb_cmd_pipe, list_pipe, env)) == -1)
    return (-1);
  wait_proc(nb_cmd_pipe, list_pipe->status, list_pipe->list_fd);
  free_list_str_pipe(list_pipe, str_pipe);
}

int	exec_cmd(char **env)
{
  char	*str_cmd;
  char	**str_tab;
  int	i;

  i = 0;
  if ((str_cmd = read_cmd(env, 1)) == NULL)
    return (-1);
  write(fd_tty, "\n", 1);
  if ((my_strlen(str_cmd)) == 0)
    return (0);
  if ((check_str(str_cmd)) == -1)
    return (0);
  if ((str_tab = seperate_wordtab(str_cmd, ';')) == NULL)
    return (-1);
  while (str_tab[i])
  {
    exec_tab(str_tab[i], env, get_nb_cmd_pipe(str_tab[i]), NULL);
    i += 1;
  }
  return (0);
}

int			main(int argc, char **argv, char **env)
{
  struct termios	term_attr;
  int			ret_exec;

  ret_exec = 0;
  term_attr.c_lflag = 1;
  if ((fd_tty = open("/dev/tty", O_RDWR)) == -1)
    return (puterror("error: could not open /dev/tty\n"));
  if (init_term(env, &term_attr) == -1)
    return (-1);
  while (ret_exec == 0)
  {
    ret_exec = exec_cmd(env);
  }
  restore_term(&term_attr);
  return (0);
}
