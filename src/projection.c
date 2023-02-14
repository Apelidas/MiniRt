# include "../miniRT.h"

double	sphere_intersection(t_ray *ray, t_sphere *sphr) //tmporary here. 
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;

	a = vec3d_dot(ray->dir, ray->dir);
	b = 2 * vec3d_dot(ray->dir, vec3d_minus(ray->origin, sphr->origin));
	c = vec3d_dot(vec3d_minus(ray->origin, sphr->origin), \
		vec3d_minus(ray->origin, sphr->origin)) - pow(sphr->d / 2, 2);
	delta = pow(b , 2) - 4 * a * c;
	if (delta < 0)
		return (-1);
    t1 = (-b + sqrt(delta)) / (2 * a);
    t2 = (-b - sqrt(delta)) / (2 * a);
	if (t1 >= 0 && t2 >= 0)
		return ((t1 > t2) ? t2 : t1);
	else if (t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	return (-1); //to be checked again.
}

t_ray	*make_ray(t_data *info, double x, double y)
{
	t_vec3d	*forward;
	t_vec3d	*right;
	t_vec3d	*up;
	t_vec3d	up_guide;
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	up_guide.x = 0;
	up_guide.y = 1;
	up_guide.z = 0;
	forward = info->cam->dir;
	vec3d_norm(forward);
	right = vec3d_cross(forward, &up_guide);
	vec3d_norm(right);
	up = vec3d_cross(right, forward);
	ray->origin = info->cam->pos;
	ray->dir = vec3d_plus(vec3d_mult_num(right, x), vec3d_mult_num(up, y));	//leaks
	ray->dir = vec3d_plus(ray->dir, forward); //leaks
	return (ray);
}

void	convert_pixels(int x_pxl, int y_pxl, t_data *info, double scrn_xy[2])
{
	scrn_xy[0] = ((2 * (double)x_pxl + 0.5) \
		/ (double)SCREEN_WIDTH - 1) * tan((info->cam->FOV * M_PI / 180) / 2) \
			* ASPECT_RATIO;
	scrn_xy[1] = (1 - 2 * ((double)y_pxl + 0.5) \
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
			// print_vec3d(ray->origin);
			intersect(info, pxl_xy, ray);
			pxl_xy[1]++;
		}
		pxl_xy[0]++;
	}
}

// void	projection2(t_data *info)
// {

// }
