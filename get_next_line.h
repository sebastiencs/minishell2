/*
** get_next_line.h for gnl in /home/chapui_s/travaux/get_next_line
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Tue Nov 19 16:54:01 2013 chapui_s
** Last update Sun Mar  2 17:15:08 2014 chapui_s
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define BUF_SIZE	42

typedef struct	s_fd
{
  char		*str;
  int		fd;
  struct s_fd	*next;
}		t_fd;

char	*get_next_line(const int fd);

#endif
