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
#include <libft/ft_string.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

static t_ray		find_cylinder_caps_ray_intersection(
						t_ray ray,
						const t_line line,
						const t_cylinder cylinder);
static t_eq_roots	solve_cylinder_quadratic_equation(
						const t_line line,
						const t_cylinder cylinder);
static bool			is_within_height_range(
						const t_cylinder cylinder,
						const t_vec3 intersection);
static t_vec3		calculate_cylinder_normal_vector(
						const t_cylinder cylinder,
						const t_vec3 intersection);

t_ray	find_cylinder_ray_intersection(
			const t_line line,
			const t_cylinder cylinder)
{
	t_ray		ray;
	t_eq_roots	eq_roots;

	ft_bzero(&ray, sizeof(ray));
	ray.line = line;
	ray = find_cylinder_caps_ray_intersection(ray, line, cylinder);
	if (ray.hit_object == CYLINDER)
		return (ray);
	eq_roots = solve_cylinder_quadratic_equation(line, cylinder);
	ray.line_t_coef = select_nearest_line_t_coef(eq_roots);
	if (EPSILON < ray.line_t_coef)
	{
		ray.intersection = calculate_ray_intersection(line, ray.line_t_coef);
		if (!is_within_height_range(cylinder, ray.intersection))
			return (ray);
		ray.hit_normal = calculate_cylinder_normal_vector(\
			cylinder, ray.intersection \
		);
		ray.color = cylinder.color;
		ray.hit_object = CYLINDER;
	}
	return (ray);
}

static t_ray	find_cylinder_caps_ray_intersection(
					t_ray ray,
					const t_line line,
					const t_cylinder cylinder)
{
	t_cylinder_cap_type	type;
	const t_eq_roots	eq_roots = (t_eq_roots){
		solve_plane_equation(line, cylinder.caps[TOP]),
		solve_plane_equation(line, cylinder.caps[BOTTOM])
	};

	ray.line_t_coef = select_nearest_line_t_coef(eq_roots);
	if (!(EPSILON < ray.line_t_coef))
		return (ray);
	ray.intersection = calculate_ray_intersection(line, ray.line_t_coef);
	type = TOP;
	if (ray.line_t_coef == eq_roots.root2)
		type = BOTTOM;
	if (cylinder.radius
		< vec3_length(ray.intersection, cylinder.caps[type].position))
		return (ray);
	if (vec3_dot_prod(line.direction, cylinder.caps[!type].normal) < EPSILON)
		return (ray);
	ray.hit_normal = cylinder.caps[type].normal;
	ray.color = cylinder.color;
	ray.hit_object = CYLINDER;
	return (ray);
}

static t_eq_roots	solve_cylinder_quadratic_equation(
						const t_line line,
						const t_cylinder cylinder)
{
	t_quad_coefs	coefs;
	const double	d1_dot_d2 = vec3_dot_prod(line.direction, cylinder.axis);
	const t_vec3	c1_sub_c2 = vec3_sub(line.position, cylinder.center);
	const double	d2_dot_c1_sub_c2 = vec3_dot_prod(cylinder.axis, c1_sub_c2);

	coefs.a = 1 - pow(d1_dot_d2, 2);
	coefs.b = 2 * (
			vec3_dot_prod(line.direction, c1_sub_c2)
			- (d1_dot_d2 * d2_dot_c1_sub_c2) \
		);
	coefs.c = vec3_dot_prod(c1_sub_c2, c1_sub_c2)
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

static t_vec3	calculate_cylinder_normal_vector(
					const t_cylinder cylinder,
					const t_vec3 intersection)
{
	const t_vec3	c_to_p = vec3_sub(intersection, cylinder.center);

	return (
		vec3_norm(
			vec3_sub(
				c_to_p,
				vec3_mult(vec3_dot_prod(c_to_p, cylinder.axis), cylinder.axis)
			)
		)
	);
}
