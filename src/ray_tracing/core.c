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

t_eq_roots	solve_quadratic_equation(t_quad_coefs coefs)
{
	t_eq_roots		eq_roots;
	const double	discriminant = pow(coefs.b, 2) - 4 * coefs.a * coefs.c;

	eq_roots.root1 = 0;
	eq_roots.root2 = 0;
	if (coefs.a < 0)
	{
		coefs.a = -coefs.a;
		coefs.b = -coefs.b;
		coefs.c = -coefs.c;
	}
	if (0 < fabs(coefs.a) && - EPSILON < discriminant)
	{
		eq_roots.root1 = (-coefs.b - sqrt(discriminant)) / (2 * coefs.a);
		eq_roots.root2 = (-coefs.b + sqrt(discriminant)) / (2 * coefs.a);
	}
	return (eq_roots);
}

double	select_nearest_line_t_coef(const t_eq_roots eq_roots)
{
	if (eq_roots.root1 < eq_roots.root2)
		return (eq_roots.root1);
	return (eq_roots.root2);
}

t_vec3	calculate_ray_intersection(const t_line line, const double line_t_coef)
{
	return (vec3_add(line.position, vec3_mult(line_t_coef, line.direction)));
}
