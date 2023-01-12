
#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "../miniRT.h"

typedef struct s_vec3d t_vec3d;
typedef struct s_ray t_ray;
typedef struct s_plain t_plane;
typedef struct s_sphere t_sphere;

/*				Memory Functions of Math Objects		*/
t_vec3d	*create_vec3d(double x, double y, double z);
t_ray	*create_ray();
t_ray	*create_oray(double x, double y, double z);
t_ray	*create_dray(double x, double y, double z, int trgb);
t_ray	*create_vray(t_vec3d *origin, t_vec3d *dir, int trgb);
void	destroy_ray(t_ray *todel);
t_plane	*create_plane(t_vec3d *origin, t_vec3d *norm, int trgb);
void	destroy_plane(t_plane *todel);

/*				Mathmetical Operations of Math Objects		*/
int		cmp_d(double a, double b);

//		vec3d functions
int		vec3d_equal(t_vec3d *a, t_vec3d *b);
t_vec3d	*vec3d_cross(t_vec3d *a, t_vec3d *b);
double	vec3d_len(t_vec3d *vector);
t_vec3d	*vec3d_cpy(t_vec3d *in);
void	vec3d_norm(t_vec3d *vec);
double	vec3d_angle(t_vec3d *a, t_vec3d *b);
double	vec3d_dot(t_vec3d	*a, t_vec3d *b);

//		ray functions
int		ray_vec3d(t_ray *ray, t_vec3d *point);
int		ray_equal(t_ray *a, t_ray *b);
t_ray	*ray_cpy(t_ray *in);
double	ray_angle(t_ray *a, t_ray *b);

//		plane functions
int		plane_point(t_vec3d *point, t_plane	*plane);
int		plane_ray_in(t_ray	*ray, t_plane	*plane);
int		plane_ray_touch(t_ray *ray, t_plane	*plane);
t_vec3d	*plane_ray_inter(t_ray *ray, t_plane *plane);

//		sphere functions
int		sphere_point(t_vec3d *point, t_sphere *ball);

#endif