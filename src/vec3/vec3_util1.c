/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:45:54 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/04 14:45:54 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/vec3.h>

t_vec3	vec3_init(const double x, const double y, const double z, const int color)
{
	return ((t_vec3){x, y, z, color});
}

bool	vec3_eq(const t_vec3 v1, const t_vec3 v2)
{
	return (
		fabs(v1.x - v2.x) < EPSILON && \
		fabs(v1.y - v2.y) < EPSILON && \
		fabs(v1.z - v2.z) < EPSILON);
}

t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, 0});
}

t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, 0});
}

t_vec3	vec3_mult(const double scalar, const t_vec3 v)
{
	return ((t_vec3){scalar * v.x, scalar * v.y, scalar * v.z, v.color});
}
