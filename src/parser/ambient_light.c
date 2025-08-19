#include <minirt/scene.h>
#include <minirt/parser.h>

void	assign_ambient_light_info(t_ambient_light *const node, const char info[static 1], const int i)
{
	if (i == 1)
		node->brightness = parse_double(info);
	if (i == 2)
		node->color = parse_color(info);
}
