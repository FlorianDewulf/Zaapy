/*
** init.c for  in /home/lund/Projets/zappy-poney/serveur
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed Jun 26 13:00:58 2013 florian dewulf
** Last update Tue Jul 16 16:55:25 2013 guillaume duez
*/

#include	<stdio.h>
#include	<string.h>
#include	"serveur.h"

static int	check_val(int val)
{
  if (val != 0)
    return (1);
  return (0);
}

static t_opt	*check(int *val, char **name_team)
{
  t_opt		*opt;
  int		i;

  i = 0;
  opt = xmalloc(sizeof(t_opt));
  opt->port = val[0];
  if (check_val(opt->port) == 0)
    {
      printf("the port cannot be null\n");
      exit(0);
    }
  opt->nb_player = xmalloc((strlen_tab(name_team) + 1) * sizeof(int));
  while (i < strlen_tab(name_team))
    {
      opt->nb_player[i] = (check_val(val[3]) == 1) ? val[3] : 4;
      i++;
    }
  opt->x_world = (check_val(val[1]) == 1) ? val[1] : 50;
  opt->y_world = (check_val(val[2]) == 1) ? val[2] : 50;
  opt->time_world = val[4];
  if (check_val(opt->time_world) == 0)
    opt->time_world = 100;
  opt->name_team = name_team;
  return (opt);
}

static int	check_tab(int i, int ac, char **av)
{
  static char	str[OPT_INT][3] = { "-p", "-x", "-y", "-c", "-t"};
  int		j;

  j = 0;
  while (j < OPT_INT)
    {
      if (strcmp(av[i], str[j]) == 0 && i + 1 < ac)
	return (j);
      j++;
    }
  return (-1);
}

static char	**manage_team(char **team, char **av, int *off)
{
  int		count;
  int		ac;
  char		**tab;
  int		nb;

  ac = -1;
  while (av[++ac]);
  count = 1;
  tab = team;
  while (*off + count < ac && check_tab(*off + count, ac, av) == -1)
    {
      nb = 0;
      while (tab && tab[nb])
	nb++;
      if ((tab = xrealloc(tab, (nb + 2) * sizeof(char *))) != NULL)
	{
	  tab[nb] = strdup(av[*off + count]);
	  tab[nb + 1] = NULL;
	}
      count++;
    }
  *off = *off + count - 2;
  return (tab);
}

void		parse_args(int ac, char **av)
{
  int		*val;
  int		i;
  char		**name_team;
  int		ret;

  val = xmalloc(sizeof(int) * OPT_INT);
  bzero(val, OPT_INT * sizeof(int));
  name_team = (i = 1) ? NULL : NULL;
  while (i < ac)
    {
      if ((ret = check_tab(i, ac, av)) != -1)
	val[ret] = atoi(av[i + 1]);
      else if (strcmp(av[i], "-n") == 0)
	name_team = manage_team(name_team, av, &i);
      else
	printf("unknow parameter :%s\n", av[i]);
      i += 2;
    }
  if (print_code_error(check_name_team(name_team)) == -1)
    exit(EXIT_FAILURE);
  run_server(check(val, name_team));
}
