/*
** exec_cmd.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar  3 14:44:19 2014 chapui_s
** Last update Mon Mar  3 18:35:27 2014 chapui_s
*/

#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minish.h"

static void	wait_child(void)
{
  int		status;

  /* signal(SIGINT, get_sigint); */
  wait(&status);
  if (WIFSIGNALED(status))
  {
    if (WTERMSIG(status) == 11)
      puterror("Segfault !\n");
    else if (WTERMSIG(status) == 8)
      puterror("Arithmetic error !\n");
    else
      puterror("Killed\n");
  }
  else if (WIFSTOPPED(status))
    puterror("Stopped\n");
}

int		exec_it(char *str, char **env, int *pipefd, int i, int nb_pipe)
{
  t_cmd		*cmd;
  pid_t		pid;
  int		j;

  if ((cmd = str_to_cmd(str, env)) == NULL)
    return (-1);
  if (cmd->cmd_path == NULL)
    return (cmd_null(cmd, str));

  j = 0;
  if ((pid = fork()) == 0)
  {

    if (i != 2)
    {
      if (dup2(pipefd[(i * 2) + 1], 1) == -1)
	return (puterror("error: dup2\n"));
    }
    if (i != 0)
    {
      if (dup2(pipefd[(i * 2) - 2], 0) == -1)
	return (puterror("error: dup2\n"));
    }

    while (j < 2 * nb_pipe)
    {
      close(pipefd[j]);
      j += 1;
    }


    if ((execve(cmd->cmd_path, cmd->args, env)) == -1)
      return (puterror("error: could not execute the command\n"));

  }
  else if (pid != -1)
  {
    /* if (i == 0) */
    /*   close(pipefd[1]); */
    /* else */
    /*   close(pipefd[0]); */
    wait_child();
  }
  else
    return (-2);
  return (0);
}
