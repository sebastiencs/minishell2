
/*
** redirections.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar  4 22:47:48 2014 chapui_s
** Last update Sun Mar  9 12:49:33 2014 chapui_s
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "minish.h"

static int	do_redi_right(t_pipe *list_pipe, int i)
{
  int		fd;
  int		flags;

  fd = 0;
  flags = O_CREAT | O_RDWR;
  flags |= (list_pipe->cmd[i]->is_redi_right == 1) ? (O_TRUNC) : (O_APPEND);
  if ((fd = open(list_pipe->cmd[i]->redi_right, flags, 0644)) == -1)
    return (puterror("error: open\n"));
  if ((dup2(fd, 1)) == -1)
    return (puterror("error: dup2\n"));
  return (fd);
}

static int	do_simple_left_redi(t_pipe *list_pipe, int i)
{
  int		fd;
  int		flags;

  fd = 0;
  flags = O_RDONLY;
  if ((fd = open(list_pipe->cmd[i]->redi_left, flags)) == -1)
  {
    puterror("error: ");
    puterror(list_pipe->cmd[i]->redi_left);
    puterror(": no such file\n");
    return (-1);
  }
  if ((dup2(fd, 0)) == -1)
    return (puterror("error: dup2\n"));
  return (fd);
}

static int	make_two_redi_left(t_pipe *list_pipe, int i, char *buffer)
{
  int		*pipefd;

  if (list_pipe->list_in[i] != -1)
    close(list_pipe->list_in[i]);
  if ((list_pipe->list_fd = (int*)malloc(sizeof(int) * 2)) == NULL)
    return (puterror("error: malloc\n"));
  pipefd = list_pipe->list_fd;
  if ((pipe(pipefd)) == -1)
    return (puterror("error: pipe\n"));
  write(pipefd[1], buffer, my_strlen(buffer));
  close(pipefd[1]);
  if ((dup2(pipefd[0], 0)) == -1)
    return (puterror("error: dup2\n"));
  return (pipefd[0]);
}

static int	do_redi_left(t_pipe *list_pipe, int i, char **env)
{
  unsigned int	j;
  char		*buffer;
  char		*tmp;

  restore_after_fork();
  if (list_pipe->cmd[i]->is_redi_left == 1)
    return (do_simple_left_redi(list_pipe, i));
  j = 0;
  buffer = NULL;
  tmp = NULL;
  while (is_good_string_redi(buffer, list_pipe->cmd[i]->redi_left) != 1)
  {
    my_putstr("> ");
    tmp = chose_read(env, 0);
    if ((buffer = realloc_it(buffer, tmp)) == NULL)
      return (-1);
    j += 1;
  }
  buffer = rm_good_string(buffer);
  return (make_two_redi_left(list_pipe, i, buffer));
}

int		do_redirections(t_pipe *list_pipe,
				int i,
				char **env,
				int is_redi)
{
  int		ret;

  ret = 0;
  if (list_pipe->cmd[i]->is_redi_left != 0)
    ret += do_redi_left(list_pipe, i, env);
  else if (is_redi == 1)
  {
    if (list_pipe->list_in[i] != -1)
      if ((dup2(list_pipe->list_in[i], 0)) == -1)
	return (puterror("error: dup2\n"));
  }
  if (list_pipe->cmd[i]->is_redi_right != 0)
    ret += do_redi_right(list_pipe, i);
  else if (is_redi == 1)
  {
    if (list_pipe->list_out[i] != -1)
      if ((dup2(list_pipe->list_out[i], 1)) == -1)
        return (puterror("error: dup2\n"));
  }
  restore_term(&term_attr);
  return (ret);
}
