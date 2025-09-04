/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:50:56 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/19 13:50:56 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

static double	solve_plane_equation(
					const t_line line,
					const t_plane plane);

t_ray	find_plane_ray_intersection(const t_line line, const t_plane plane)
{
	t_ray			ray;
	const double	t_coef = solve_plane_equation(line, plane);

	ray.line = line;
	ray.intersection = vec3_init(0, 0, 0);
	ray.hit_normal = vec3_init(0, 0, 0);
	ray.color = (t_color){0, 0, 0};
	ray.exists = false;
	if (EPSILON < t_coef)
	{
		ray.intersection = \
			vec3_add(line.position, vec3_mult(t_coef, line.direction));
		ray.hit_normal = plane.normal;
		ray.color = plane.color;
		ray.exists = true;
	}
	return (ray);
}

static double	solve_plane_equation(
					const t_line line,
					const t_plane plane)
{
	const double	n_dot_a = vec3_dot_prod(plane.normal, line.position);
	const double	n_dot_c = vec3_dot_prod(plane.normal, plane.position);
	const double	n_dot_d = vec3_dot_prod(plane.normal, line.direction);

	if (EPSILON < fabs(n_dot_d))
		return ((n_dot_c - n_dot_a) / n_dot_d);
	return (-1);
}
