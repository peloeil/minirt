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

static t_quad_root	solve_cylinder_quadratic_equation(
						const t_line line,
						const t_cylinder cylinder);
static bool			is_within_height_range(
						const t_cylinder cylinder,
						const t_vec3 intersection);
static t_vec3		solve_cylinder_normal_vector(
						const t_cylinder cylinder, 
						const t_vec3 intersection);

t_ray	find_cylinder_ray_intersection(
			const t_line line,
			const t_cylinder cylinder)
{
	t_ray				ray;
	const t_quad_root	quad_root = \
		solve_cylinder_quadratic_equation(line, cylinder);

	ray.line = line;
	ray.intersection = vec3_init(0, 0, 0);
	ray.normal = vec3_init(0, 0, 0);
	ray.target_object = NULL;
	ray.exists = false;
	if (0 < quad_root.root_large)
	{
		ray.intersection = find_ray_intersection(line, quad_root);
		if (!is_within_height_range(cylinder, ray.intersection))
			return (ray);    // [TODO] ここに上面または底面との交差点算出を実装する
		ray.normal = solve_cylinder_normal_vector(cylinder, ray.intersection);
		ray.exists = true;
	}
	return (ray);
}

static t_quad_root	solve_cylinder_quadratic_equation(
						const t_line line,
						const t_cylinder cylinder)
{
	t_quad_coefs	coefs;
	const double	d1_dot_d2 = vec3_dot_prod(line.direction, cylinder.axis);
	const t_vec3	c1_sub_c2 = vec3_sub(line.position, cylinder.center);
	const double	d2_dot_c1_sub_c2 = vec3_dot_prod(cylinder.axis, c1_sub_c2);

	coefs.a = 1 - pow(d1_dot_d2, 2);
	coefs.b = \
		2 * (
			vec3_dot_prod(line.direction, c1_sub_c2)
			- (d1_dot_d2 * d2_dot_c1_sub_c2) \
		);
	coefs.c = \
		vec3_dot_prod(c1_sub_c2, c1_sub_c2)
		- pow(d2_dot_c1_sub_c2, 2)
		- pow(cylinder.radius, 2);
	return (solve_quadratic_equation(coefs));
}

static bool	is_within_height_range(
				const t_cylinder cylinder,
				const t_vec3 intersection)
{
	const t_vec3	c_to_p = vec3_sub(intersection, cylinder.center);
	const double	projection = vec3_dot_prod(c_to_p, cylinder.axis);
	const double	half_height = cylinder.height / 2;

	if (fabs(projection) <= half_height)
		return (true);
	return (false);
}

static t_vec3	solve_cylinder_normal_vector(
					const t_cylinder cylinder, 
					const t_vec3 intersection)
{
	const t_vec3	c_to_p = vec3_sub(intersection, cylinder.center);

	return (vec3_norm(
		vec3_sub(
			c_to_p,
			vec3_mult(vec3_dot_prod(c_to_p, cylinder.axis), cylinder.axis)
		)
	));
}
