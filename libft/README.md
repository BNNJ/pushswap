# libft

42 project\
Personal and customized C library

## Most useful functions

ft_qsort:\
void ft_qsort(void \*base, size_t nmemb, size_t size, int (\*cmp)(void\*, void\*))\
&emsp; base: a pointer to the beginning of thearray to sort\
&emsp; nmemb: the number of elements in the array\
&emsp; size: the size of an element\
&emsp; cmp: the comparison function\
Based on GNU quicksort

get_next_line:\
int	get_next_line(int fd, char \*\*line)\
&emsp; fd: the file descriptor to be read\
&emsp; line: a pointer to a string, in which the next line read will be stored\
If line is NULL, the data corresponding to the fd will be freed.

ft_getopt:\
int ft_getopt(char const \*\*argv, char const \*optstr, char const \*\*opttab)\
&emsp; argv: the arguments to parse\
&emsp; opstr: a string containing the options letters\
&emsp; opttab: an array of string representing the long options\
returns an int that is functionnally a bitfield, where each bit is a boolean 
representing an option. The first option in optstr is the rightmost bit.

## TODO

Reorganize and clean libft.h\
finish porting the insertsort part of ft_qsort