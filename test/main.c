
#include "test.h"

int run_test(char *name, int (*test)())
{
	write(1, KBLU, 5);
	write(1, name, ft_strlen(name));
	write(1, ": ", 2);
	if (!(*test)())
	{
		write(1, KRED, 5);
		write(1, "Failed\n", 7);
		write(1, KNRM, 4);
		return (0);
	}
	else
	{
		write(1, KGRN, 5);
		write(1, "OK\n", 3);
		write(1, KNRM, 4);
		return (1);
	}
}

/*
ADD automated Github Tests here
*/
int main()
{
	// write(2, KRED, 5);
	// write(2, "Failed\n", 7);
	// write(2, KNRM, 4);
	if (!run_test("testRest", &testRest))
		return (0);
	return (1);
}