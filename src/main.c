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
	info->obj = NULL;
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
	t_objects *head; 
	// printf("test1:|%f|\n", info->amb->r);
	// printf("test2:|%f|\n", info->amb->g);
	// printf("test3:|%f|\n", info->amb->b);
	// printf("light pos %f\n", info->light->pos->y);
	// printf("light brightness %f\n", info->light->bright);
	head = info->obj;
	while (head)
	{
		printf("to be %d\n", head->id);
		if (head->id == 0)
			printf("LL for plane:%d\n", head->plane->trgb->b);
		if(head->id == 1)
			printf("\n\nsphere o: %f %f %f d: %f rgb %d %d %d\n", head->sphere->origin->x\
		, head->sphere->origin->y, head->sphere->origin->z, head->sphere->d, head->sphere->trgb->r\
		,head->sphere->trgb->g, head->sphere->trgb->b);
		head = head->next;
	}
}
