##
## Makefile for minish2 in /home/sebastien/travaux/minishell2
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Sun Feb  9 17:43:54 2014 chapui_s
## Last update Thu Mar  6 19:19:54 2014 chapui_s
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
	  my_atoi.c

NAME	= mysh

CFLAGS	= -lncurses -ggdb

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
