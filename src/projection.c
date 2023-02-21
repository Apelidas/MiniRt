#include "../miniRT.h"

/**
 * @brief since MLX is stupid, we write this function to put pixels
 * on screen much faster than mlx_pixel_put//
 * 
 * @param data 
 * @param x 
 * @param y 
 * @param color 
 */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < SCREEN_WIDTH && y < SCREEN_HIGHT && x > 0 && y > 0)
	{
		dst = data->mlx->addr + (y * data->mlx->l_length
				+ x * (data->mlx->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

/**
 * @brief with the help of right and up vector, this function makes rays 
 * from cam point to the x and y on the imaginary screen. up_guide is a 
 * guide for (0, 1, 0) direction, right is the cross product of camera 
 * direction and up_guide, the cross product of cam_dir and up_guide 
 * is perpendecular to them and is the right direction vector. 
 * we are setting our camera with certain direction 
 * (pre defined) in a way that it is perpendecular to our imaginary 
 * screen and its direction is perpendecular to our screen's up and right 
 * coordinates. in fact, these calculations are setting 
 * up the screen.
 * 
 * @param info all the data of scences and objects
 * @param x imaginary screen's x
 * @param y imaginary screen's y
 * @return t_ray* returns the ray from camera to the (x, y)
 */

t_ray	*make_ray(t_data *info, double x, double y)
{
	t_vec3d	*tmp;
	t_vec3d	*right;
	t_vec3d	*up;
	t_vec3d	*up_guide;
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	up_guide = create_vec3d(0, 1, 0);
	vec3d_norm(info->cam->dir);
	right = vec3d_cross(info->cam->dir, up_guide);
	vec3d_norm(right);
	up = vec3d_cross(right, info->cam->dir);
	vec3d_norm(up);
	vec3d_mult(right, x);
	vec3d_mult(up, y);
	tmp = vec3d_plus(right, up);
	ray = create_vray(vec3d_cpy(info->cam->pos),
			vec3d_plus(tmp, info->cam->dir), 0);
	free(tmp);
	free(up);
	free(right);
	free(up_guide);
	return (ray);
}
/**
 * @brief converts each pixel of the screen, to the x and y of 
 * the imaginary screen coordinates. we know that the pixels are different 
 * than image screen and there is a formula converting the pixels to the
 * screen x and y.
 * 
 * @param x_pxl pixel x
 * @param y_pxl pixel y
 * @param info  information of the whole scene
 * @param scrn_xy screen x and screen y that we want to calculate.
 */
void	convert_pixels(int x_pxl, int y_pxl, t_data *info, double scrn_xy[2])
{
	scrn_xy[0] = ((2 * (double)x_pxl + 0.5) \
		/ (double)SCREEN_WIDTH - 1) * tan((info->cam->FOV * M_PI / 180) / 2) \
			* ASPECT_RATIO;
	scrn_xy[1] = (1 - 2 * ((double)y_pxl + 0.5) \
		/ (double)SCREEN_HIGHT) * tan((info->cam->FOV * M_PI / 180) / 2);
}
/**
 * @brief this function goes through each pixel, converts them to 
 * imaginary screen's coordinates, casts a ray from camera to that point, 
 * and checks for intersection between any object and the ray. then it 
 * destroys the ray and goes through another pixel and another ray.
 * 
 * @param info holds all the information of objects and lights and camera.
 */

void	projection(t_data *info)
{
	int			pxl_xy[2];
	double		scrn_xy[2];
	t_ray		*ray;

	pxl_xy[0] = 0;
	while (pxl_xy[0] <= SCREEN_WIDTH)
	{
		pxl_xy[1] = 0;
		while (pxl_xy[1] <= SCREEN_HIGHT)
		{
			convert_pixels(pxl_xy[0], pxl_xy[1], info, scrn_xy);
			ray = make_ray(info, scrn_xy[0], scrn_xy[1]);
			intersect2(info, pxl_xy, ray);
			destroy_ray(ray);
			pxl_xy[1]++;
		}
		pxl_xy[0]++;
	}
}
