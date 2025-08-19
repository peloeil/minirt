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

#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

t_ray	solve_sphere_ray_intersection(const t_line line, const t_sphere sphere)
{
	t_ray			ray;
	const t_quad_eq	quad_eq = solve_sphere_quadratic_equation(line, sphere);

	ray.line = line;
	ray.intersection = vec3_init(0, 0, 0);
	ray.exits_intersection = false;
	if (quad_eq.has_two_real_roots)
	{
		ray.exits_intersection = true;
		ray.intersection = solve_ray_intersection(line, quad_eq);
	}
	return (ray);
}

t_quad_eq	solve_sphere_quadratic_equation(const t_line line, const t_sphere sphere)
{
	t_quad_eq		quad_eq;
    const t_vec3    line_sphere_sub = vec3_sub(line.position, sphere.center);

	quad_eq.a = vec3_dot_prod(line.direction, line.direction);
	quad_eq.b = vec3_dot_prod(line_sphere_sub, line.direction) * 2;
	quad_eq.c = vec3_dot_prod(line_sphere_sub, line_sphere_sub) - pow(sphere.radius, 2);
	quad_eq.roots[0] = 0;
	quad_eq.roots[1] = 0;
	quad_eq.has_two_real_roots = false;
	return (solve_quadratic_equation(quad_eq));
}
