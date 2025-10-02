/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:43:16 by sota              #+#    #+#             */
/*   Updated: 2025/09/15 22:54:56 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <stddef.h>

void	assign_sphere_info(
			t_sphere *const node,
			const char info[static 1],
			const size_t i)
{
	if (i == 1)
		node->center = parse_vec3(info);
	if (i == 2)
	{
		node->radius = parse_double(info) / 2;
		if (node->radius <= 0.0)
			exit_with_message("sphere: diameter must be positive");
	}
	if (i == 3)
		node->color = parse_color(info);
}
