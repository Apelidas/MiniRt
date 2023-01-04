
#include "operations.h"

t_vec3d	*vec3d_cpy(t_vec3d *in)
{
	t_vec3d *out;

	out = create_vec3d(in->x, in->y, in->z);
	return (out);
}