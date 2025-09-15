/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:14 by sota              #+#    #+#             */
/*   Updated: 2025/09/15 19:54:44 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <stddef.h>

void	assign_ambient_light_info(
			t_ambient_light *const node,
			const char info[static 1],
			const size_t i)
{
	if (i == 1)
	{
		node->brightness = parse_double(info);
		if (node->brightness < 0.0 || 1.0 < node->brightness)
			exit(EXIT_FAILURE);
	}
	if (i == 2)
		node->color = parse_color(info);
}
