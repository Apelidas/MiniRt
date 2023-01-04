#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "error.h"
# include "math/operations.h"
# include <math.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

/*
	A 3D Vector containing a color
*/
	typedef struct s_vec3d
	{
		double	x;
		double	y;
		double	z;
	}				t_vec3d;
/* 
	A ray contain a point of Origin and a direction Vector
	TRGB of the direction Vector is used for the ray
 */
	typedef struct s_ray
	{
		t_vec3d	*origin;
		t_vec3d	*dir;
		int		trgb;
	}				t_ray;

/* 
	An Ambient lighting variable
 */
	typedef struct s_amb
	{
		double	r;
		double	g;
		double	b;
		double	ratio;
	}				t_amb;

/* 
	An Camera Object
	Position: pos
	View Direction: dir
	Field of view: FOV		// how narrow the vision is like clenching your eyelids
 */
	typedef struct s_camera
	{
		t_vec3d	*pos;
		t_vec3d	*dir;
		int		FOV;
	}				t_camera;
/* 
	An Object emitting Light
 */
	typedef struct s_light
	{
		t_vec3d	*pos;
		double	bright;
	}				t_light;

/*
	A struct containing the neccessary MLX information
*/
	typedef struct s_mlx
	{
		char	*addr;
		void	*win;
		void	*img;
		int		bpp;
		int		l_length;
		int		endian;
	}				t_mlx;

/*
	A struct containing all current information of Objects or MLX
*/
	typedef struct s_data
	{
		t_mlx		*mlx;
		t_camera	*cam;
		t_light		*light;
		t_amb		*amb;
		void		*obj;	// array containing all Objects(except light/Camera)
	}				t_data;

	typedef struct s_plain
	{
		t_vec3d	*origin;
		t_vec3d	*dir_a;
		t_vec3d	*dir_b;
		int		trgb;
	}				t_plain;


#endif