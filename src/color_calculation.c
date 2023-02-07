# include"../miniRT.h"

t_vec3d	*add_to_t(t_ray *ray, t_vec3d *inter, t_vec3d *some_point)
{
	double	t;

	t = (some_point->x - ray->origin->x) / (ray->dir->x);
	t += 0.0000001;
	inter->x += inter->x + t * ray->dir->x;
	inter->y += inter->y + t * ray->dir->y;
	inter->z += inter->z + t * ray->dir->z;
	return (inter);
}

int	ray_hits_light(t_data *info, t_ray *light_ray, t_vec3d *inter)
{
	t_objects	*tmp;

	tmp = info->obj;
	light_ray->origin = add_to_t(light_ray, inter, info->light->pos);
	while (tmp)
	{
		if (tmp->id == 1 && sphere_ray_inter(light_ray, tmp->sphere))
			return (0);
			//other objs to be added
		tmp = tmp->next;
	}
	(void)inter;
	return (1);
}

double maxx(double a)
{
	if (a >= 0)
		return (a);
	return (0);
}

void	obj_color(t_objects *obj, int id, int	color[3])
{
	if (id == 1)
	{
		color[0] = obj->sphere->r;
		color[1] = obj->sphere->g;
		color[2] = obj->sphere->b;
	}
}

int	add_lighting_effect(double l_coef, t_data *info, t_objects *obj, int id)
{
	int		color[3];
	double	amb[3];

	obj_color(obj, id, color);
	amb[0] = info->amb->r * info->amb->ratio / 255;
	amb[1] = info->amb->g * info->amb->ratio / 255;
	amb[2] = info->amb->b * info->amb->ratio / 255;
	color[0] = (amb[0] + info->light->r * l_coef / 255) * color[0];
	color[1] = (amb[1] + info->light->g * l_coef / 255) * color[1];
	color[2] = (amb[2] + info->light->b * l_coef / 255) * color[2];
	if (color[0] > 255)
		color[0] = 255;
	if (color[1] > 255)
		color[1] = 255;
	if (color[2] > 255)
		color[2] = 255;
	return (((int)color[0] << 16) | ((int)color[1] << 8) | ((int)color[2]));
}

int add_co(t_light *light, double coef, t_amb *amb, t_sphere *sp)
{
	// double coef_amb;
	double ambb[3];
	ambb[0] = amb->r * amb->ratio /255;
	ambb[1] = amb->g * amb->ratio / 255;
	ambb[2] = amb->b * amb->ratio /255;
	// coef_amb = color_x_light(amb->trgb, amb->ratio);
	// coef += coef_amb;
	(void)amb;
	// return(color_x_light(color, coef));
	double tmp[3];
	tmp[0] = ambb[0] + light->r * coef / 255;
	tmp[1] = ambb[1] + light->g * coef /255;
	tmp[2] = ambb[2] + light->b * coef/255;
	tmp[0] = sp->r * tmp[0];
	tmp[1] = sp->g * tmp[1];
	tmp[2] = sp->b * tmp[2];
	if (tmp[0] > 255)
		tmp[0] = 255;
	if (tmp[1] > 255)
		tmp[1] = 255;
	if (tmp[2] > 255)
		tmp[2] = 255;
	return(((int)tmp[0] << 16) | ((int)tmp[1] << 8) | ((int)tmp[2]));
	// return(get_trgb(0, tmp[0], tmp[1], tmp[1])); //something is wrong with this function
}
int	amb_light_cal(t_amb *amb)
{
	double	ambb[3];

	ambb[0] = amb->r * amb->ratio / 255;
	ambb[1] = amb->g * amb->ratio / 255;
	ambb[2] = amb->b * amb->ratio / 255;
	return ((int)ambb[0] << 16) | ((int)ambb[1] << 8) | ((int)ambb[2]);
}

int	color_cal_sphere(t_data *info, t_sphere *sphere, t_ray *ray, t_vec3d *inter)
{
	t_vec3d	*normal;
	t_ray	light_ray;
	double	coef_light;
	int		color;

	normal = vec3d_minus(inter, sphere->origin);
	vec3d_norm(normal);
	t_vec3d *tmp = vec3d_minus(info->light->pos, inter);
	vec3d_norm(tmp);
	light_ray.dir = tmp;
	light_ray.origin = inter;
	if (!ray_hits_light(info, &light_ray, inter))
		return (amb_light_cal(info->amb));
		// return(0);
	coef_light = info->light->bright * maxx(vec3d_dot(light_ray.dir, normal));
	// color = add_lighting_effect(coef_light, info, info->obj, 1);
	color = add_co(info->light, coef_light, info->amb, sphere);
	(void)ray;
	return (color);
}

int	color_calculation(t_data *info, void *obj, t_ray *ray, int id, t_vec3d *inter)
{
	int color;

	color = 0;
	if (id == 1)
		color = color_cal_sphere(info, (t_sphere *)obj, ray, inter);
	(void)info;
	(void)ray;
	(void)obj;
	(void)id;
	(void)inter;
	return (color);
}