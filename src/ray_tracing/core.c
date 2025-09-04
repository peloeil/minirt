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
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

t_quad_root	solve_quadratic_equation(t_quad_coefs coefs)
{
	t_quad_root		quad_root;
	const double	discriminant = pow(coefs.b, 2) - 4 * coefs.a * coefs.c;

	quad_root.root_large = 0;
	quad_root.root_small = 0;
	if (coefs.a < 0)
	{
		coefs.a = -coefs.a;
		coefs.b = -coefs.b;
		coefs.c = -coefs.c;
	}
	if (EPSILON < fabs(coefs.a) && - EPSILON < discriminant)
	{
		quad_root.root_large = (-coefs.b + sqrt(discriminant)) / (2 * coefs.a);
		quad_root.root_small = (-coefs.b - sqrt(discriminant)) / (2 * coefs.a);
	}
	return (quad_root);
}

double	select_nearest_line_t_coef(const t_quad_root quad_root)
{
	if (0.0 < quad_root.root_small)
		return (quad_root.root_small);
	if (0.0 < quad_root.root_large)
		return (quad_root.root_large);
	return (0);
}

t_vec3	calculate_ray_intersection(const t_line line, const double line_t_coef)
{
	return (vec3_add(line.position, vec3_mult(line_t_coef, line.direction)));
}
