
#include "test.h"

/*
Readability and Norminette Function
*/
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
	write(1, KGRN, 5);
	write(1, "OK\n", 3);
	write(1, KNRM, 4);
	return (1);
}

/*
ADD automated Github Tests here
this main runs the automated GitHub tests
*/
int main()
{
	if (!run_test("testRest", &testRest))
		return (1);
	return (0);
}