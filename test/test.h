
#ifndef TEST_H
# define TEST_H

# include "../miniRT.h"

int	test_cmp_d(void);

int	test_rest(void);

//	VECTOR
int	vec_cross(void);
int	vec_len(void);
int	vec_equal(void);
int	vec_cpy(void);
int	vec_norm(void);
int	vec_angle(void);

//	RAY
int	test_onray(void);
int	test_raycpy(void);
int	test_rayequal(void);

//	PLANE
int	p_point(void);
int	p_ray_in(void);
int	p_ray_touch(void);
int	p_ray_inter(void);

//	SPHERE
int	sr_touch(void);
int	sr_inter(void);
int	test_sphere(void);

//	CYLINDER
int	cyl_ray(void);
#endif