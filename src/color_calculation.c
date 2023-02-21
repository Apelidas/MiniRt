#include"../miniRT.h"

int	ray_hits_light(t_data *info, t_ray *light_ray, t_objects *obj)
{
	t_objects	*tmp;

	tmp = info->obj;
	while (tmp)
	{
		if (tmp && tmp == obj)
			tmp = tmp->next;
		if (tmp && tmp->id == 1 && \
			sphere_intersection(light_ray, tmp->sphere) > 1e-4)
			return (0);
		if (tmp && tmp->id == 0 && \
			plane_intersection(light_ray, tmp->plane) > 1e-4)
			return (0);
		if (tmp && tmp->id == 2 \
			&& hit_cylinder2(light_ray, tmp->cylinder) > 1e-4)
			return (0);
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

int	amb_light_effect(t_data	*info, t_objects *obj)
{
	double	ambb[3];
	int		obj_color[3];

	each_obj_color(obj, obj_color);
	ambb[0] = obj_color[0] * info->amb->r * info->amb->ratio / 255;
	ambb[1] = obj_color[1] * info->amb->g * info->amb->ratio / 255;
	ambb[2] = obj_color[2] * info->amb->b * info->amb->ratio / 255;
	return ((int)ambb[0] << 16 | ((int)ambb[1] << 8) | ((int)ambb[2]));
}

int	add_light_util(t_data *info, double coef, t_objects *obj)
{
	double	ambb[3];
	double	tmp[3];
	int		color[3];

	ambb[0] = info->amb->r * info->amb->ratio / 255;
	ambb[1] = info->amb->g * info->amb->ratio / 255;
	ambb[2] = info->amb->b * info->amb->ratio / 255;
	tmp[0] = ambb[0] + info->light->r * coef / 255;
	tmp[1] = ambb[1] + info->light->g * coef / 255;
	tmp[2] = ambb[2] + info->light->b * coef / 255;
	each_obj_color(obj, color);
	tmp[0] = color[0] * tmp[0];
	tmp[1] = color[1] * tmp[1];
	tmp[2] = color[2] * tmp[2];
	if (tmp[0] > 255)
		tmp[0] = 255;
	if (tmp[1] > 255)
		tmp[1] = 255;
	if (tmp[2] > 255)
		tmp[2] = 255;
	return (((int)tmp[0] << 16) | ((int)tmp[1] << 8) | ((int)tmp[2]));
}

int	color_cal_util(t_data *info, t_objects *obj, t_ray	*ray, t_vec3d *inter)
{
	t_vec3d	*normal;
	t_vec3d	*tmp;
	t_ray	light_ray;
	double	coef_light;

	normal = find_obj_normal(obj, inter, ray);
	tmp = vec3d_minus(info->light->pos, inter);
	light_ray.dir = tmp;
	light_ray.origin = inter;
	if (!ray_hits_light(info, &light_ray, obj))
	{
		free(normal);
		free(tmp);
		return (amb_light_effect(info, obj));
	}
	vec3d_norm(tmp);
	if (obj->id == 1)
		coef_light = info->light->bright * \
			maxx(vec3d_dot(light_ray.dir, normal));
	else
		coef_light = info->light->bright * \
			maxx2(vec3d_dot(light_ray.dir, normal));
	free(normal);
	free(tmp);
	return (add_light_util(info, coef_light, obj));
}

int	color_calculation(t_data *info, t_objects *obj, t_ray *ray, double t)
{
	int		color;
	t_vec3d	*inter_point;

	inter_point = create_vec3d(ray->origin->x + ray->dir->x * t, \
		ray->origin->y + ray->dir->y * t, ray->origin->z + ray->dir->z * t);
	color = color_cal_util(info, obj, ray, inter_point);
	free(inter_point);
	return (color);
}
