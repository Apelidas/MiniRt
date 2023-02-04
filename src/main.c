/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:35:02 by pooneh            #+#    #+#             */                          
/* ************************************************************************** */

#include"../miniRT.h"

void	window_init(t_data	*info)
{
	info->mlx = malloc(sizeof(t_mlx));
	if (!info->mlx)
		return ;
	info->mlx->mlx = mlx_init();
	if (!info->mlx->mlx)
		return ;
	info->mlx->img = mlx_new_image(info->mlx->mlx, SCREEN_WIDTH, SCREEN_HIGHT);
	if (!info->mlx->img)
		return ;
	info->mlx->win = mlx_new_window(info->mlx->mlx, SCREEN_WIDTH, \
		SCREEN_HIGHT, "miniRT");
	if (!info->mlx->win)
		return ;
	info->mlx->addr = mlx_get_data_addr(info->mlx->img, &info->mlx->bpp, \
		&info->mlx->l_length, &info->mlx->endian);
}

void	data_init(t_data *info)
{
	info->amb = malloc(sizeof(t_amb));
	if (!info->amb)
		return ;
	info->cam = malloc(sizeof(t_camera));
	if (!info->cam)
		return ;
	info->cam->pos = malloc(sizeof(t_vec3d));
	if (!info->cam->pos)
		return ;
	info->cam->dir = malloc(sizeof(t_vec3d));
	if (!info->cam->dir)
		return ;
	// info->light = malloc (sizeof(t_light));
	// if (!info->light)
	// 	return ;
	info->light = NULL;
	info->obj = NULL;
	window_init(info);
}

int	main(int argc, char **argv)
{
	t_data	*info;

	if (argc != 2)
		error("number of arguments out of range.");
	info = malloc(sizeof(t_data));
	if (!info)
		return (0);
	data_init(info);
	parser(argv, info);
	// projection(info);
	t_light *head_light;
	head_light = info->light;
	while(head_light)
	{
		printf("Multi lights o:%f %f %f\n", head_light->pos->x, head_light->pos->y, head_light->pos->z);
		head_light = head_light->next;
	}
	// t_objects *head;
	// printf("light light pos %f\n", info->light->pos->y);
	// printf("light brightness %f\n", info->light->bright);
	// head = info->obj;
	// while (head)
	// {
	// 	printf("id %d\n", head->id);
	// 	if (head->id == 0)
	// 		printf("plane: o:%f %f %f   n:%f %f %f rgb:%d surface:%d\n", head->plane->origin->x, head->plane->origin->y, head->plane->origin->z, head->plane->norm->x, head->plane->norm->y, head->plane->norm->z, head->plane->trgb, head->plane->surface_type);
	// 	if (head->id == 1)
	// 		printf("sphere o:%f %f %f d:%f rgb:%d surface:%d\n", head->sphere->origin->x\
	// 	, head->sphere->origin->y, head->sphere->origin->z, head->sphere->d, head->sphere->trgb, head->sphere->surface_type);
	// 	if (head->id == 2)
	// 		printf("cylinder o:%f %f %f  n:%f %f %f   d:%f  h:%f rgb:%d  surface:%d\n", head->cylinder->origin->x, head->cylinder->origin->y, head->cylinder->origin->z, head->cylinder->norm->x, head->cylinder->norm->y, head->cylinder->norm->z, head->cylinder->d, head->cylinder->h, head->cylinder->trgb, head->cylinder->surface_type);
	// 	head = head->next;
	// }
	mlx_put_image_to_window(info->mlx->mlx, info->mlx->win, info->mlx->img, 0, 0);
	mlx_hook(info->mlx->win, 2, 0, &key_hook, &info->mlx);
	mlx_hook(info->mlx->win, 17, 0, &close_x, &info->mlx);
	mlx_loop(info->mlx->mlx);
}
