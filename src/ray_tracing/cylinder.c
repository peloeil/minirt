/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:10:43 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/19 20:10:43 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

t_ray	solve_cylinder_ray_intersection(const t_line line, const t_cylinder cylinder)
{
	t_ray			ray;
	const t_quad_eq	quad_eq = solve_cylinder_quadratic_equation(line, cylinder);

	ray.line = line;
	ray.intersection = vec3_init(0, 0, 0);
	ray.exits_intersection = false;
	if (quad_eq.has_two_real_roots)
	{
		ray.intersection = solve_ray_intersection(line, quad_eq);
		if (validate_cylinder_vertical_position(cylinder, ray.intersection))
			ray.exits_intersection = true;
	}
	return (ray);
}

t_quad_eq	solve_cylinder_quadratic_equation(const t_line line, const t_cylinder cylinder)
{
	t_quad_eq		quad_eq;
	const double	d1_dot_d2 = vec3_dot_prod(line.direction, cylinder.axis);
	const t_vec3	c1_sub_c2 = vec3_sub(line.position, cylinder.bottom_center);
	const double	d2_dot_c1_sub_c2 = vec3_dot_prod(cylinder.axis, c1_sub_c2);

	quad_eq.a = 1 - pow(d1_dot_d2, 2);
	quad_eq.b = 2 * ((vec3_dot_prod(line.direction, c1_sub_c2)) - (d1_dot_d2 * d2_dot_c1_sub_c2));
	quad_eq.c = vec3_dot_prod(c1_sub_c2, c1_sub_c2) + pow(d2_dot_c1_sub_c2, 2) - (2 * pow(d2_dot_c1_sub_c2, 2)) - pow(cylinder.radius, 2);
	quad_eq.roots[0] = 0;
	quad_eq.roots[1] = 0;
	quad_eq.has_two_real_roots = false;
	return (solve_quadratic_equation(quad_eq));
}

int	validate_cylinder_vertical_position(const t_cylinder cylinder, const t_vec3 intersection)
{
	const t_vec3	c_to_p = vec3_sub(intersection, cylinder.bottom_center);
	const double	c_dot_p = vec3_dot_prod(c_to_p, c_to_p);
	const double	height = sqrt(c_dot_p - pow(cylinder.radius, 2));

	if ((cylinder.height / 2) + EPSILON < height)
		return (1);
	return (0);
}
