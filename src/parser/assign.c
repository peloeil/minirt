#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <libft/ft_string.h>

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

void	assign_info_to_obj(const int i, const char info[static 1], const t_scene *const obj)
{
	void *const	node = obj->content;
	t_tag		tag;

	if (i == 0)
	{
		*(t_tag *)node = identify_tag(info);
		return ;
	}
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
	exit(EXIT_FAILURE);
}
