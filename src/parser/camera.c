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
		node->direction = parse_vec3(info);
	if (i == 3)
		node->radian = parse_double(info) * M_PI / 180.0;
}
