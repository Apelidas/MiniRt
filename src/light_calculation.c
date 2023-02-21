
#include"../miniRT.h"

/**
 * @brief goes through all the objects available in the scene, to see
 * if the ray hits then or not.
 * 
 * @param info 
 * @param light_ray 
 * @param obj 
 * @return int 1 if ray doesnt hit any object. 0 : if the ray is blocked 
 * by an object.
 */
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
/**
 * @brief ambient light effect is calculated via formulas.
 * 
 * @param info 
 * @param obj 
 * @return int 
 */

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
/**
 * @brief here, we calculte the affect of light source.
 * the formula says that, light source coef X light_color / 255 
 * and added to ambient light, is the coef of r, g & b colors 
 * of pixel, respectively.
 * 
 * @param info 
 * @param coef calculated from lambertian law, in the other function.
 * @param obj 
 * @return int color 
 */
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

/**
 * @brief in this function, we make a ray from intersection point, 
 * to the light source, and then we check if the ray reachs the 
 * light, or it is blocked by other objects in the scence. 
 * if it is blocked, it means the color of that point is only
 * affected by ambient light and the object itself. if not blocked, it is
 * affected by the light_source too. this is the lambert law,
 * that the light_ray's and intersection point (on the surface)'s 
 * normal angle is important in the light calculation.
 * 
 * @param info all the data of the scences and ...
 * @param obj all of objects in the scene.
 * @param ray the ray that hit the intersecrion point. 
 * actually this is not really usefull, if the functions
 * were written in a way that cyl didnt need a ray, it was
 * totally ommitable. 
 * @param inter intersection point. 
 * @return int color
 */
int	light_cal_util(t_data *info, t_objects *obj, t_ray	*ray, t_vec3d *inter)
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
/**
 * @brief in this function, we turn the t of the closest inter
 * section point to the intersection point itself. 
 * 
 * @param info 
 * @param obj the whole objects of the scene
 * @param ray ray!
 * @param t t of the closest intersection
 * @return int color of the respective pixel is returned. 
 */

int	light_calculation(t_data *info, t_objects *obj, t_ray *ray, double t)
{
	int		color;
	t_vec3d	*inter_point;

	inter_point = create_vec3d(ray->origin->x + ray->dir->x * t, \
		ray->origin->y + ray->dir->y * t, ray->origin->z + ray->dir->z * t);
	color = light_cal_util(info, obj, ray, inter_point);
	free(inter_point);
	return (color);
}
