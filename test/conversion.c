
#include "test.h"

int	test_cmp_d(void)
{
	if (!cmp_d(0, 0))
		return (0);
	if (!cmp_d(1, 1))
		return (0);
	if (!cmp_d(1.23456, 1.23456))
		return (0);
	if (!cmp_d(-1.23456, -1.23456))
		return (0);
	if (cmp_d(1.2345678, 1.3456782))
		return (0);
	return (1);
}
