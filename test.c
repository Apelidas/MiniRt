#include"miniRT.h"
#include"math/operations.h"
void	vec3d_norm(t_vec3d *vec);
t_vec3d	*vec3d_cross(t_vec3d *a, t_vec3d *b);
double	vec3d_dot(t_vec3d	*a, t_vec3d *b);
double	vec3d_len(t_vec3d *vector);


double	vec3d_len(t_vec3d *vector)
{
	double	a;
	double	b;
	double	c;

	a = pow(vector->x, 2.0);
	b = pow(vector->y, 2.0);
	c = pow(vector->z, 2.0);
	a = sqrt(a + b + c);
	return (a);
}
double	vec3d_dot(t_vec3d	*a, t_vec3d *b)
{
	double	res;

	res = a->x * b->x + a->y * b->y + a->z * b->z;
	return (res);
}

t_vec3d	*vec3d_minus(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*res;

	res = malloc(sizeof(t_vec3d));
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return(res);
}

double	siphere_intersection(t_ray *ray, t_sphere *sphr)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;

	a = vec3d_dot(ray->dir, ray->dir);
	b = 2 * vec3d_dot(ray->dir, vec3d_minus(ray->origin, sphr->origin));
	c = pow(vec3d_len(ray->origin), 2) - pow(sphr->d / 2, 2);
	delta = pow(b , 2) - 4 * a * c;
	if (delta < 0 )
		return (-1);
	t1 = (-b + sqrt(delta)) / (2 * a);
	t2 = (-b - sqrt(delta)) / (2 * a);
	if (t1 >= 0 && t2 >= 0)
		return ((t1 > t2) ? t2 : t1);
	else if (t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	return (-1);
}
int main()
{
    t_ray   ray;
    t_data data;

    ray.dir = malloc(sizeof(t_vec3d));
    ray.origin = malloc(sizeof(t_vec3d));
    data.obj = malloc(sizeof(t_objects));
    data.obj->sphere = malloc(sizeof(t_sphere));
    data.obj->sphere->origin = malloc(sizeof(t_vec3d));

    data.obj->id = 1;
    data.obj->sphere->d = 5;
    data.obj->sphere->origin->x = 2;
    data.obj->sphere->origin->y = 2;
    data.obj->sphere->origin->z = 2;
    data.obj->next = NULL;
    ray.dir->x = 1;
    ray.dir->y = 1;
    ray.dir->z = 1;
    ray.origin->x = 0;
    ray.origin->y = 0;
    ray.origin->z = 0;
    printf("h %f \n", data.obj->sphere->origin->x);
    printf("intersection is %d \n", siphere_intersection(&ray, data.obj->sphere));
    int t = siphere_intersection(&ray, data.obj->sphere);
    printf("the point is %f", ray.origin->x + t * ray.dir->x);

}