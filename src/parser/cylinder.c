#include <minirt/scene.h>
#include <minirt/parser.h>

void	assign_cylinder_info(t_cylinder *const node, const char info[static 1], const int i)
{
	if (i == 1)
		node->bottom_center = parse_vec3(info); // TODO: center
	if (i == 2)
		node->axis = parse_vec3(info);
	if (i == 3)
		node->radius = parse_double(info) / 2;
	if (i == 4)
		node->height = parse_double(info);
	if (i == 5)
		node->color = parse_color(info);
}
