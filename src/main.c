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
	mlx_put_image_to_window(info->mlx->mlx, \
		info->mlx->win, info->mlx->img, 0, 0);
	mlx_hook(info->mlx->win, 2, 0, &key_hook, &info->mlx);
	mlx_hook(info->mlx->win, 17, 0, &close_x, &info->mlx);
	mlx_loop(info->mlx->mlx);
}
