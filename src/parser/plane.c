/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:43:04 by sota              #+#    #+#             */
/*   Updated: 2025/09/15 22:30:13 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <minirt/vec3.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

void	assign_plane_info(
			t_plane *const node,
			const char info[static 1],
			const size_t i)
{
	if (i == 1)
		node->position = parse_vec3(info);
	if (i == 2)
	{
		node->normal = parse_vec3(info);
		if (fabs(vec3_abs(node->normal) - 1.0) > EPSILON)
			exit_with_message("plane: normal vector must be normalized");
	}
	if (i == 3)
		node->color = parse_color(info);
}
