#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <libft/ft_string.h>
#include <libft/ft_stdlib.h>

static t_tag	identify_tag(const char str[static 1])
{
	if (ft_strcmp(str, "A") == 0)
		return (AMBIENT_LIGHT);
	if (ft_strcmp(str, "C") == 0)
		return (CAMERA);
	if (ft_strcmp(str, "L") == 0)
		return (LIGHT_SOURCE);
	if (ft_strcmp(str, "sp") == 0)
		return (SPHERE);
	if (ft_strcmp(str, "pl") == 0)
		return (PLANE);
	if (ft_strcmp(str, "cy") == 0)
		return (CYLINDER);
	exit(EXIT_FAILURE);
}

static t_tag	*allocate_node(const t_tag tag)
{
	t_tag	*res;

	if (tag == PLANE)
		res = (t_tag *)ft_calloc(1, sizeof(t_plane));
	if (tag == SPHERE)
		res = (t_tag *)ft_calloc(1, sizeof(t_sphere));
	if (tag == CYLINDER)
		res = (t_tag *)ft_calloc(1, sizeof(t_cylinder));
	if (tag == CAMERA)
		res = (t_tag *)ft_calloc(1, sizeof(t_camera));
	if (tag == AMBIENT_LIGHT)
		res = (t_tag *)ft_calloc(1, sizeof(t_ambient_light));
	if (tag == LIGHT_SOURCE)
		res = (t_tag *)ft_calloc(1, sizeof(t_light_source));
	if (res == NULL)
		exit(EXIT_FAILURE);
	return (res);
}

void	assign_info_to_obj(
			const size_t i,
			const char info[static 1],
			t_scene *const obj)
{
	t_tag	tag;
	void	*node;

	if (i == 0)
	{
		obj->content = allocate_node(identify_tag(info));
		*(t_tag *)(obj->content) = identify_tag(info);
		return ;
	}
	node = obj->content;
	tag = *(t_tag *)node;
	if (tag == AMBIENT_LIGHT)
		assign_ambient_light_info((t_ambient_light *)node, info, i);
	else if (tag == CAMERA)
		assign_camera_info((t_camera *)node, info, i);
	else if (tag == LIGHT_SOURCE)
		assign_light_source_info((t_light_source *)node, info, i);
	else if (tag == SPHERE)
		assign_sphere_info((t_sphere *)node, info, i);
	else if (tag == PLANE)
		assign_plane_info((t_plane *)node, info, i);
	else if (tag == CYLINDER)
		assign_cylinder_info((t_cylinder *)node, info, i);
	else
		exit(EXIT_FAILURE);
}
