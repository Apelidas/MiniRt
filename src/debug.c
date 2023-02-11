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

void	print_ray(t_ray *a)
{
	if (!a)
	{
		write(2, "Ray is NULL\n", 15);
		return ;
	}
	printf("origin:\n");
	print_vec3d(a->origin);
	printf("dir:\n");
	print_vec3d(a->dir);
	printf("color:\n%d\n", a->trgb);
}

void	print_plane(t_plane *a)
{
	if (!a)
	{
		write(2, "Plane is NULL\n", 15);
		return ;
	}
	printf("origin:\n");
	print_vec3d(a->origin);
	printf("norm:\n");
	print_vec3d(a->norm);
	printf("color:\n%d\n", a->trgb);
	printf("surface:\n%d\n", a->surface_type);
}

void	print_cyl(t_cylinder *a)
{
	if (!a)
	{
		write(2, "Cyl is NULL\n", 15);
		return ;
	}
	printf("origin:\n");
	print_vec3d(a->origin);
	printf("norm:\n");
	print_vec3d(a->norm);
	printf("diameter:\n%f\nheight:\n%f\ncolor:\n%d\n", a->d, a->h, a->trgb);
	printf("surface:\n%d\n", a->surface_type);
}
