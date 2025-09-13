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

static t_vec3	calculate_camera_up(const t_vec3 forward);

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
		node->up = calculate_camera_up(node->forward);
		node->right = vec3_cross_prod(node->forward, node->up);
	}
	if (i == 3)
	{
		node->radian = parse_double(info) * M_PI / 180.0;
		if (node->radian < 0.0 || M_PI < node->radian)
			exit(EXIT_FAILURE);
	}
}

static t_vec3	calculate_camera_up(const t_vec3 forward)
{
	double			f_dot_z;
	double			a;
	double			b;
	const t_vec3	z_axis = (t_vec3){0, 0, 1};

	if (vec3_eq(forward, z_axis))
		return ((t_vec3){0, -1, 0});
	f_dot_z = vec3_dot_prod(forward, z_axis);
	a = -f_dot_z / fabs(sqrt(1 - pow(f_dot_z, 2)));
	b = 1 / fabs(sqrt(1 - pow(f_dot_z, 2)));
	return (vec3_add(vec3_mult(a, forward), vec3_mult(b, z_axis)));
}
