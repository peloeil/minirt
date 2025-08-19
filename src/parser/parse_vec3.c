#include <minirt/vec3.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <libft/ft_string.h>

t_vec3	parse_vec3(const char str[static 1])
{
	const char *const *const	xyz = (const char **)ft_split(str, ',');
	size_t						i;
	t_vec3						res;

	if (xyz == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	if (xyz[i++] != NULL)
		res.x = parse_double(xyz[i]);
	if (xyz[i++] != NULL)
		res.y = parse_double(xyz[i]);
	if (xyz[i++] != NULL)
		res.z = parse_double(xyz[i]);
	if (i != 3)
		exit(EXIT_FAILURE);
	free_2darray((void **)xyz);
	return (res);
}
