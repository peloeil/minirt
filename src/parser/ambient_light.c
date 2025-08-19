#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stddef.h>

void	assign_ambient_light_info(
			t_ambient_light *const node,
			const char info[static 1],
			const size_t i)
{
	if (i == 1)
		node->brightness = parse_double(info);
	if (i == 2)
		node->color = parse_color(info);
}
