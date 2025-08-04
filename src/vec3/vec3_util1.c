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

t_vec3	vec3_init(double x, double y, double z, int color)
{
	return ((t_vec3){x, y, z, color});
}

bool	vec3_eq(t_vec3 v1, t_vec3 v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (true);
	return (false);
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, 0});
}

t_vec3	vec3_sub(t_vec3 v1_from, t_vec3 v2_offset)
{
	return ((t_vec3){
		v1_from.x - v2_offset.x,
		v1_from.y - v2_offset.y,
		v1_from.z - v2_offset.z,
		0});
}

t_vec3	vec3_mult(t_vec3 v, double scalar)
{
	return ((t_vec3){v.x * scalar, v.y * scalar, v.z * scalar, v.color});
}
