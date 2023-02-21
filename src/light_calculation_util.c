#include "../miniRT.h"

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

/**
 * @brief finds the normal of the given object
 * at the intersection point
 * 
 * @param obj  the specific object
 * @param inter intersection point
 * @param ray 
 * @return t_vec3d* normal vector
 */
t_vec3d	*find_obj_normal(t_objects *obj, t_vec3d *inter, t_ray *ray)
{
	t_vec3d	*normal;

	if (obj->id == 0)
		normal = vec3d_cpy(obj->plane->norm);
	if (obj->id == 1)
		normal = vec3d_minus(inter, obj->sphere->origin);
	if (obj->id == 2)
		normal = cyl_norm(obj->cylinder, ray, inter);
	vec3d_norm(normal);
	return (normal);
}

/**
 * @brief gives the colors (r,g,b)
 * of the given object node. 
 * 
 * @param obj object
 * @param color colors
 */
void	each_obj_color(t_objects *obj, int color[3])
{
	if (obj->id == 0)
	{
		color[0] = obj->plane->r;
		color[1] = obj->plane->g;
		color[2] = obj->plane->b;
	}
	if (obj->id == 1)
	{
		color[0] = obj->sphere->r;
		color[1] = obj->sphere->g;
		color[2] = obj->sphere->b;
	}
	if (obj->id == 2)
	{
		color[0] = obj->cylinder->r;
		color[1] = obj->cylinder->g;
		color[2] = obj->cylinder->b;
	}
}
