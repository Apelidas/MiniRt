# include "../miniRT.h"

t_vec3d	*vec3d_plus(t_vec3d	*a, t_vec3d	*b)
{
	t_vec3d	*res;

	res = malloc (sizeof(t_vec3d));
	if (!res)
		return (NULL);
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	return (res);
}
t_vec3d	*vec3d_mult_num(t_vec3d	*a, double b)
{
	t_vec3d	*res;

	res = malloc(sizeof(t_vec3d));
	if (!res)
		return (NULL);
	res->x = a->x * b;
	res->y = a->y * b;
	res->z = a->z * b;
	return (res);
}
t_vec3d	*make_ray(t_vec3d	*screen_point, t_vec3d	*camera_normal)
{
	t_vec3d	*up_guide;
	t_vec3d	*x_axis;
	t_vec3d	*y_axis;
	t_vec3d	*rotated;

	up_guide = create_vec3d(0, 1, 0);
	vec3d_norm(camera_normal);
	x_axis = vec3d_cross(up_guide, camera_normal);
	y_axis = vec3d_cross(camera_normal, x_axis);
	rotated = vec3d_plus(vec3d_mult_num(x_axis, screen_point->x), camera_normal);
	rotated = vec3d_plus(vec3d_mult_num(y_axis, screen_point->y), rotated);
	return (rotated);
}

t_vec3d	*convert_to_screen_xy(int pixel_x, int pixel_y, t_data *info)
{
	t_vec3d	*res;

	res = malloc(sizeof(t_vec3d));
	if (!res)
		return (NULL);
	res->x = ((2 * (double)pixel_x + 0.5) / (double)SCREEN_WIDTH - 1) * tan((info->cam->FOV * M_PI / 180) / 2) * ASPECT_RATIO;
	res->y	= (1 - 2 * ((double)pixel_y + 0.5) / (double)SCREEN_HIGHT) * tan((info->cam->FOV * M_PI / 180) / 2);
	res->z = 1;
	res = make_ray(res, info->cam->dir);
	return (res);
}

t_vec3d	*vec3d_minus(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*res;

	res = malloc(sizeof(t_vec3d));
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return (res);
}
double	sphere_intersection(t_ray *ray, t_sphere *sphr)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;

	a = vec3d_dot(ray->dir, ray->dir);
	b = 2 * vec3d_dot(ray->dir, vec3d_minus(ray->origin, sphr->origin));
	c = pow(vec3d_len(ray->origin), 2) - pow(sphr->d / 2, 2);
	delta = pow(b , 2) - 4 * a * c;
	if (delta < 0 )
		return (-1);
	t1 = (-b + sqrt(delta)) / (2 * a);
	t2 = (-b - sqrt(delta)) / (2 * a);
	if (t1 >= 0 && t2 >= 0)
		return ((t1 > t2) ? t2 : t1);
	else if (t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	return (-1);
}

void	projection(t_data	*info)
{
	int		x_pixel;
	int		y_pixel;
	t_vec3d	*screen_coordnt;
	t_ray	*ray;
	t_objects	*tmp;

	x_pixel = 0;
	while (x_pixel < SCREEN_WIDTH)
	{
		y_pixel = 0;
		while (y_pixel < SCREEN_HIGHT)
		{
			screen_coordnt = convert_to_screen_xy(x_pixel, y_pixel, info);
			ray = make_ray_camera(screen_coordnt, info);
			tmp = info->obj;
			printf("-------------------------RAYS-----------------------------\n%f   %f   %f\n", screen_coordnt->x, screen_coordnt->y, screen_coordnt->z);
			// while (tmp)
			// {
			// 	// if (tmp->id == 0)
			// 	// {
			// 	// 	if (plane_ray_touch(ray, tmp->plane))
			// 	// 	{
						// my_mlx_pixel_put(info, 100 + x_pixel, 100 + y_pixel, 255);
			// 	// 		// printf("==================== x  %d and y %d ===================\n", x_pixel, y_pixel);
			// 	// 	}
			// 	// }
				if (tmp->id == 1 && sphere_intersection(ray, tmp->sphere) >= 0)
				{
					// printf(" the intersection function output is %f \n", sphere_intersection(ray, tmp->sphere));
					my_mlx_pixel_put(info, 100 + x_pixel, 100 + y_pixel, get_trgb(0, 250, 0, 0));
				}
			// 	tmp = tmp->next;
			// }
			y_pixel++;
		}
		x_pixel++;
	}
}
