
int	cmp_d(double a, double b)
{
	double	err;

	err = 0.0000001;
	if (a - err < b && a + err > b)
		return (1);
	return (0);
}
