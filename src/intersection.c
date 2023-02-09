#include "../miniRT.h"

t_vec3d	*hit_sphere(int pxl[2], t_ray *ray, t_sphere *sphere, t_vec3d *closest, t_data *info, int reflec)
{
	t_vec3d	*inter;
	int		color;

	inter = sphere_ray_inter(ray, sphere);
	if (reflec > 0)
	{
		printf("closest:\n");
		print_vec3d(closest);
		printf("inter:\n");
		print_vec3d(inter);
	}
	if (!inter)
		return (closest);
	if (!closest)
	{
		reflec = 0;
		//color = color_calculation(info, (void *)sphere, ray, 1, inter);
		color = sphere->trgb; //placeholder color calculation
		printf("a\n");
		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
		return (inter);
	}
	if (vec3d_dist(ray->origin, inter) < vec3d_dist(ray->origin, closest))
	{
		
		color = sphere->trgb; //placeholder color calculation
		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
		free(closest);
		return (inter);
	}
	free(inter);
	return (closest);
}

t_vec3d	*hit_plane(int pxl[2], t_ray *ray, t_plane *plane, t_vec3d *closest, t_data *info, int reflec)
{
	t_vec3d	*inter;
	int		color;

	inter = plane_ray_inter(ray, plane);
	if (!inter)
		return (closest);
	if (!closest)
	{
		if (plane->surface_type == 1)
		{
			intersect_reflection(info, pxl, plane_reflect(ray, plane, inter), reflec + 1);
		}
		else
		{
			color = plane->trgb; //placeholder color calculation
			my_mlx_pixel_put (info, pxl[0], pxl[1], color);
		}
		return (inter);
	}
	if (vec3d_dist(ray->origin, inter) < vec3d_dist(ray->origin, closest))
	{
		if (plane->surface_type == 1)
		{
			intersect_reflection(info, pxl, plane_reflect(ray, plane, inter), reflec + 1);
		}
		else
		{
			color = plane->trgb; //placeholder color calculation
			my_mlx_pixel_put (info, pxl[0], pxl[1], color);
		}
		free(closest);
		return (inter);
	}
	free(inter);
	return (closest);
}

t_vec3d	*hit_cylinder(int pxl[2], t_ray *ray, t_cylinder *cyl, t_vec3d *closest, t_data *info, int reflec)
{
	t_vec3d	*inter;
	int		color;

	inter = cyl_ray_inter(cyl, ray);
	if (!inter)
		return (closest);
	if (!closest)
	{
		color = cyl->trgb; //placeholder color calculation
		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
		return (inter);
	}
	if (vec3d_dist(ray->origin, inter) < vec3d_dist(ray->origin, closest))
	{
		if (cyl->surface_type == 2)
		{
			intersect_reflection(info, pxl, cyl_ray_reflec(cyl, ray, inter), reflec + 1);
		}
		else
		{
			color = cyl->trgb; //placeholder color calculation
			my_mlx_pixel_put (info, pxl[0], pxl[1], color);
		}
		free(closest);
		return (inter);
	}
	free(inter);
	return (closest);
}

/**
 * @brief intersection function that limits reflection to prevent loop
 * 
 * @param info 
 * @param pxl 
 * @param ray 
 * @param reflec 
 */
void	intersect_reflection(t_data *info, int	pxl[2], t_ray *ray, int reflec)
{
	t_objects	*tmp;
	t_vec3d		*closest;

	if (reflec == MAX_REFLEC)
		return ;
	closest = NULL;
	tmp = info->obj;
	while (tmp)
	{
		if (tmp->id == 0)
			closest = hit_plane(pxl, ray, tmp->plane, closest, info, reflec);
		if (tmp->id == 1)
			closest = hit_sphere(pxl, ray, tmp->sphere, closest, info, reflec);
		else if (tmp->id == 2)
			closest = hit_cylinder(pxl, ray, tmp->cylinder, closest, info, reflec);
		// printf("closest:\n");
		// print_vec3d(closest);
		// printf("\n");
		tmp = tmp->next;
	}
	if (closest)
	{
		// printf("closest:\n");
		// print_vec3d(closest);
		free(closest);
	}
	destroy_ray(ray);
}

/**
 * @brief calculates the color of all pixels by calculating the point of intersection for each ray
 * 
 * @param info 
 * @param pxl 
 * @param ray 
 */
void	intersect(t_data *info, int	pxl[2], t_ray *ray)
{
	t_objects	*tmp;
	t_vec3d		*closest;

	closest = NULL;
	tmp = info->obj;
	while (tmp)
	{
		if (tmp->id == 0)
			closest = hit_plane(pxl, ray, tmp->plane, closest, info, 0);
		if (tmp->id == 1)
			closest = hit_sphere(pxl, ray, tmp->sphere, closest, info, 0);
		else if (tmp->id == 2)
			closest = hit_cylinder(pxl, ray, tmp->cylinder, closest, info, 0);
		tmp = tmp->next;
	}
	if (closest)
		free(closest);
	destroy_ray(ray);
}
