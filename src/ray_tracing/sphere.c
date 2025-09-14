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
#include <libft/ft_string.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

static t_quad_root	solve_sphere_quadratic_equation(
						const t_line line,
						const t_sphere sphere);

t_ray	find_sphere_ray_intersection(const t_line line, const t_sphere sphere)
{
	t_ray				ray;
	const t_quad_root	quad_root = solve_sphere_quadratic_equation(\
		line, sphere \
	);

	ft_bzero(&ray, sizeof(ray));
	ray.line = line;
	ray.line_t_coef = select_nearest_line_t_coef(quad_root);
	if (0 < ray.line_t_coef)
	{
		ray.intersection = calculate_ray_intersection(line, ray.line_t_coef);
		ray.hit_normal = vec3_norm(vec3_sub(ray.intersection, sphere.center));
		ray.color = sphere.color;
		ray.hit_exists = true;
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
		vec3_dot_prod(line_sphere_sub, line_sphere_sub)
		- pow(sphere.radius, 2);
	return (solve_quadratic_equation(coefs));
}
