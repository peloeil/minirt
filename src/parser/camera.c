/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:26 by sota              #+#    #+#             */
/*   Updated: 2025/08/19 22:41:27 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <minirt/vec3.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

void	assign_camera_info(
			t_camera *const node,
			const char info[static 1],
			const size_t i)
{
	if (i == 1)
		node->position = parse_vec3(info);
	if (i == 2)
	{
		node->forward = parse_vec3(info);
		if (fabs(vec3_abs(node->forward) - 1.0) > EPSILON)
			exit(EXIT_FAILURE);
	}
	if (i == 3)
	{
		node->radian = parse_double(info) * M_PI / 180.0;
		if (node->radian < 0.0 || M_PI < node->radian)
			exit(EXIT_FAILURE);
	}
}
