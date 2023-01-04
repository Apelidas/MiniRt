
#include "test.h"

int	test_dtoint(void)
{
	double	a;

	a = 0;
	if (dtoint(a) != 0)
		return (0);
	a = 1;
	if (dtoint(a) != 10000)
		return (0);
	a = -1;
	if (dtoint(a) != -10000)
		return (0);
	a = 1.2345678;
	if (dtoint(a) != 12345)
		return (0);
	a = -1.2345678;
	if (dtoint(a) != -12345)
		return (0);
	return (1);
}
