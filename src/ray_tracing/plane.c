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
#include <libft/ft_string.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

static double	solve_plane_equation(
					const t_line line,
					const t_plane plane);

t_ray	find_plane_ray_intersection(const t_line line, const t_plane plane)
{
	t_ray			ray;

	ft_bzero(&ray, sizeof(ray));
	ray.line = line;
	ray.line_t_coef = solve_plane_equation(line, plane);
	if (EPSILON < ray.line_t_coef)
	{
		ray.intersection = calculate_ray_intersection(line, ray.line_t_coef);
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
