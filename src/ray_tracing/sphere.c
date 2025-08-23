/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:10:43 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/18 20:10:43 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

static t_quad_root	solve_sphere_quadratic_equation(
						const t_line line,
						const t_sphere sphere);

t_ray	find_sphere_ray_intersection(const t_line line, const t_sphere sphere)
{
	t_ray				ray;
	const t_quad_root	quad_root = \
		solve_sphere_quadratic_equation(line, sphere);

	ray.line = line;
	ray.intersection = vec3_init(0, 0, 0);
	ray.exists_intersection = false;
	if (0 < quad_root.root_large)
	{
		ray.intersection = find_ray_intersection(line, quad_root);
		ray.exists_intersection = true;
	}
	return (ray);
}

static t_quad_root	solve_sphere_quadratic_equation(
						const t_line line,
						const t_sphere sphere)
{
	t_quad_coefs	coefs;
	const t_vec3	line_sphere_sub = vec3_sub(line.position, sphere.center);

	coefs.a = vec3_dot_prod(line.direction, line.direction);
	coefs.b = vec3_dot_prod(line_sphere_sub, line.direction) * 2;
	coefs.c = \
		vec3_dot_prod(line_sphere_sub, line_sphere_sub) - pow(sphere.radius, 2);
	return (solve_quadratic_equation(coefs));
}
