#include "qsort.h"

size_t		g_size;
cmp_func	g_cmp;

/*
** Figure out the median value out of three elements:
** the first element in the array, the last one, and the one in the middle.
** Swap those elements around so they're already in order.
*/

static char	*median(char **lo, char **hi)
{
	char *mid;

	mid = *lo + g_size * (((*hi - *lo) / g_size) >> 1);
	if (g_cmp(mid, *lo) < 0)
		qswap(mid, *lo, g_size);
	if (g_cmp(*hi, mid) < 0)
		qswap(mid, *hi, g_size);
	else
		return (mid);
 	if (g_cmp(mid, *lo) < 0)
		qswap(mid, *lo, g_size);
	return (mid);
}

/*
** move the pointers toward the middle until the comparison of the pointed
** values with the pivot returns false, then swap them if they're on the
** wrong side of the pivot.
** If the swap occurs and the pivot was one of the swapped values,
** update the mid pointer so it keeps pointing to the
** same value instead of the same place in the array.
**
**	can a while replace the do_while ?
**	>> while (left_ptr <= right_ptr);
*/

static void	traverse(char **left_ptr, char **right_ptr, char **mid)
{
	while (*left_ptr <= *right_ptr)
	{
		while (g_cmp(*left_ptr, *mid) < 0)
			*left_ptr += g_size;
		while (g_cmp(*right_ptr, *mid) > 0)
			*right_ptr -= g_size;
		if (*left_ptr < *right_ptr)
		{
			qswap(*left_ptr, *right_ptr, g_size);
			if (*mid == *left_ptr)
				*mid = *right_ptr;
			else if (*mid == *right_ptr)
				*mid = *left_ptr;
			*left_ptr += g_size;
			*right_ptr -= g_size;
		}
		else if (*left_ptr == *right_ptr)
		{
			*left_ptr += g_size;
			*right_ptr -= g_size;
//			return ;
		}
	}
}

/*
** Push the bounds of the biggest partition on the stack if it's still higher
** than the minimum partition size (QBOUND), and keep processing the
** smallest one.
** If the QBOUND had been reached, pop the first node of the stack, update
** the boundaries pointers, and process it.
*/

static void	partition(char **left_ptr, char **right_ptr, char **lo, char **hi)
{
	const size_t	bound = QBOUND * g_size;

	if ((size_t)(*right_ptr - *lo) <= bound)
	{
		if ((size_t)(*hi - *left_ptr) <= bound)
			qpop(lo, hi);
		else
			*lo = *left_ptr;
	}
	else if ((size_t)(*hi - *left_ptr) <= bound)
		*hi = *right_ptr;
	else if ((*right_ptr - *lo) > (*hi - *left_ptr))
	{
		qpush(*lo, *right_ptr);
		*lo = *left_ptr;
	}
	else
	{
		qpush(*left_ptr, *hi);
		*hi = *right_ptr;
	}
}

/*
** left and right pointers are set to the second element from each end
** of the array, because the first one, the middle one and the last one
** are already put in order while determining the pivot. 
** keep sorting and partitioning until the stack is empty,
** at which point all the partitions are small enough that quicksort isn't
** efficient anymore, and a different sorting algorithm can be used instead.
*/

static void	quicksort(char *lo, size_t nmemb)
{
	char	*hi;
	char	*left_ptr;
	char	*right_ptr;
	char	*mid;

	qpush(NULL, NULL);
	hi = lo + g_size * (nmemb - 1);
	while (!qempty())
	{
		mid = median(&lo, &hi);
		left_ptr = lo + g_size;
		right_ptr = hi - g_size;
		traverse(&left_ptr, &right_ptr, &mid);
		partition(&left_ptr, &right_ptr, &lo, &hi);
	}
}

/*
** base:	the array to sort
** nmemb:	the number of elements in the array
** size:	the size of each element
** cmp:		a pointer to the comparison function
*/

void		ft_qsort (void *const base, size_t nmemb, size_t size, cmp_func cmp)
{
	char	*base_ptr;
	g_size = size;
	g_cmp = cmp;

	base_ptr = (char*)base;
	if (nmemb == 0)
		return;
	if (nmemb > QBOUND)
		quicksort(base_ptr, nmemb);
//	smallsort(base_ptr, nmemb);
	insertsort(base_ptr, nmemb);
}
