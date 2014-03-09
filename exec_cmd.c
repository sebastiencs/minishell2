/*
** main.c for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 17:40:22 2014 chapui_s
** Last update Sun Mar  9 12:46:16 2014 chapui_s
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

static void	exec_it(t_pipe *l_pip, char **env, int i)
{
  restore_term(&term_attr);
  if ((execve(l_pip->cmd[i]->cmd_path, l_pip->cmd[i]->args, env)) == -1)
  {
    puterror("error: execve\n");
    exit(0);
  }
}

int		loop_exec_pipe(int nb_cmd_pipe,
			       t_pipe *l_pip,
			       char **env,
			       int is_redi)
{
  unsigned int	i;
  pid_t		pid;
  int		ret;

  i = 0;
  while (i < nb_cmd_pipe)
  {
    if (is_builtin(l_pip->cmd[i]->filename) == 1
	&& (ret = do_builtin(l_pip->cmd[i], env, l_pip, (i < nb_cmd_pipe - 1) ?
			     (l_pip->list_out[i]) : (fd_tty))) != 0)
      return (ret);
    else if ((is_builtin(l_pip->cmd[i]->filename) == 0) && (pid = fork()) == 0)
    {
      if ((do_redirections(l_pip, i, env, is_redi)) == -1)
	exit(0);
      close_pipe(l_pip, nb_cmd_pipe);
      exec_it(l_pip, env, i);
    }
    else if (pid == -1)
      return (my_putstr("error: fork\n"));
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
    }
    else if (WIFSTOPPED(status[i]))
      puterror("Stopped\n");
    i += 1;
  }
  restore_after_fork();
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
