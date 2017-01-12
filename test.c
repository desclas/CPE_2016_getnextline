/*
** test.c for  in /home/mathias/Bureau/GTN
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Fri Jan  6 09:49:58 2017 Mathias
** Last update Thu Jan 12 18:08:56 2017 Mathias
*/

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void inistr(char *str, int max)
{
  int i;

  i = 0;
  while (i != max)
    {
      str[i] = '\0';
      i += 1;
    }
}

char *my_strcpy2(char *tmp, char *save, int *i)
{
  while (save[*i] != '\0')
    {
      tmp[*i] = save[*i];
      *i += 1;
    }
  return (tmp);
}

char *my_strcpy3(char *tmp, char *memo, int i)
{
  int count;

  count = 0;
  while (memo[count] != '\0')
    {
      tmp[i] = memo[count];
      i += 1;
      count += 1;
    }
  return (tmp);
}

char *my_strcpy4(char *tmp, char *save, int i)
{
  int count;

  count = 0;
  while (tmp[i] != '\0')
    {
      save[count] = tmp[i];
      i += 1;
      count += 1;
    }
}

char *my_strcpy5(char *tmp, char *save, int *i)
{
  while (save[*i] != '\n')
    {
      tmp[*i] = save[*i];
      *i += 1;
    }
}

char *my_strcpy(char *memo, char *save, int len)
{
  char *tmp;
  int i;
  int count;

  i = 0;
  count = 0;
  if (save != NULL)
    {
      tmp = malloc(sizeof(char) * len);
      inistr(tmp, len);
      tmp = my_strcpy2(tmp, save, &i);
      free(save);
      tmp = my_strcpy3(tmp, memo, i);
      return (tmp);
    }
  else
    {
      save = malloc(sizeof(char) * len);
      while (memo[i] != '\0')
	{
	  save[i] = memo[i];
	  i += 1;
	}
      return (save);
    }
}

char *befor_display(t_gnl *all, char *save)
{
  char *tmp;
  int i;

  i = 0;
  tmp = malloc(sizeof(char) * all->len);
  inistr(tmp, all->len);
  my_strcpy2(tmp, save, &i);
  my_strcpy3(tmp, all->memo, i);
  free(all->memo);
  free(save);
  all->memo = malloc(sizeof(char) * all->len);
  save = malloc(sizeof(char) * all->len);
  inistr(all->memo, all->len);
  inistr(save, all->len);
  i = 0;
  my_strcpy5(all->memo, tmp, &i);
  if (tmp[i + 1] != '\0')
    save = my_strcpy3(save, tmp, i);
  free(tmp);
  return (save);
}

char *no_save(t_gnl *all, char *save, int fd)
{
  while (all->st != 0 && all->st != -1 && all->memo[all->i] != '\n')
    {
      all->i = 0;
      all->len += READ_SIZE;
      all->memo = malloc(sizeof(char) * READ_SIZE + 1);
      inistr(all->memo, READ_SIZE);
      all->st = read(fd, all->memo, READ_SIZE + 1);
      while (all->memo[all->i] != '\n' && all->memo[all->i] != '\0')
	all->i += 1;
      if (all->memo[all->i] == '\0')
	save = my_strcpy(all->memo, save, all->len);
      if (all->memo[all->i] != '\n' && all->memo[all->i] != '\0')
	free(all->memo);
    }
  save = befor_display(all, save);
  return (save);
}

int check_save(char *str)
{
  int i;

  i = 0;
  while (str[i] != '\n' && str[i] != '\0')
    i += 1;
  if (str[i] == '\n')
    return (1);
  else
    return (0);
}

int my_len(char *str)
{
  int i;

  i = 0;
  while (str[i] != '\0')
    i += 1;
  return (i);
}

char *line_save(t_gnl *all, char *save)
{
  char *tmp;
  int i;
  int len;

  i = 0;
  len = my_len(save);
  tmp = malloc(sizeof(char) * len);
  all->memo = malloc(sizeof(char) * len);
  inistr(tmp, len);
  inistr(all->memo, len);
  all->memo = my_strcpy2(all->memo, save, &i);
  tmp = my_strcpy3(tmp, save, i);
  free(save);
  return (tmp);
}

char *get_next_line(const int fd)
{
  static char *save = NULL;
  t_gnl *all;

  all = malloc(sizeof(*all));
  all->len = 1;
  all->i = 0;
  all->st = 4;
  all->memo = "a";
  if (save == NULL)
    {
      save = no_save(all, save, fd);
      return (all->memo);
    }
  else
    {
      if (check_save(save) == 1)
	{
	  save = line_save(all, save);
	  return (all->memo);
	}
      else
	{
	  save = no_save(all, save, fd);
	  return (all->memo);
	}
    }
}
