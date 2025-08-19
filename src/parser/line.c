#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>

static void	validate_duplicate_tag(const t_scene *const scene, const t_scene *const obj)
{
	const t_scene	*cur;
	t_tag			obj_tag;

	if (scene == NULL)
		return ;
	cur = scene;
	while (true)
	{
		obj_tag = *(t_tag *)obj->content;
		if ((obj_tag == CAMERA
			|| obj_tag == AMBIENT_LIGHT
			|| obj_tag == LIGHT_SOURCE)
			&& obj_tag == *(t_tag *)cur->content)
			exit(EXIT_FAILURE);
		cur = cur->next;
		if (cur == scene)
			break ;
	}
}

static void	validate_object_filled(const t_scene *const obj, const size_t i)
{
	const t_tag	tag = *(t_tag *)obj->content;

	if (tag == PLANE && i == 4)
		return ;
	if (tag == SPHERE && i == 4)
		return ;
	if (tag == CYLINDER && i == 6)
		return ;
	if (tag == CAMERA && i == 4)
		return ;
	if (tag == AMBIENT_LIGHT && i == 3)
		return ;
	if (tag == LIGHT_SOURCE && i == 4)
		return ;
	exit(EXIT_FAILURE);
}

void	free_2darray(void *array[static 1])
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
}

t_scene	*convert_line_into_object(const t_scene *const scene, const char line[static 1])
{
	t_scene *const				obj = ft_list_new(NULL);
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
	validate_object_filled(obj, i);
	validate_duplicate_tag(scene, obj);
	return (obj);
}
