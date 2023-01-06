
#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "../miniRT.h"

typedef struct s_vec3d t_vec3d;
typedef struct s_ray t_ray;

/*				Memory Functions of Math Objects		*/
t_vec3d	*create_vec3d(double x, double y, double z);
t_ray	*create_ray();
t_ray	*create_oray(double x, double y, double z);
t_ray	*create_dray(double x, double y, double z, int trgb);
t_ray	*create_vray(t_vec3d *origin, t_vec3d *dir, int trgb);
void	destroy_ray(t_ray *todel);

/*				Mathmetical Operations of Math Objects		*/
double	vec3d_len(t_vec3d *vector);
void	vec3d_norm(t_vec3d *vec);
t_vec3d	*vec3d_cpy(t_vec3d *in);
int		vec3d_equal(t_vec3d *a, t_vec3d *b);
t_vec3d	*vec3d_scalar(t_vec3d *a, t_vec3d *b);
t_vec3d	*vec3d_cross(t_vec3d *a, t_vec3d *b);

int		ray_vec3d(t_ray *ray, t_vec3d *point);
t_ray	*ray_cpy(t_ray *in);
int		ray_equal(t_ray *a, t_ray *b);

int		cmp_d(double a, double b);

#endif