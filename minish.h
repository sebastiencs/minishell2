/*
** minish.h for minish2 in /home/sebastien/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb  9 17:42:54 2014 chapui_s
** Last update Sun Mar  9 12:54:47 2014 chapui_s
*/

#ifndef MINISH_H_
# define MINISH_H_

# include <termios.h>

typedef struct		s_read
{
  char			c;
  unsigned int		is_current;
  struct s_read		*prec;
  struct s_read		*next;
}			t_read;

typedef struct		s_cmd
{
  char			*filename;
  char			*cmd_path;
  char			**args;
  int			is_redi_right;
  char			*redi_right;
  int			is_redi_left;
  char			*redi_left;
}			t_cmd;

typedef struct		s_pipe
{
  int			*status;
  int			*list_in;
  int			*list_out;
  int			*list_fd;
  int			nb_cmd_to_wait;
  t_cmd			**cmd;
}			t_pipe;

typedef struct		s_env
{
  int			i;
  int			zero;
  int			u;
}			t_env;

typedef struct		s_historic
{
  t_read		*list_read;
  int			is_cur;
  struct s_historic	*prec;
  struct s_historic	*next;
}			t_historic;

# define TERM_BUF_SIZE		4096
# define HISTORIC_SIZE_MAX	15

int		fd_tty;
char		*username;
struct termios	term_attr;
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
int		go_left(int *curs_cur, int *is_rm, t_read **list_read);
int		rm_left(t_read **list_read, int *curs_cur);
int		rm_cur(t_read **list_read, char *buf, int *curs_cur);
int		go_right(t_read **list_read, int *curs_cur, int *is_rm);
char		*search_in_env(char **env, char *var);
void		prompt(void);
char		*list_to_str(t_read *list_read,
			     int is_clean,
			     t_historic **historic);
int		check_str(char *str);
char		**seperate_wordtab(char *str, char separator);
int		restore_term(struct termios *term_attr);
int		rm_in_list(t_read **list, int nb);
int		my_strlen(char *str);
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
int		do_redirections(t_pipe *list_pipe,
				int i,
				char **env,
				int is_redi);
char		*realloc_it(char *dest, char *src);
char		*get_next_line(const int fd);
int		is_good_string_redi(char *str, char *good_string);
char		*rm_good_string(char *str);
void		clean_screen(char **env, t_read *list_read);
int		is_builtin(char *str);
char		*make_path_builtin(char *str);
int		do_builtin(t_cmd *cmd,
			   char **environ,
			   t_pipe *list_pipe,
			   int fd_out);
char		*my_strchr(char *s, int c);
int		my_unsetenv(char ***env, char *variable);
void		usage_env(void);
char		*left_egale(char *str);
char		*right_egale(char *str);
int		my_exit(char *str);
int		my_cd(char *path, char **env);
int		my_atoi(char *str);
int		disp_env(char **env, t_env *options, t_cmd *cmd);
t_pipe		*malloc_pipe_struct(t_pipe *list_pipe,
				    int nb_cmd_pipe,
				    char **str_pipe,
				    char **env);
int		get_nb_cmd_pipe(char *str);
int		prepare_pipe(int nb_cmd_pipe,
			     int *list_in,
			     int *list_out,
			     int *list_fd);
int		exec_cmd(char **env);
char		*chose_read(char **env, int is_prompt);
char		*clean_str(char *str);
void		get_sigint(int sig);
int		update_env(char ***env, t_cmd **cmd);
int		push_historic(t_historic **historic,
			      t_read *list_read);
void		disp_list_read(t_read *list_read);
void		my_putchar(char c);
t_read		*move_in_historic(char *buf,
				  t_historic **historic,
				  t_read *list_read,
				  int *curs_cur);
int		check_str_redi(char *str);
void		close_pipe(t_pipe *list_pipe, int nb_cmd_pipe);
t_read		*create_read(char c);
int		restore_after_fork(void);
int		gmd(char *buf, int n1, int n2, int n3);
int		my_setenv(char ***env, char *variable, char *value);
int		find_all_cmd(char **str_pipe, t_pipe *list_pipe);
void		free_list_str_pipe(t_pipe *list_pipe, char **str_pipe);
void		free_str_tab(char **str_tab);
int		my_env(char **env, t_cmd *cmd, int fd_out);
int		prepare_setenv(char ***env, char *str);
int		exec_with_env(t_cmd *cmd,
			      char **env,
			      int j,
			      int null);
int		loop_exec_pipe(int nb_cmd_pipe,
			       t_pipe *l_pip,
			       char **env,
			       int is_redi);
void		wait_proc(int nb_cmd_pipe,
			  int *status,
			  int *list_fd,
			  t_pipe *list_pipe);

#endif /* !MINISH_H_ */
