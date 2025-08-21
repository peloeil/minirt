/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:23:25 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/18 18:23:25 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

t_quad_eq	solve_quadratic_equation(const t_quad_coefs coefs)
{
	t_quad_eq		quad_eq;
	const double	discriminant = pow(coefs.b, 2) - 4 * coefs.a * coefs.c;

	quad_eq.root_pos = 0;
	quad_eq.root_neg = 0;
	quad_eq.root_pos_is_valid = false;
	quad_eq.root_neg_is_valid = false;
	quad_eq.has_real_roots = false;
	if (fabs(coefs.a) < EPSILON && -EPSILON < discriminant)
	{
		quad_eq.root_pos = (-coefs.b + sqrt(discriminant)) / (2 * coefs.a);
		quad_eq.root_neg = (-coefs.b - sqrt(discriminant)) / (2 * coefs.a);
		quad_eq.root_pos_is_valid = (bool)(0 < quad_eq.root_pos);
		quad_eq.root_neg_is_valid = (bool)(0 < quad_eq.root_neg);
		quad_eq.has_real_roots = true;
	}
	return (quad_eq);
}

t_vec3	find_ray_intersection(const t_line line, const t_quad_eq quad_eq)
{
	const t_vec3	intersections1 = \
		vec3_add(line.position, vec3_mult(quad_eq.root_pos, line.direction));
	const t_vec3	intersections2 = \
		vec3_add(line.position, vec3_mult(quad_eq.root_neg, line.direction));

	if (quad_eq.root_pos_is_valid && quad_eq.root_neg_is_valid)
	{
		if (quad_eq.root_pos <= quad_eq.root_neg)
			return (intersections1);
		else
			return (intersections2);
	}
	if (quad_eq.root_pos_is_valid)
		return (intersections1);
	else
		return (intersections2);
}
