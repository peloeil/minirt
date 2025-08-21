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

#include <math.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

static t_quad_eq	solve_cylinder_quadratic_equation(
						const t_line line,
						const t_cylinder cylinder);
static int			validate_cylinder_vertical_position(
						const t_cylinder cylinder,
						const t_vec3 intersection);

t_ray	find_cylinder_ray_intersection(
			const t_line line,
			const t_cylinder cylinder)
{
	t_ray			ray;
	const t_quad_eq	quad_eq = solve_cylinder_quadratic_equation(line, cylinder);

	ray.line = line;
	ray.intersection = vec3_init(0, 0, 0);
	ray.exists_intersection = false;
	if (quad_eq.has_real_roots
		&& quad_eq.root_pos_is_valid
		&& quad_eq.root_neg_is_valid)
	{
		ray.intersection = find_ray_intersection(line, quad_eq);
		if (validate_cylinder_vertical_position(cylinder, ray.intersection))
			ray.exists_intersection = true;
	}
	return (ray);
}

static t_quad_eq	solve_cylinder_quadratic_equation(
						const t_line line,
						const t_cylinder cylinder)
{
	t_quad_coefs	coefs;
	const double	d1_dot_d2 = vec3_dot_prod(line.direction, cylinder.axis);
	const t_vec3	c1_sub_c2 = vec3_sub(line.position, cylinder.bottom_center);
	const double	d2_dot_c1_sub_c2 = vec3_dot_prod(cylinder.axis, c1_sub_c2);
	const double	d2_dot_c1_sub_c2_sq = pow(d2_dot_c1_sub_c2, 2);

	coefs.a = 1 - pow(d1_dot_d2, 2);
	coefs.b = \
		2 * (
			vec3_dot_prod(line.direction, c1_sub_c2)
			- (d1_dot_d2 * d2_dot_c1_sub_c2) \
		);
	coefs.c = \
		vec3_dot_prod(c1_sub_c2, c1_sub_c2)
		- d2_dot_c1_sub_c2_sq
		- pow(cylinder.radius, 2);
	return (solve_quadratic_equation(coefs));
}

static int	validate_cylinder_vertical_position(
				const t_cylinder cylinder,
				const t_vec3 intersection)
{
	const t_vec3	c_to_p = vec3_sub(intersection, cylinder.bottom_center);
	const double	projection = vec3_dot_prod(c_to_p, cylinder.axis);
	const double	half_height = cylinder.height / 2;

	if (fabs(projection) <= half_height)
		return (1);
	return (0);
}
