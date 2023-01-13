# include "../miniRT.h"

double	convert_to_spacial_xy(int pixel_coordinate, int indicator)
{
	double	space_coordinate;

	if (indicator == 1)
		space_coordinate = 2 * (double)pixel_coordinate \
			/ (double)SCREEN_WIDTH - 1;
	else
		space_coordinate = 2 * (double)pixel_coordinate \
			/ (double)SCREEN_HEIGHT - 1;
	return (space_coordinate);
}

void	projection(t_data	*info)
{
	int	x_pixel;
	int	y_pixel;
	double	coordinates[2];

	x_pixel = 0;
	y_pixel = 0;
	while (x_pixel < SCREEN_WIDTH)
	{
		coordinates[0] = convert_to_spacial_xy(x_pixel, 1);
		while (y_pixel < SCREEN_HEIGHT)
		{
			coordinates[1] = convert_to_spacial_xy(y_pixel, 2);
			(void)info;
			y_pixel++;
		}
		printf("==================== x  %f and y %f ===================\n", coordinates[0], coordinates[1]);
		x_pixel++;
	}
}
