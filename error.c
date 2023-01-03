
#include "miniRT.h"

void	*error(char *message)
{
	write(2, "ERROR\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (NULL);
}