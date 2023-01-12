#include "../miniRT.h"

int	get_b(int color)
{
	int	r;

	r = color & 0xFF;
	return (r);
}

int	get_g(int color)
{
	int	r;

	r = (color >> 8) & 0xFF;
	return (r);
}

int	get_r(int color)
{
	int	r;

	r = (color >> 16) & 0xFF;
	return (r);
}

int	get_t(int color)
{
	int	r;

	r = (color >> 24) & 0xFF;
	return (r);
}

/*
takes 4 int (0 - 255)
returns int or -1 if error
*/
int	get_trgb(unsigned int t, unsigned int r, unsigned int g, unsigned int b)
{
	int	out;

	if (t > 255 || r > 255 || g > 255 || b > 255)
		return (-1);
	out = 0;
	set_t(&out, t);
	set_r(&out, r);
	set_g(&out, g);
	set_b(&out, b);
	return (out);
}
