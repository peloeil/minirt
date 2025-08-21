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

#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

t_quad_eq	solve_quadratic_equation(const t_quad_coefs coefs)
{
	const double	discriminant = pow(coefs.b, 2) - 4 * coefs.a * coefs.c;

	if (isless(0, discriminant))
	{
		return (t_quad_eq){
			(-1 * coefs.b + sqrt(discriminant)) / (2 * coefs.a),
			(-1 * coefs.b - sqrt(discriminant)) / (2 * coefs.a),
			true
		};
	}
	return (t_quad_eq){
		0, 0, false
	};
}

t_vec3	solve_ray_intersection(const t_line line, const t_quad_eq quad_eq)
{
	const t_vec3	intersections1 = vec3_add(line.position, vec3_mult(quad_eq.root_pos, line.direction));
	const t_vec3	intersections2 = vec3_add(line.position, vec3_mult(quad_eq.root_neg, line.direction));
	const double	intersections_abs1 = vec3_abs(vec3_sub(intersections1, line.position));
	const double	intersections_abs2 = vec3_abs(vec3_sub(intersections2, line.position));

	if (islessequal(intersections_abs1, intersections_abs2))
		return (intersections1);
	return (intersections2);
}
