#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stddef.h>

void	assign_plane_info(
			t_plane *const node,
			const char info[static 1],
			const size_t i)
{
	if (i == 1)
		node->position = parse_vec3(info);
	if (i == 2)
		node->normal = parse_vec3(info);
	if (i == 3)
		node->color = parse_color(info);
}
