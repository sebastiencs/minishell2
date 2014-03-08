/*
** main.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 17:40:22 2014 chapui_s
** Last update Sat Mar  8 00:50:42 2014 chapui_s
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

int		loop_exec_pipe(int nb_cmd_pipe,
			       t_pipe *list_pipe,
			       char **env,
			       int is_redi)
{
  unsigned int	i;
  unsigned int	j;
  pid_t		pid;
  int		ret_built;

  i = 0;
  j = 0;
  while (i < nb_cmd_pipe)
  {
    if (is_builtin(list_pipe->cmd[i]->filename) == 1)
    {
      if ((ret_built = do_builtin(list_pipe->cmd[i], env, list_pipe,
				  (i < nb_cmd_pipe - 1) ?
				  (list_pipe->list_out[i]) : (fd_tty))) != 0)
	return (ret_built);
    }
    else if ((pid = fork()) == 0)
    {
      j = 0;
      if ((do_redirections(list_pipe, i, env, is_redi)) == -1)
	return (-1);
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
  return (0);
}

void		wait_proc(int nb_cmd_pipe,
			  int *status,
			  int *list_fd,
			  t_pipe *list_pipe)
{
  int		i;

  i = 0;
  while (i < 2 * (nb_cmd_pipe - 1))
    close(list_fd[i++]);
  i = 0;
  while (i < list_pipe->nb_cmd_to_wait)
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

static int	is_because_no_found(t_cmd **cmd, char **str_pipe)
{
  unsigned int	i;

  i = 0;
  while (str_pipe[i])
  {
    if (cmd[i]->cmd_path == NULL)
      return (1);
    i += 1;
  }
  return (0);
}

static int	exec_tab(char *str,
			 char **env,
			 int nb_cmd_pipe,
			 char **str_pipe)
{
  t_pipe	*list_pipe;
  int		ret_exec;

  if ((list_pipe = (t_pipe*)malloc(sizeof(*list_pipe))) == NULL)
    return (puterror("error: could not alloc\n"));
  if ((str_pipe = seperate_wordtab(str, '|')) == NULL)
    return (-1);
  if ((list_pipe = malloc_pipe_struct(list_pipe, nb_cmd_pipe,
				      str_pipe, env)) == NULL)
    return (-1);
  if ((find_all_cmd(str_pipe, list_pipe)) == 0)
    return (1);
  if ((prepare_pipe(nb_cmd_pipe, list_pipe->list_in,
  		    list_pipe->list_out, list_pipe->list_fd)) == -1)
    return (-1);
  list_pipe->nb_cmd_to_wait = nb_cmd_pipe;
  if ((ret_exec = loop_exec_pipe(nb_cmd_pipe, list_pipe, env, 1)) != 0)
    return (ret_exec);
  wait_proc(nb_cmd_pipe, list_pipe->status, list_pipe->list_fd, list_pipe);
  if ((update_env(&env, list_pipe->cmd)) == -1)
    return (-1);
  free_list_str_pipe(list_pipe, str_pipe);
  return (0);
}

int		exec_cmd(char **env)
{
  char		*str_cmd;
  char		**str_tab;
  int		i;
  int		ret;

  i = 0;
  if ((str_cmd = chose_read(env, 1)) == NULL)
    return (-1);
  if ((my_strlen(str_cmd)) == 0)
    return (0);
  if ((check_str(str_cmd)) == -1)
    return (0);
  if ((str_tab = seperate_wordtab(str_cmd, ';')) == NULL)
    return (-1);
  while (str_tab[i])
  {
    ret = exec_tab(str_tab[i], env, get_nb_cmd_pipe(str_tab[i]), NULL);
    if (ret == 1)
      break ;
    else if (ret != 0)
      return (ret);
    i += 1;
  }
  free_str_tab(str_tab);
  return (0);
}
