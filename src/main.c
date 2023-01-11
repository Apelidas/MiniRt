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
	info->obj = malloc(sizeof(t_objects) * 10); //amend later
}

int	main(int argc, char **argv)
{
	t_data	*info;

	if (argc != 2)
		return (0);
	info = malloc(sizeof(t_data));
	if (!info)
		return (0);
	data_init(info);
	parser(argv, info);
	printf("test1:|%f|\n", info->amb->r);
	printf("test2:|%f|\n", info->amb->g);
	printf("test3:|%f|\n", info->amb->b);
	printf("light pos %f\n", info->light->pos->y);
	printf("light brightness %f\n", info->light->bright);
	printf("plane? origin x %f y %f z %f\n", info[0].obj->plane->origin->x, info[0].obj->plane->origin->y, info[0].obj->plane->origin->z);
}
