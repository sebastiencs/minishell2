/*
** my_atoi.c for minish2 in /home/chapui_s/travaux/minishell2
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  6 19:19:38 2014 chapui_s
** Last update Thu Mar  6 19:19:43 2014 chapui_s
*/

int	my_atoi(char *str)
{
  int	i;
  int	negativ;
  int	number;

  i = 0;
  negativ = 0;
  number = 0;
  while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
	 || (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
    i++;
  if (str[i] == 45)
    negativ = 1;
  if ((str[i] == 45) || (str[i] == 43))
    i++;
  while (str[i] >= 48 && str[i] <= 57)
  {
    number *= 10;
    number += ((int)str[i] - 48);
    i++;
  }
  if (negativ == 1)
    return (-number);
  else
    return (number);
}
