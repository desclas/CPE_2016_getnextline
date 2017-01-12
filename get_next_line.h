/*
** get_next_line.h for  in /home/mathias/Bureau/GTN
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Fri Jan  6 13:22:47 2017 Mathias
** Last update Tue Jan 10 17:00:13 2017 Mathias
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# ifndef READ_SIZE
#  define READ_SIZE (7)
# endif /* !READ_SIZE */

# include <unistd.h>
# include <stdlib.h>

typedef struct s_gnl
{
  char *memo;
  int i;
  int len;
  int st;
}		t_gnl;

#endif /* !GET_NEXT_LINE_H_ */
