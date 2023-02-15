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



int	main(int argc, char **argv)
{
	t_data	*info;

	if (argc != 2)
		error("number of arguments out of range.");
	info = malloc(sizeof(t_data));
	if (!info)
		return (0);
	data_init(info);
	if (!parser(argv, info))
	{
		destroy_data(info);
		return (0);
	}
	projection(info);
	// t_vec3d *tmp = create_vec3d(1, -0.5, 1);
	// vec3d_norm(tmp);
	// printf("tmp: %f %f %f\n", tmp->x, tmp->y, tmp->z);
	// t_light *head_light;
	// head_light = info->light;
	// while(head_light)
	// {
	// 	printf("Multi lights o:%f %f %f\n", head_light->pos->x, head_light->pos->y, head_light->pos->z);
	// 	head_light = head_light->next;
	// }
	// t_objects *head;
	// // printf("light light pos %f\n", info->light->pos->y);
	// // printf("light brightness %f\n", info->light->bright);
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
