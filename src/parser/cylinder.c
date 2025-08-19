/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:32 by sota              #+#    #+#             */
/*   Updated: 2025/08/19 22:41:34 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stddef.h>

void	assign_cylinder_info(
			t_cylinder *const node,
			const char info[static 1],
			const size_t i)
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
