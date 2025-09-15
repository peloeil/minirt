/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:38 by sota              #+#    #+#             */
/*   Updated: 2025/09/15 22:19:15 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <stddef.h>

void	assign_light_source_info(
			t_light_source *const node,
			const char info[static 1],
			const size_t i)
{
	if (i == 1)
		node->position = parse_vec3(info);
	if (i == 2)
	{
		node->brightness = parse_double(info);
		if (node->brightness < 0.0 || 1.0 < node->brightness)
			exit_with_message("light: brightness must be in [0, 1]");
	}
	if (i == 3)
	{
		node->color = parse_color(info);
		node->sphere.tag = SPHERE;
		node->sphere.center = node->position;
		node->sphere.radius = 0.5 * node->brightness;
		node->sphere.color = node->color;
	}
}
