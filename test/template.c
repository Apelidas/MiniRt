#include "test.h"
/*
Example of how to design a Test
*/
int	rest(unsigned int a, unsigned int b)
{
	int	tmp;

	if (b == 0)
		return (-1);
	tmp = a / b;
	tmp = b * tmp;
	return (a - tmp);
}

int	test_rest(void)
{
	if (rest(0, 0) != -1)
		return (0);
	if (rest(10, 0) != -1)
		return (0);
	if (rest(UINT_MAX, 0) != -1)
		return (0);
	if (rest(20, 10) != 0)
		return (0);
	if (rest(20, 3) != 2)
		return (0);
	return (1);
}
