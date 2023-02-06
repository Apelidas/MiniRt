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
# include <fcntl.h>
# include "mlx/mlx.h"
# define SCREEN_WIDTH 1000
# define SCREEN_HIGHT 1000
# define ASPECT_RATIO	1
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

typedef struct s_cylinder t_cyl;

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}			t_color;

/*
	A 3D Vector
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
	int		trgb;
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
	int		trgb;
	struct s_light *next;
}				t_light;

/*
	A struct containing the neccessary MLX information
*/
typedef struct s_mlx
{
	char	*addr;
	void	*win;
	void	*img;
	void	*mlx;
	int		bpp;
	int		l_length;
	int		endian;
}				t_mlx;

/* 
	A plain created by having a point of origin and 2 vectors lying in the plain.
	Important both vectors cannot be the same.
 */
typedef struct s_plain
{
	t_vec3d	*origin;
	t_vec3d	*norm;
	int		trgb;
	int		surface_type;
}				t_plane;

typedef struct s_sphere
{
	t_vec3d	*origin;
	double	d;
	int	trgb;
	int	surface_type;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3d	*origin;
	t_vec3d	*norm;
	double	d;
	double	h;
	int		trgb;
	int		surface_type;
}	t_cylinder;
/*
	containing all of the objects
*/
typedef struct objects
{
	t_plane			*plane;
	t_sphere		*sphere;
	t_cylinder		*cylinder;
	int				id;
	struct objects	*next;
}	t_objects;


/*
	A struct containing all current information of Objects or MLX
*/
typedef struct s_data
{
	t_mlx		*mlx;
	t_camera	*cam;
	t_light		*light;
	t_amb		*amb;
	t_objects	*obj;	// linked list  containing all Objects(except light/Camera)
}				t_data;


/* 
	is equal
	plain_cpy
 */

//		Color Functions
int		get_t(int color);
int		get_r(int color);
int		get_g(int color);
int		get_b(int color);
void	set_t(int *color, int t);
void	set_r(int *color, int r);
void	set_g(int *color, int g);
void	set_b(int *color, int b);
int		get_trgb(unsigned int t, unsigned int r, unsigned int g, unsigned int b);

//		PARSER
void	parser(char **argv, t_data *info);
void	parser_camera(char *line, t_data *info);
void	parser_light(char *line, t_data *info);
void	parser_cylinder(char *line, t_data	*info);
void	parser_plane(char *line, t_data	*info);
void	parser_sphere(char *line, t_data *info);

//		DEBUG
void	print_vec3d(t_vec3d *a);

int		skip_spaces(char *s);
int	format_check(char *s);
double	ft_atoi_float(char *s);
char	*meaningful_string(char *line, int i);
void	validity_check_amb_light(t_data *info);
void	lstaddback(t_objects **lst, t_objects *new);
int		is_normal_vector(t_vec3d	*norm);
void	is_color(int r, int g, int b);
void	check_begining(char *s, char *line, int index);
int		key_hook(int key_code, t_data *img);
int		close_x(t_data	*info);
void	projection(t_data	*info);
t_ray	*make_ray(t_data *info, double x, double y);
void	ray_cast(t_ray *ray, t_data	*info, int x, int y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	intersect(t_data *info, int	pxl[2], t_ray *ray);
int	color_calculation(t_data *info, void *obj, t_ray *ray, int id, t_vec3d *inter);
void	check_form(char *line);


#endif