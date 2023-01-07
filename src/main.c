/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:35:02 by pooneh            #+#    #+#             */
/*   Updated: 2023/01/07 15:19:04 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../miniRT.h"

int main(int argc, char **argv)
{
    t_data *info;
    
    if (argc != 2)
        return(0);
    info = malloc(sizeof(t_data));
    info->amb = malloc(sizeof(t_amb));
    parser(argv, info);
    	printf("test1:|%f|\n", info->amb->r);
	printf("test2:|%f|\n", info->amb->g);
	printf("test3:|%f|\n", info->amb->b);
}