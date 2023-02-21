#include "../miniRT.h"

void	sphere_intersection_norm(double c[3], t_sphere *sphr, t_ray *ray)
{
	t_vec3d	*tmp;

	tmp = vec3d_minus(ray->origin, sphr->origin);
	c[0] = vec3d_dot(ray->dir, ray->dir);
	c[1] = 2 * vec3d_dot(ray->dir, tmp);
	c[2] = vec3d_dot(tmp, tmp) - pow(sphr->d / 2, 2);
	free(tmp);
}

double	sphere_intersection(t_ray *ray, t_sphere *sphr)
{
	double	c[3];
	double	delta;
	double	t1;
	double	t2;

	sphere_intersection_norm(c, sphr, ray);
	delta = pow(c[1], 2) - 4 * c[0] * c[2];
	if (delta < 0)
		return (-1);
	t1 = (-c[1] + sqrt(delta)) / (2 * c[0]);
	t2 = (-c[1] - sqrt(delta)) / (2 * c[0]);
	if (t1 >= 0 && t2 >= 0)
	{
		if (t1 > t2)
			return (t2);
		return (t1);
	}
	else if (t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	return (-1);
}

t_ray	*make_ray(t_data *info, double x, double y)
{
	t_vec3d	*tmp;
	t_vec3d	*right;
	t_vec3d	*up;
	t_vec3d	up_guide;
	t_ray	*ray;

	up_guide.x = 0;
	up_guide.y = 1;
	up_guide.z = 0;
	vec3d_norm(info->cam->dir);
	right = vec3d_cross(info->cam->dir, &up_guide);
	vec3d_norm(right);
	up = vec3d_cross(right, info->cam->dir);
	vec3d_norm(up);
	vec3d_mult(right, x);
	vec3d_mult(up, y);
	tmp = vec3d_plus(right, up);
	ray = create_vray(vec3d_cpy(info->cam->pos),
			vec3d_plus(tmp, info->cam->dir), 0);
	free(tmp);
	free(up);
	free(right);
	return (ray);
}

void	convert_pixels(int x_pxl, int y_pxl, t_data *info, double scrn_xy[2])
{
	scrn_xy[0] = ((2 * (double)x_pxl + 0.5)
			/ (double)SCREEN_WIDTH - 1) * tan((info->cam->FOV * M_PI / 180) / 2)
		* ASPECT_RATIO;
	scrn_xy[1] = (1 - 2 * ((double)y_pxl + 0.5)
			/ (double)SCREEN_HIGHT) * tan((info->cam->FOV * M_PI / 180) / 2);
}

void	projection(t_data *info)
{
	int			pxl_xy[2];
	double		scrn_xy[2];
	t_ray		*ray;

	pxl_xy[0] = 0;
	while (pxl_xy[0] <= SCREEN_WIDTH)
	{
		pxl_xy[1] = 0;
		while (pxl_xy[1] <= SCREEN_HIGHT)
		{
			convert_pixels(pxl_xy[0], pxl_xy[1], info, scrn_xy);
			ray = make_ray(info, scrn_xy[0], scrn_xy[1]);
			intersect2(info, pxl_xy, ray);
			destroy_ray(ray);
			pxl_xy[1]++;
		}
		pxl_xy[0]++;
	}
}
