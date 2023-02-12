# include"../miniRT.h"

t_vec3d	*add_to_t(t_ray *ray, t_vec3d *inter, t_vec3d *some_point)
{
	double	t;
	if (!ray || !inter)
		return (0);
	t = (some_point->x - ray->origin->x) / (ray->dir->x);
	t += 0.000001;
	inter->x += inter->x + t * ray->dir->x;
	inter->y += inter->y + t * ray->dir->y;
	inter->z += inter->z + t * ray->dir->z;
	return (inter);
}

double	plane_intersection(t_vec3d *ray_d, t_vec3d *cam_o, t_vec3d *pl_n, t_vec3d *pl_o)
{
	double	inter_proj;//projection of intersecting normal and direction of camera
	double	inter;

	inter_proj = vec3d_dot(ray_d, pl_n);
	if(inter_proj == 0)//this means that plane doesnt intersect with the ray
		return (INFINITY);
	inter = vec3d_dot(vec3d_minus(pl_o, cam_o), pl_n) / inter_proj;
	//if inter == 0 vector is || to plane
	//if < 0 its on the oposite side of the cam
	//if > 0 it intersects
	if (inter <= 0)
		return (INFINITY);
	else
		return (inter);
}

int	ray_hits_light(t_data *info, t_ray *light_ray, t_vec3d *inter)
{
	t_objects	*tmp;

	tmp = info->obj;
	light_ray->origin = add_to_t(light_ray, inter, info->light->pos);
	while (tmp)
	{
		if (tmp->id == 1 && sphere_intersection(light_ray, tmp->sphere)> 1e-3)
			return (0);
		if (tmp->id == 0 && !plane_intersection(light_ray->dir,info->cam->pos, tmp->plane->norm, tmp->plane->origin))
			return (0);
		if (tmp->id == 2 && cyl_ray_inter(tmp->cylinder, light_ray))
			return (0);
			//other objs to be added
		tmp = tmp->next;
	}
	(void)inter;
	return (1);
}

double	maxx(double a)
{
	if (a >= 0)
		return (a);
	return (0);
}

double	maxx2(double a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

int add_co_sph(t_light *light, double coef, t_amb *amb, t_sphere *sp)
{
	double	ambb[3];
	double	tmp[3];

	ambb[0] = amb->r * amb->ratio / 255;
	ambb[1] = amb->g * amb->ratio / 255;
	ambb[2] = amb->b * amb->ratio / 255;
	tmp[0] = ambb[0] + light->r * coef / 255;
	tmp[1] = ambb[1] + light->g * coef / 255;
	tmp[2] = ambb[2] + light->b * coef / 255;
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

int add_co_plane(t_data *info, double coef, t_plane *pl)
{
	double	ambb[3];
	double	tmp[3];

	ambb[0] = info->amb->r * info->amb->ratio / 255;
	ambb[1] = info->amb->g * info->amb->ratio / 255;
	ambb[2] = info->amb->b * info->amb->ratio / 255;
	tmp[0] = ambb[0] + info->light->r * coef / 255;
	tmp[1] = ambb[1] + info->light->g * coef / 255;
	tmp[2] = ambb[2] + info->light->b * coef / 255;
	tmp[0] = pl->r * tmp[0];
	tmp[1] = pl->g * tmp[1];
	tmp[2] = pl->b * tmp[2];
	if (tmp[0] > 255)
		tmp[0] = 255;
	if (tmp[1] > 255)
		tmp[1] = 255;
	if (tmp[2] > 255)
		tmp[2] = 255;
	return (((int)tmp[0] << 16) | ((int)tmp[1] << 8) | ((int)tmp[2]));
	// return(get_trgb(0, tmp[0], tmp[1], tmp[1])); //something is wrong with this function
}

int	amb_light_cal(t_amb *amb, t_sphere *sph)
{
	double	ambb[3];

	ambb[0] = sph->r * amb->r * amb->ratio / 255;
	ambb[1] = sph->g * amb->g * amb->ratio / 255;
	ambb[2] = sph->b * amb->b * amb->ratio / 255;
	return ((int)ambb[0] << 16 | ((int)ambb[1] << 8) | ((int)ambb[2]));
}

int	amb_light_cal_p(t_amb *amb, t_plane *pl)
{
	double	ambb[3];

	ambb[0] = pl->r * amb->r * amb->ratio / 255;
	ambb[1] = pl->g * amb->g * amb->ratio / 255;
	ambb[2] = pl->b * amb->b * amb->ratio / 255;
	return ((int)ambb[0] << 16 | ((int)ambb[1] << 8) | ((int)ambb[2]));
}

int	color_cal_sphere(t_data *info, t_sphere *sphere, t_vec3d *inter)
{
	t_vec3d	*normal;
	t_ray	light_ray;
	t_vec3d	*tmp;
	double	coef_light;

	normal = vec3d_minus(inter, sphere->origin);
	vec3d_norm(normal);
	tmp = vec3d_minus(info->light->pos, inter);
	vec3d_norm(tmp);
	light_ray.dir = tmp;
	light_ray.origin = inter;
	coef_light = info->light->bright * maxx(vec3d_dot(light_ray.dir, normal));
	// color = add_lighting_effect(coef_light, info, info->obj, 1);
	if (!ray_hits_light(info, &light_ray, inter))
	{
		free(tmp);
		free(normal);	
		return (amb_light_cal(info->amb, sphere));
	}
	free(tmp);
	free(normal);
	return (add_co_sph(info->light, coef_light, info->amb, sphere));
}

int color_cal_plane(t_data *info, t_plane *plane, t_vec3d *inter)
{
	t_vec3d	*tmp;
	t_ray	light_ray;
	int		color;
	double	coef_light;

	vec3d_norm(plane->norm);
	// printf("normal %f %f %f |", plane->norm->x, plane->norm->y, plane->norm->z);
	tmp = vec3d_minus(info->light->pos, inter);
	vec3d_norm(tmp);
	light_ray.dir = tmp;
	light_ray.origin = inter;
	if (!ray_hits_light(info, &light_ray, inter))
		return (amb_light_cal_p(info->amb, plane));
	coef_light = info->light->bright * maxx2(vec3d_dot(light_ray.dir, plane->norm));
	color = add_co_plane(info, coef_light, plane);
	return (color);
}

int	color_calculation(t_data *info, t_objects *obj, t_ray *ray, double t)
{
	int		color;
	t_vec3d	*inter_point;

	inter_point =  create_vec3d(ray->origin->x + ray->dir->x * t, ray->origin->y + ray->dir->y * t, ray->origin->z + ray->dir->z * t);
	color = 0;
	if (obj->id == 0)
		color = color_cal_plane(info, obj->plane, inter_point);
	if (obj->id == 1)
		color = color_cal_sphere(info, obj->sphere, inter_point);
	free(inter_point);
	return (color);
}