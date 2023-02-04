#include"miniRT.h"
#include"math/operations.h"
void	vec3d_norm(t_vec3d *vec);
t_vec3d	*vec3d_cross(t_vec3d *a, t_vec3d *b);
double	vec3d_dot(t_vec3d	*a, t_vec3d *b);
double	vec3d_len(t_vec3d *vector);

// int		ft_atoi(const char *str);

// int		ft_isdigit(int c);
int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}
int		ft_atoi(const char *str)
{
	long	nb;
	int		neg;
	int		ovf;

	nb = 0;
	neg = 1;
	ovf = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') && ovf == 1)
	{
		nb = (nb * 10) + *str++ - 48;
		if (nb < 0)
			ovf = (neg == 1 ? -1 : 0);
	}
	return (ovf != 1 ? ovf : (int)(nb * neg));
}

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

double	ft_atoi_float(char *s)
{
	int		i;
	int		j;
	int		md;
	double	n;

	// j = skip_spaces(s);
	i = 0;
	while (s[i] && s[i] != '.')
		i++;
	md = i;
	if (s[i] && s[i] == '.')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	n = ft_atoi(s)+ ft_atoi(&s[md + 1]) * pow(10, - (i - md - 1));
	return (n);
}
int main()
{
	char *s ="       67833.88889     ";
	printf("J %f\n", ft_atoi_float(s));
}