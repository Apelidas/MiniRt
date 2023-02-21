#include "operations.h"

t_cylinder	*create_cylinder(t_vec3d *origin, t_vec3d *n, double d, double h)
{
	t_cylinder	*out;

	out = malloc(sizeof(t_cylinder));
	if (!out)
		return (NULL);
	out->origin = origin;
	out->norm = n;
	out->d = d;
	out->h = h;
	return (out);
}

void	destroy_cylinder(t_cylinder *cyl)
{
	if (!cyl)
		return ;
	if (cyl->origin)
		free(cyl->origin);
	if (cyl->norm)
		free(cyl->norm);
	free(cyl);
}

t_vec3d	*on_ray(t_ray *ray, t_vec3d *a, t_vec3d *b)
{
	int	ra;
	int	rb;

	ra = ray_vec3d(ray, a);
	rb = ray_vec3d(ray, b);
	if (ra && rb)
		return (is_closer(ray, a, b));
	if (ra && !rb)
	{
		free(b);
		return (a);
	}
	if (!ra && rb)
	{
		free(a);
		return (b);
	}
	free(a);
	free(b);
	return (NULL);
}

t_vec3d	*cyl_norm(t_cylinder *cyl, t_ray *ray_in, t_vec3d *point)
{
	t_vec3d	*tmp;
	t_vec3d	*norm;

	tmp = ray_circle_inter(ray_in, cyl->norm, cyl->origin, 0);
	if (tmp)
	{
		free(tmp);
		return (vec3d_cpy(cyl->norm));
	}
	vec3d_norm(cyl->norm);
	vec3d_mult(cyl->norm, cyl->h);
	norm = vec3d_add(cyl->origin, cyl->norm);
	vec3d_norm(cyl->norm);
	tmp = ray_circle_inter(ray_in, cyl->norm, norm, 0);
	free(norm);
	if (tmp)
	{
		free(tmp);
		return (vec3d_cpy(cyl->norm));
	}
	tmp = vec3d_cross(point, cyl->norm);
	norm = vec3d_cross(cyl->norm, tmp);
	vec3d_norm(norm);
	free(tmp);
	return (norm);
}

t_ray	*cyl_ray_reflec(t_cylinder *cyl, t_ray *ray_in, t_vec3d *point)
{
	t_vec3d	*norm;
	t_ray	*out;

	norm = cyl_norm(cyl, ray_in, point);
	vec3d_mult(norm, 2 * vec3d_dot(ray_in->dir, norm));
	out = create_vray(point, vec3d_sub(ray_in->dir, norm), 0);
	free(norm);
	return (out);
}
