
#include "../miniRT.h"

void	set_b(int *color, int b)
{
	*color = *color + b;
}

void	set_g(int *color, int g)
{
	int	help;

	help = *color;
	help = (help >> 8) + g;
	*color = help << 8;
}

void	set_r(int *color, int r)
{
	int	help;

	help = *color;
	help = (help >> 16) + r;
	*color = help << 16;
}

void	set_t(int *color, int t)
{
	int	help;

	help = *color;
	help = (help >> 24) + t;
	*color = help << 24;
}
