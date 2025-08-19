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
#include <minirt/scene.h>

typedef struct s_quad_eq
{
	double	a;
	double	b;
	double	c;
	double	roots[2];
	bool	has_two_real_roots;
}	t_quad_eq;

typedef struct s_ray
{
	t_line	line;
	t_vec3	intersection;
	bool	exits_intersection;
}	t_ray;

#endif
