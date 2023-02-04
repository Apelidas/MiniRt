# include"../miniRT.h"



int	ray_hits_light(t_data *info, t_ray *light_ray)
{
	t_objects	*tmp;

	tmp = info->obj;
	while (tmp)
	{
		if (tmp->id == 1 && sphere_ray_inter(light_ray, tmp->sphere))
			return (0);
			//other objs to be added
		tmp = tmp->next;
	}
	return (1);
}
double maxx(double a)
{
	if (a >= 0)
		return (a);
	return (0);
}
int		color_x_light(int color, double light)
{
	int mask = 255;
	int r;
	int	g;
	int	b;

	r = light * ((color & (mask << 16)) >> 16);
	g = light * ((color & (mask << 8)) >> 8);
	b = light * (color & mask);

/*	r = pow(r, 1/2.2) * 10;
	g = pow(g, 1/2.2) * 10;
	b = pow(b, 1/2.2) * 10;
*/
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;

	return ((r << 16) | (g << 8) | b);
}
t_vec3d *add_to_t(t_ray *ray, t_vec3d *inter)
{
	double t = (inter->x - ray->origin->x)/ray->dir->x;
	t += 0.0000001;
	inter->x += inter->x + t * ray->dir->x;
	inter->y += inter->y + t * ray->dir->y;
	inter->z += inter->z + t * ray->dir->z;
	return(inter);
}
int	color_cal_sphere(t_data *info, t_sphere *sphere, t_ray *ray, t_vec3d *inter)
{
	t_vec3d	*normal;
	t_ray light_ray;
	// double	alpbedo = 0.18;
	int color;

	// inter = add_to_t(ray, inter);
	normal = vec3d_minus(inter, sphere->origin);
	vec3d_norm(normal);
	t_vec3d *tmp =vec3d_minus(inter, info->light->pos);
	vec3d_norm(tmp);
	light_ray.dir = tmp;
	light_ray.origin = inter;
	if (!ray_hits_light(info, &light_ray))
		return (0);
	light_ray.origin = info->light->pos;
	// int light = (info->light->bright * maxx(vec3d_dot(normal, light_ray.dir)) + get_trgb(0, info->amb->r, info->amb->g, info->amb->b) * info->amb->ratio);
	color =sphere->trgb * (info->light->bright * maxx(vec3d_dot(normal, light_ray.dir)));
	(void)ray;
	// return(color_x_light(sphere->trgb, light));
	return(color);
}
int	color_calculation(t_data *info, void *obj, t_ray *ray, int id, t_vec3d *inter)
{
	int color;

	color = 100;
	if (id == 1)
		color = color_cal_sphere(info, (t_sphere *)obj, ray, inter);
	(void)info;
	(void)ray;
	(void)obj;
	(void)id;
	return(color);
}