#include <minirt/scene.h>
#include <minirt/parser.h>

void	assign_sphere_info(t_sphere *const node, const char info[static 1], const int i)
{
	if (i == 1)
		node->center = parse_vec3(info);
	if (i == 2)
		node->radius = parse_double(info);
	if (i == 3)
		node->color = parse_color(info);
}
