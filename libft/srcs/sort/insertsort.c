#include "qsort.h"

static char	*qmin(char *a, char *b)
{
	return (a > b ? b : a);
}

static void	traverse(char *run_ptr, char *end_ptr)
{
	char	*tmp_ptr;
	char	*trav;
	char	*hi;
	char	*lo;
	char	c;

	while ((run_ptr += g_size) <= end_ptr)
	{
		tmp_ptr = run_ptr - g_size;
		while (g_cmp(run_ptr, tmp_ptr) < 0)
			tmp_ptr -= g_size;
		tmp_ptr += g_size;
		if (tmp_ptr != run_ptr)
		{
			trav = run_ptr + g_size;
			while (--trav >= run_ptr)
			{
				c = *trav;
				hi = trav;
				lo = trav;
//				for (hi = lo = trav; (lo -= g_size) >= tmp_ptr; hi = lo)
//					*hi = *lo;
				while ((lo -= g_size) >= tmp_ptr)
				{
					*hi = *lo;
					hi = lo;
				}
				*hi = c;
			}
		}
	}
}

void		insertsort(char *base_ptr, size_t nmemb)
{
	char	*end_ptr;
	char	*tmp_ptr;
	char	*bound;
	char	*run_ptr;

	end_ptr = base_ptr + g_size * (nmemb - 1);
	tmp_ptr = base_ptr;
	run_ptr = base_ptr + g_size;
	bound = qmin(end_ptr, base_ptr + QBOUND * g_size);
	while (run_ptr <= bound)
	{
		if (g_cmp(run_ptr, tmp_ptr) < 0)
			tmp_ptr = run_ptr;
		run_ptr += g_size;
	}
	if (tmp_ptr != base_ptr)
		qswap(tmp_ptr, base_ptr, g_size);
	traverse(base_ptr + g_size, end_ptr);
}
