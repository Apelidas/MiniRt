#include "operations.h"


// t_vec3d *vec3d_project(t_vec3d *a, t_vec3d *b)
// {
// 	double	dot;
// 	double	mag;
// 	t_vec3d	*res;

// 	dot = vec3d_dot(a, b);
// 	mag  = sqrt(b->x * b->x + b->y * b->y + b->z * b->z);
// 	res = vec3d_cpy(b);
// 	vec3d_mult(res, dot / (mag * mag));
// 	free(b);
// 	return (res);
// }

// t_vec3d *cyl_ray_inter(t_cylinder *cyl, t_ray *ray)
// {
// 	double		dot;
// 	t_vec3d		*proj;
// 	t_vec3d		*delta;
// 	double		distance;
// 	double		t;
// 	double		y;
// 	t_vec3d		*tmp;
// 	t_vec3d		*endcap1;
// 	t_vec3d		*endcap2;
// 	t_vec3d		*intersection;

// 	dot = vec3d_dot(ray->dir, cyl->norm);
// 	if (dot == 0)
// 		return (NULL);
// 	proj = vec3d_project(cyl->norm, vec3d_sub(ray->origin, cyl->origin));
// 	delta = vec3d_sub(proj, cyl->origin);
// 	distance = vec3d_dot(delta, cyl->norm);
// 	if (distance < 0 || distance > cyl->h)
// 		return (NULL);
// 	t = vec3d_dot(vec3d_sub(proj, ray->origin), cyl->norm) / dot;
// 	if (t < 0)
// 		return (NULL);
// 	tmp = vec3d_cpy(ray->dir);
// 	vec3d_mult(tmp, t);
// 	intersection = vec3d_add(ray->origin, tmp);
// 	y = vec3d_dot(vec3d_sub(intersection, cyl->origin), cyl->norm);
// 	if (y < 0 || y > cyl->h)
// 		return (NULL);
// 	vec3d_mult(cyl->norm, cyl->h);
// 	endcap1 = vec3d_add(cyl->origin, cyl->norm);
// 	endcap2 = vec3d_sub(cyl->origin, cyl->norm);
// 	if (vec3d_len(vec3d_sub(intersection, endcap1)) < cyl->d / 2
// 		|| vec3d_len(vec3d_sub(intersection, endcap2)) < cyl->d / 2)
// 		return (intersection);
// 	return (NULL);
// }

t_vec3d *mantle(t_cylinder *cyl, t_ray *ray)
{
	t_vec3d *intersect;
	double a;
	double b;
	double c;
	double disc;
	double t1;
	double t2;
	t_vec3d *oc;
	t_vec3d *od;
	
	oc = vec3d_sub(ray->origin, cyl->origin);
	a = vec3d_dot(ray->dir, ray->dir) - pow(vec3d_dot(ray->dir, cyl->norm), 2);
	b = 2 * (vec3d_dot(oc, ray->dir) - vec3d_dot(oc, cyl->norm) * vec3d_dot(ray->dir, cyl->norm));
	c = vec3d_dot(oc, oc) - pow(vec3d_dot(oc, cyl->norm), 2) - pow(cyl->d, 2);
	disc = pow(b, 2) - 4 * a * c;
	free(oc);
	if (disc < 0)
		return (NULL);
	t1 = (-b + sqrt(disc)) / (2 * a);
	t2 = (-b - sqrt(disc)) / (2 * a);
	if ((t1 <= 0 && t2 <= 0) || (t1 != t1 && t2 != t2))
		return (NULL);
	if (t1 > 0 && t2 > 0)
		t1 = fmin(t1, t2);
	else if (t2 > 0)
		t1 = t2;
	vec3d_mult(ray->dir, t1);
	od = vec3d_cpy(ray->dir);
	intersect = vec3d_add(ray->origin, od);
	free(od);
	if (vec3d_dot(vec3d_sub(intersect, cyl->origin), cyl->norm) < 0 ||
		vec3d_dot(vec3d_sub(intersect, cyl->origin), cyl->norm) > cyl->h)
	{
		free(intersect);
		return (NULL);
	}
	return (intersect);
}

t_vec3d	*mantle_circle(t_ray *ray, t_cyl *cyl, t_vec3d *point)
{
	t_vec3d	*mant;

	mant = mantle(cyl, ray);
	if (mant == NULL)
		return (point);
	return (is_closer(ray, point, mant));
}

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

// static t_vec3d	*mantle_circle(t_ray *ray, t_cylinder *cyl, t_vec3d *a)
// {
// 	t_vec3d	*help;
// 	t_vec3d	*norm;
// 	t_plane	*plane;

// 	help = vec3d_cross(ray->dir, cyl->norm);
// 	norm = vec3d_cross(cyl->norm, help);
// 	vec3d_norm(norm);
// 	vec3d_mult(norm, (cyl->d / 2));
// 	free(help);
// 	help = create_vec3d(cyl->origin->x + norm->x, cyl->origin->y + norm->y,
// 			cyl->origin->z + norm->z);
// 	plane = create_plane(help, norm, 0);
// 	help = cyl_plane_ray(ray, plane);
// 	norm = create_vec3d(cyl->origin->x - help->x, cyl->origin->y - help->y,
// 			cyl->origin->z - help->z);
// 	destroy_plane(plane);
// 	if (vec3d_angle(norm, cyl->norm) < 90)
// 		return (help);
// 	free(norm);
// 	norm = create_vec3d(cyl->origin->x + help->x, cyl->origin->y + help->y,
// 			cyl->origin->z + help->z);
// 	free(help);
// 	return (is_closer(ray, a, norm));
// }

// static t_vec3d	*mantle_closer(t_ray *ray, t_cyl *cyl, t_vec3d *a, t_vec3d *b)
// {
// 	double	dist;
// 	double	dist_a;
// 	double	dist_b;

// 	dist = sqrt(pow(cyl->h, 2) + pow(cyl->d / 2, 2));
// 	dist_a = vec3d_dist(a, cyl->origin);
// 	dist_b = vec3d_dist(b, cyl->origin);
// 	if (dist_a > dist && dist_b > dist)
// 	{
// 		free(a);
// 		free(b);
// 		return (NULL);
// 	}
// 	if (dist_a > dist)
// 	{
// 		free(a);
// 		return (b);
// 	}
// 	if (dist_b > dist)
// 	{
// 		free(b);
// 		return (a);
// 	}
// 	return (is_closer(ray, a, b));
// }

// static t_vec3d	*mantle(t_ray *ray, t_cyl *cyl)
// {
// 	t_vec3d	*tmp;
// 	t_vec3d	*norm;
// 	t_plane	*help;
// 	t_ray	*cyl_ray;
// 	double	dist;

// 	norm = vec3d_cross(ray->dir, cyl->norm);
// 	help = create_plane(vec3d_cpy(cyl->origin), vec3d_cross(norm, cyl->norm), 0);
// 	vec3d_norm(help->norm);
// 	tmp = plane_ray_inter(ray, help);
// 	cyl_ray = create_vray(cyl->origin, cyl->norm, 0);
// 	dist = ray_vec3d_dist(cyl_ray, tmp);
// 	free(cyl_ray);
// 	free(norm);
// 	if (dist > cyl->d / 2)
// 	{
// 		free(tmp);
// 		return (NULL);
// 	}
// 	if (cmp_d(dist, cyl->d / 2))
// 	{
// 		destroy_plane(help);
// 		return (tmp);
// 	}
// 	vec3d_mult(help->norm, (cyl->d / 2) - dist);
// 	free(tmp);
// 	tmp = help->origin;
// 	help->origin = vec3d_sub(tmp, help->norm);
// 	norm = plane_ray_inter(ray, help);
// 	free(help->origin);
// 	help->origin = vec3d_add(tmp, help->norm);
// 	free(tmp);
// 	tmp = plane_ray_inter(ray, help);
// 	destroy_plane(help);
// 	if (!tmp)
// 		return (norm);
// 	if (!norm)
// 		return (tmp);
// 	return (mantle_closer(ray, cyl, tmp, norm));
// }

// static t_vec3d	*mantle_help(t_ray *ray, t_cyl *cyl, t_vec3d *a, double dist)
// {
// 	double	angle;
// 	t_vec3d	*help;

// 	angle = vec3d_angle(a, cyl->norm);
// 	if (angle > 90)
// 	{
// 		free(a);
// 		return (NULL);
// 	}
// 	if (dist / sin(angle) > cyl->h)
// 	{
// 		free(a);
// 		return (NULL);
// 	}
// 	dist = (cyl->d / 2) - dist;
// 	angle = vec3d_angle(ray->dir, cyl->norm);
// 	dist = dist / sin(angle);
// 	vec3d_norm(ray->dir);
// 	vec3d_mult(ray->dir, dist);
// 	help = is_closer(ray, vec3d_add(a, ray->dir), vec3d_sub(a, ray->dir));
// 	free(a);
// 	return (help);
// }

// static t_vec3d	*mantle(t_ray *ray, t_cylinder *cyl)
// {
// 	t_plane	*help;
// 	t_vec3d	*a;
// 	t_vec3d	*b;
// 	double	dist;

// 	a = vec3d_cross(ray->dir, cyl->norm);
// 	b = vec3d_cross(cyl->norm, a);
// 	help = create_plane(cyl->origin, b, 0);
// 	free(a);
// 	a = plane_ray_inter(ray, help);
// 	free(help);
// 	dist = cyl_dist(a, cyl);
// 	free(b);
// 	if (dist > cyl->d / 2)
// 	{
// 		free(a);
// 		return (NULL);
// 	}
// 	if (cmp_d(dist, cyl->d / 2))
// 		return (a);
// 	if (cmp_d(dist, 0))
// 	{
// 		dist = (cyl->d / 2) / sin(vec3d_angle(ray->dir, cyl->norm));
// 		vec3d_norm(ray->dir);
// 		vec3d_mult(ray->dir, dist);
// 		b = is_closer(ray, vec3d_add(a, ray->dir), vec3d_sub(a, ray->dir));
// 		free(a);
// 		return (b);
// 	}
// 	return (mantle_help(ray, cyl, a, dist));
// }

// t_vec3d	*cyl_ray_inter(t_cylinder *cyl, t_ray *ray)
// {
// 	t_vec3d	*tmp;
// 	t_vec3d	*a;
// 	t_vec3d	*b;

// 	vec3d_norm(cyl->norm);
// 	vec3d_mult(cyl->norm, cyl->h);
// 	tmp = create_vec3d(cyl->origin->x + cyl->norm->x, cyl->origin->y
// 			+ cyl->norm->y, cyl->origin->z + cyl->norm->z);
// 	a = ray_circle_inter(ray, cyl->norm, cyl->origin, cyl->d / 2);
// 	b = ray_circle_inter(ray, cyl->norm, tmp, cyl->d / 2);
// 	free(tmp);
// 	if (a && b)
// 		return (on_ray(ray, a, b));
// 	if (a && !b)
// 		return (mantle_circle(ray, cyl, a));
// 	if (!a && b)
// 	{
// 		cylinder_reverse(cyl);
// 		return (mantle_circle(ray, cyl, b));
// 	}
// 	return (mantle(ray, cyl));
// }
