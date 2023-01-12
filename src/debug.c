#include "../miniRT.h"

void	print_vec3d(t_vec3d *a)
{
	if (!a)
	{
		write(2, "Vector is NULL\n", 15);
		return ;
	}
	printf("x: %f\ty: %f\tz: %f\n", a->x, a->y, a->z);
}