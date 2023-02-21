#include "operations.h"

int	cyl_inside(t_cylinder *cyl, t_camera *cam)
{
	t_ray	*help;
	t_vec3d	*front;
	t_vec3d	*back;
	int		out;

	out = 0;
	help = create_vray(cam->pos, cam->dir, 0);
	front = cyl_ray_inter(cyl, help);
	vec3d_mult(cam->dir, -1);
	back = cyl_ray_inter(cyl, help);
	vec3d_mult(cam->dir, -1);
	free(help);
	if (front && back)
		out = 1;
	if (front)
		free(front);
	if (back)
		free(back);
	return (out);
}
