/*
** signal_funct.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  8 00:36:56 2014 chapui_s
** Last update Sat Mar  8 00:37:36 2014 chapui_s
*/

void	get_sigint(int sig)
{
  my_putstr("\n");
  prompt();
}
