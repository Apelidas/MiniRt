// #include "../miniRT.h"

// t_vec3d	*hit_sphere(int pxl[2], t_ray *ray, 
// t_sphere *sphere, t_vec3d *closest, t_data *info)
// {
// 	t_vec3d	*inter;
// 	int		color;

// 	inter = sphere_ray_inter(ray, sphere);
// 	if (!inter)
// 		return (closest);
// 	if (!closest)
// 	{
// 		// color = color_calculation(info, (void *)sphere, ray, 1, closest);
// 		color = sphere->trgb; //placeholder color calculation
// 		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
// 		return (inter);
// 	}
// 	if (vec3d_dist(ray->origin, inter) < vec3d_dist(ray->origin, closest))
// 	{
// 		color = sphere->trgb; //placeholder color calculation
// 		// color = color_calculation(info, (void *)sphere, ray, 1, inter);
// 		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
// 		free(closest);
// 		return (inter);
// 	}
// 	free(inter);
// 	return (closest);
// }

// t_vec3d	*hit_plane(int pxl[2], t_ray *ray,
// t_plane *plane, t_vec3d *closest, t_data *info)
// {
// 	t_vec3d	*inter;
// 	int		color;

// 	inter = plane_ray_inter(ray, plane);
// 	if (!inter)
// 		return (closest);
// 	if (!closest)
// 	{
// 		color = plane->trgb; //placeholder color calculation
// 		// color = color_calculation(info, (void *)plane, ray, 0, inter);
// 		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
// 		return (inter);
// 	}
// 	if (vec3d_dist(ray->origin, inter) < vec3d_dist(ray->origin, closest))
// 	{
// 		color = plane->trgb; //placeholder color calculation
// 		// color = color_calculation(info, (void *)plane, ray, 0, inter);
// 		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
// 		free(closest);
// 		return (inter);
// 	}
// 	free(inter);
// 	return (closest);
// }

// t_vec3d	*hit_cylinder(int pxl[2], t_ray *ray, 
//	t_cylinder *cyl, t_vec3d *closest, t_data *info)
// {
// 	t_vec3d	*inter;
// 	int		color;

// 	inter = cyl_ray_inter(cyl, ray);
// 	if (!inter)
// 		return (closest);
// 	if (!closest)
// 	{
// 		color = cyl->trgb; //placeholder color calculation
// 		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
// 		return (inter);
// 	}
// 	if (vec3d_dist(ray->origin, inter) < vec3d_dist(ray->origin, closest))
// 	{
// 		color = cyl->trgb; //placeholder color calculation
// 		my_mlx_pixel_put (info, pxl[0], pxl[1], color);
// 		free(closest);
// 		return (inter);
// 	}
// 	free(inter);
// 	return (closest);
// }

// /**
//  * @brief calculates the color of all pixels by calculating
// the point of intersection for each ray
//  * 
//  * @param info 
//  * @param pxl 
//  * @param ray 
//  */
// void	intersect(t_data *info, int	pxl[2], t_ray *ray)
// {
// 	t_objects	*tmp;
// 	t_vec3d		*closest;

// 	closest = NULL;
// 	tmp = info->obj;
// 	while (tmp)
// 	{
// 		if (tmp->id == 0)
// 			closest = hit_plane(pxl, ray, tmp->plane, closest, info);
// 		if (tmp->id == 1)
// 			closest = hit_sphere(pxl, ray, tmp->sphere, closest, info);
// 		else if (tmp->id == 2)
// 			closest = hit_cylinder(pxl, ray, tmp->cylinder, closest, info);
// 		tmp = tmp->next;
// 	}
// 	if (closest)
// 		free(closest);
// }
