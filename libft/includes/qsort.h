#ifndef FT_QSORT_H
# define FT_QSORT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define STACK_SIZE 64
# define QBOUND		4

typedef int (*cmp_func)(const void*, const void*);

typedef struct s_qnode
{
	char *lo;
	char *hi;
}				t_qnode;

extern size_t	g_size;
extern cmp_func	g_cmp;

/*
** stack handling
*/

void	qpush(char *low, char *hi);
void	qpop(char **low, char **hi);
int		qempty(void);

/*
** sorting
*/

void	ft_qsort (void *const base, size_t nmemb, size_t size, cmp_func cmp);
void	insertsort(char *base_ptr, size_t nmemb);
void	qswap(char *a, char *b, size_t s);

#endif