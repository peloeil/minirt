#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <libft/ft_string.h>
#include <libft/ft_stdlib.h>

static void	free_2darray(void *array[static 1])
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
}

t_scene	*convert_line_into_object(const t_scene *const scene, const char line[static 1])
{
	t_scene *const				obj = ft_calloc(1, sizeof(t_scene));
	const char *const *const	info = (const char **)ft_split(line, ' ');
	size_t						i;

	if (obj == NULL || info == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (info[i] != NULL)
	{
		assign_info_to_obj(i, info[i], obj);
		i++;
	}
	free_2darray((void **)info);
	return (obj);
}
