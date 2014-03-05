/*
** minish.h for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 17:42:54 2014 chapui_s
** Last update Wed Mar  5 00:39:23 2014 chapui_s
*/

#ifndef MINISH_H_
# define MINISH_H_

# include <termios.h>

typedef struct	s_read
{
  char		c;
  unsigned int	is_current;
  struct s_read	*prec;
  struct s_read	*next;
}		t_read;

typedef struct	s_cmd
{
  char		*filename;
  char		*cmd_path;
  char		**args;
  int		is_redi_right;
  char		*redi_right;
  int		is_redi_left;
  char		*redi_left;
}		t_cmd;

typedef struct	s_pipe
{
  int		*status;
  int		*list_in;
  int		*list_out;
  int		*list_fd;
  t_cmd		**cmd;
}		t_pipe;

# define TERM_BUF_SIZE	4096
struct termios		term_attr;

int		fd_tty;
void		*puterror_null(char *str);
int		puterror(char *str);
int		my_putstr(char *str);
int		push_read(t_read **list, char c, int place);
int		my_strcmp(char *s1, char *s2);
void		buf_zero(char *buf, int size);
int		init_term(char **env, struct termios *term_attr);
void		my_tputs(char *str);
int		my_strncmp(char *s1, char *s2, int n);
void		buf_zero(char *buf, int size);
char		*get_term(char **env);
int		get_size_list(t_read *list);
void		my_tputs2(int n1, int n2, int n3);
int		get_char(t_read **list_read, char *buf, int *curs_cur, int *is_rm);
int		go_left(int *curs_cur, int *is_rm);
int		rm_left(t_read **list_read, int *curs_cur);
int		rm_cur(t_read **list_read, char *buf, int *curs_cur);
int		go_right(t_read **list_read, int *curs_cur, int *is_rm);
char		*search_in_env(char **env, char *var);
void		prompt(char **env);
char		*read_cmd(char **env, int is_prompt);
char		*list_to_str(t_read *list_read);
int		check_str(char *str);
char		**seperate_wordtab(char *str, char separator);
int		restore_term(struct termios *term_attr);
void		rm_in_list(t_read **list, int nb);
int		my_strlen(char *str);
int		exec_it(char *str, char **env, int *pipefd, int i, int nb_pipe);
char		**my_str_to_wordtab(char *str);
t_cmd		*str_to_cmd(char *str, char **env);
char		*find_cmd(char *str, char **environ, int i, char *tmp);
char		*my_strdup(char *str);
char		*str_cat(char *s1, char *s2);
int		is_only_spaces(char *str);
int		cmd_null(t_cmd *cmd, char *str);
int		get_right_redirection(char *str, t_cmd *cmd);
int		get_left_redirection(char *str, t_cmd *cmd);
char		*get_str_without_redi(char *str, t_cmd *cmd);
int		do_redirections(t_pipe *list_pipe, int i, char **env);
char		*realloc_it(char *dest, char *src);
char		*get_next_line(const int fd);
int		restore_term_after_redi(struct termios *term_attr);
int		is_good_string_redi(char *str, char *good_string);
char		*rm_good_string(char *str);

#endif /* !MINISH_H_ */
