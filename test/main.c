
#include "test.h"

/*
Readability and Norminette Function
*/
int	run_test(char *name, int (*test)())
{
	write(1, KBLU, 5);
	write(1, "\t", 1);
	write(1, name, ft_strlen(name));
	write(1, ":\t", 2);
	if (!(*test)())
	{
		write(1, KRED, 5);
		write(1, "Failed\n", 7);
		write(1, KNRM, 4);
		return (0);
	}
	write(1, KGRN, 5);
	write(1, "OK\n", 3);
	write(1, KNRM, 4);
	return (1);
}

int	test_vec(void)
{
	if (!run_test("VecEqual", &vec_equal))
		return (0);
	if (!run_test("VecCross", &vec_cross))
		return (0);
	if (!run_test("VecLen\t", &vec_len))
		return (0);
	if (!run_test("VecCpy\t", &vec_cpy))
		return (0);
	if (!run_test("VecNorm", &vec_norm))
		return (0);
	if (!run_test("VecAngle", &vec_angle))
		return (0);
	return (1);
}

int	test_ray(void)
{
	if(!run_test("RayVec3d", &test_onray))
		return (0);
	if(!run_test("RayEqual", &test_rayequal))
		return (0);
	if(!run_test("RayCpy\t", &test_raycpy))
		return (0);
	return (1);
}

int	test_plane(void)
{
	if(!run_test("PlanePoint", &p_point))
		return (0);
	if(!run_test("PlaneRayIN", &p_ray_in))
		return (0);
	if(!run_test("PlaneRayTouch", &p_ray_touch))
		return (0);
	if(!run_test("PlaneRayInter", &p_ray_inter))
		return (0);
	return (1);
}

int	test_sphere(void)
{
	if(!run_test("SphereRayTouch", &sr_touch))
		return (0);
	return (1);
}

/*
ADD automated Github Tests here
this main runs the automated GitHub tests
*/
int	main(void)
{
	if (!run_test("testRest", &test_rest))
		return (1);
	if (!run_test("test_cmp_d", &test_cmp_d))
		return (1);
	write(1, "\nVector:\n", 9);
	if (!test_vec())
		return (1);
	write(1, "\nRay:\n", 6);
	if (!test_ray())
		return (1);
	write(1, "\nPlane:\n", 8);
	if (!test_plane())
		return (1);
	write(1, "\nSphere:\n", 9);
	if (!test_sphere())
		return (1);
	return (0);
}
