#include "operations.h"

/**
 * @brief calculates the multiplier for the shortest intersection with cyl-mantle
 * 
 * @param cyl 
 * @param ray 
 * @return double
 */
double	calculate_closer_t(t_cylinder *cyl, t_ray *ray)
{
	t_vec3d	help;
	t_vec3d	tmp;
	t_vec3d	*oc;

	oc = vec3d_sub(ray->origin, cyl->origin);
	help.x = vec3d_dot(ray->dir, ray->dir)
		- pow(vec3d_dot(ray->dir, cyl->norm), 2);
	help.y = 2 * (vec3d_dot(oc, ray->dir)
			- vec3d_dot(oc, cyl->norm) * vec3d_dot(ray->dir, cyl->norm));
	help.z = vec3d_dot(oc, oc)
		- pow(vec3d_dot(oc, cyl->norm), 2) - pow(cyl->d, 2);
	tmp.x = pow(help.y, 2) - 4 * help.x * help.z;
	free(oc);
	if (tmp.x < 0)
		return (-1);
	tmp.y = (-help.y + sqrt(tmp.x)) / (2 * help.x);
	tmp.z = (-help.y - sqrt(tmp.x)) / (2 * help.x);
	if ((tmp.y <= 0 && tmp.z <= 0) || (tmp.y != tmp.y && tmp.z != tmp.z))
		return (-1);
	if (tmp.y > 0 && tmp.z > 0)
		tmp.y = fmin(tmp.y, tmp.z);
	else if (tmp.z > 0)
		tmp.y = tmp.z;
	return (tmp.y);
}

/**
 * @brief calculates the intersection with the mantle of the cylinder
 * 
 * @param cyl 
 * @param ray 
 * @return t_vec3d* 
 */
t_vec3d	*mantle(t_cylinder *cyl, t_ray *ray)
{
	t_vec3d	*inter;
	double	t;

	t = calculate_closer_t(cyl, ray);
	if (t < 0)
		return (NULL);
	vec3d_mult(ray->dir, t);
	inter = vec3d_add(ray->origin, ray->dir);
	if (vec3d_dot(vec3d_sub(inter, cyl->origin), cyl->norm) < 0
		|| vec3d_dot(vec3d_sub(inter, cyl->origin), cyl->norm) > cyl->h)
	{
		free(inter);
		return (NULL);
	}
	return (inter);
}

/**
 * @brief calculates closer point to origin of both intersections
 * 
 * @param ray 
 * @param cyl 
 * @param point 
 * @return t_vec3d* 
 */
t_vec3d	*mantle_circle(t_ray *ray, t_cyl *cyl, t_vec3d *point)
{
	t_vec3d	*mant;

	mant = mantle(cyl, ray);
	if (mant == NULL)
		return (point);
	return (is_closer(ray, point, mant));
}

/**
 * @brief calculates intersection point. NULL if not
 * 
 * @param cyl 
 * @param ray 
 * @return t_vec3d* 
 */
t_vec3d	*cyl_ray_inter(t_cylinder *cyl, t_ray *ray)
{
	t_vec3d	*tmp;
	t_vec3d	*a;
	t_vec3d	*b;

	vec3d_norm(cyl->norm);
	vec3d_mult(cyl->norm, cyl->h);
	tmp = create_vec3d(cyl->origin->x + cyl->norm->x, cyl->origin->y
			+ cyl->norm->y, cyl->origin->z + cyl->norm->z);
	a = ray_circle_inter(ray, cyl->norm, cyl->origin, cyl->d);
	b = ray_circle_inter(ray, cyl->norm, tmp, cyl->d);
	free(tmp);
	if (a && b)
		return (on_ray(ray, a, b));
	if (a && !b)
		return (mantle_circle(ray, cyl, a));
	if (!a && b)
		return (mantle_circle(ray, cyl, b));
	return (mantle(cyl, ray));
}

t_vec3d	*is_closer(t_ray *ray, t_vec3d *a, t_vec3d *b)
{
	if (vec3d_dist(b, ray->origin) > vec3d_dist(a, ray->origin))
	{
		free(b);
		return (a);
	}
	free(a);
	return (b);
}
