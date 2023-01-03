
#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "../miniRT.h"


/*				Memory Functions of Math Objects								*/
t_vec3d	*create_vec3d(double x, double y, double z);


/*				Mathmetical Operations of Math Objects							*/
double	vec3d_len(vec3d *vector);
t_vec3d	*cross(t_vec3d *a, t_vec3d *b);


#endif