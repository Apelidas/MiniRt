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
	info->light = malloc (sizeof(t_light));
	if (!info->light)
		return ;
	info->light->pos = malloc(sizeof(t_vec3d));
	if (!info->light->pos)
		return ;
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
	projection(info);
	// t_objects *head; 
	// printf("amb test1:|%f|\n", info->amb->r);
	// printf("amb test2:|%f|\n", info->amb->g);
	// printf("amb test3:|%f|\n", info->amb->b);
	// printf("light light pos %f\n", info->light->pos->y);
	// printf("light brightness %f\n", info->light->bright);
	// head = info->obj;
	// while (head)
	// {
	// 	printf("id %d\n", head->id);
	// 	if (head->id == 0)
	// 		printf("Z of origin for plane:%f", head->plane->origin->z);
	// 	if (head->id == 1)
	// 		printf("sphere o: %f %f %f d: %f rgb %d\n", head->sphere->origin->x\
	// 	, head->sphere->origin->y, head->sphere->origin->z, head->sphere->d, head->sphere->trgb);
	// 	if (head->id == 2)
	// 	printf("stuff for the cylinder %f\n", head->cylinder->origin->z);
	// 	head = head->next;
	// }
	mlx_put_image_to_window(info->mlx->mlx, info->mlx->win, info->mlx->img, 0, 0);
	mlx_hook(info->mlx->win, 2, 0, &key_hook, &info->mlx);
	mlx_hook(info->mlx->win, 17, 0, &close_x, &info->mlx);
	mlx_loop(info->mlx->mlx);
}
