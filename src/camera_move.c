#include "../miniRT.h"

/**
 * @brief moves the camera for debugging purposes
 * 
 * @param info 
 * @param x 
 * @param y 
 */
void	camera_move(t_data *info, int x, int y)
{
	t_ray	*help;
	t_plane	*plane;
	t_vec3d	*tmp;

	plane = create_plane(info->cam->pos, info->cam->dir, 0);
	tmp = vec3d_cpy(info->cam->pos);
	tmp->x += x * CAMERA_MOVE;
	tmp->y += y * CAMERA_MOVE;
	help = create_vray(tmp, vec3d_cpy(info->cam->dir), 0);
	tmp = plane_ray_inter(help, plane);
	free(info->cam->pos);
	if (!tmp)
	{
		vec3d_mult(help->dir, -1);
		tmp = plane_ray_inter(help, plane);
	}
	destroy_ray(help);
	if (!tmp)
	{
		info->cam->pos = help->origin;
		free(plane->norm);
		free(plane);
		return ;
	}
	// destroy_plane(plane);
	info->cam->pos = tmp;
}

/**
 * @brief changes the angle in which the camera looks at the scene
 * 
 * @param info 
 * @param x 
 * @param y 
 */
void	camera_dir_move(t_data *info, int x, int y)
{
	double	rotate[9];
	double	rad;
	t_vec3d	*help;

	rad = (CAMERA_ANGLE * M_PI) / 180;
	rotate[1] = 0;
	rotate[3] = 0;
	if (x != 0)
	{
		rotate[0] = 1 * x;
		rotate[2] = 0;
		rotate[6] = 0;
		rotate[4] = cos(rad) * x;
		rotate[5] = -1 * sin(rad) * x;
		rotate[7] = sin(rad) * x;
		rotate[8] = cos(rad) * x;
	}
	else if (y != 0)
	{
		rotate[0] = cos(rad) * y;
		rotate[2] = sin(rad) * y;
		rotate[6] = -1 * sin(rad) * y;
		rotate[4] = 1 * y;
		rotate[5] = 0;
		rotate[7] = 0;
		rotate[8] = cos(rad) * y;
	}
	help = info->cam->dir;
	vec3d_norm(help);
	help->x = rotate[0] * help->x + rotate[1] * help->y + rotate[2] * help->z;
	help->y = rotate[3] * help->x + rotate[4] * help->y + rotate[5] * help->z;
	help->z = rotate[6] * help->x + rotate[7] * help->y + rotate[8] * help->z;
	vec3d_norm(help);
}