##
## Makefile for minish2 in /home/sebastien/travaux/minishell2
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Sun Feb  9 17:43:54 2014 chapui_s
## Last update Sun Mar  9 13:00:29 2014 chapui_s
##

SRC	= main.c \
	  my_puts.c \
	  list_read.c \
	  utils.c \
	  utils2.c \
	  mod_term.c \
	  move_curs.c \
	  about_env.c \
	  prompt.c \
	  read_cmd.c \
	  list_to_str.c \
	  check_str.c \
	  seperate_wordtab.c \
	  exec_cmd.c \
	  str_to_cmd.c \
	  my_str_to_wordtab.c \
	  find_cmd.c \
	  my_strdup.c \
	  my_strcat.c \
	  get_redi.c \
	  redirections.c \
	  realloc_it.c \
	  get_next_line.c \
	  key_clean.c \
	  builtin.c \
	  my_setenv.c \
	  my_env.c \
	  my_env_exec.c \
	  my_unsetenv.c \
	  my_strchr.c \
	  builtins_complem.c \
	  my_cd.c \
	  my_atoi.c \
	  my_env_disp.c \
	  prepare_exec.c \
	  signal_funct.c \
	  list_historic.c \
	  disp_historic.c \
	  historic.c \
	  free_lists.c \
	  close_pipe.c \
	  push_read.c

NAME	= mysh

CFLAGS	= -lncurses

OBJ	= $(SRC:.c=.o)

CC	= gcc

RM	= rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
