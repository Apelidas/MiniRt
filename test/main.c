
#include "test.h"

/*
ADD automated Github Tests here
*/
int main()
{
	if (!testRest())
	{
		write(2, KRED, 5);
		write(2, "Failed testRest\n", 16);
		write(2, KNRM, 4);
		return (0);
	}
	return (1);
}