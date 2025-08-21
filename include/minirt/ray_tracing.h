/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:30:05 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/18 16:30:05 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

#include <stdbool.h>
#include <minirt/vec3.h>

typedef struct s_quad_coefs
{
	double	a;
	double	b;
	double	c;
}	t_quad_coefs;

typedef struct s_quad_eq
{
	double	root_pos;
	double	root_neg;
	bool	root_pos_is_valid;
	bool	root_neg_is_valid;
	bool	has_two_real_roots;
}	t_quad_eq;

typedef struct s_ray
{
	t_line	line;
	t_vec3	intersection;
	bool	exists_intersection;
}	t_ray;

// core.c
t_quad_eq	solve_quadratic_equation(const t_quad_coefs coefs);
t_vec3		find_ray_intersection(const t_line line, const t_quad_eq quad_eq);

// plane.c
t_ray		solve_plane_ray_intersection(const t_line line, const t_plane plane);

// sphere.c
t_ray		solve_sphere_ray_intersection(const t_line line, const t_sphere sphere);

// cylinder.c
t_ray		solve_cylinder_ray_intersection(const t_line line, const t_cylinder cylinder);

#endif
