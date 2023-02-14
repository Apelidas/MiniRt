#include "test.h"

void	print_objs(t_data *info)
{
	t_objects	*tmp;

	tmp = info->obj;
	while (tmp)
	{
		if (tmp->id == 0)
			print_plane(tmp->plane);
		if (tmp->id == 1)
			print_sphere(tmp->sphere);
		if (tmp->id == 2)
			print_cyl(tmp->cylinder);
		printf("\n");
		tmp = tmp->next;
	}
}

void	print_lights(t_data *info)
{
	t_light	*tmp;

	tmp = info->light;
	while (tmp)
	{
		printf("pos:\n");
		print_vec3d(tmp->pos);
		printf("bright:\n%f\ncolor:\n%d\n", tmp->bright, tmp->trgb);
		printf("\n");
		tmp = tmp->next;
	}
}

void	print_camera(t_data *info)
{
	if (!info->cam)
		return ;
	printf("pos:\n");
	print_vec3d(info->cam->pos);
	printf("dir:\n");
	print_vec3d(info->cam->dir);
	printf("FOV:\n%d\n", info->cam->FOV);
}

void	print_amb(t_data *info)
{
	if (!info->amb)
		return ;
	printf("trgb:\n%d\nratio:\n%f\n", info->amb->trgb, info->amb->ratio);
}

int	main(int argc, char **argv)
{
	t_data	*info;

	if (argc != 2)
		return (1);
	info = malloc(sizeof(t_data));
	data_init(info);
	if (!info)
		return (0);
	parser(argv, info);
	printf("CAMERA:\n");
	print_camera(info);
	printf("\nLIGHTS:\n");
	print_lights(info);
	printf("\nAMB:\n");
	print_amb(info);
	printf("\nOBJECTS:\n");
	print_objs(info);
	
}