/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 21:38:17 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/09 21:38:17 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>

t_camera	*find_camera_in_scene(const t_scene *const scene)
{
	t_tag			tag;
	const t_scene	*node = scene;

	while (true)
	{
		tag = *(t_tag *)node->content;
		if (tag == CAMERA)
			return ((t_camera *)node->content);
		node = node->next;
		if (scene == node)
			break ;
	}
	return (NULL);
}

t_light_source	*find_light_source_in_scene(const t_scene *const scene)
{
	t_tag			tag;
	const t_scene	*node = scene;

	while (true)
	{
		tag = *(t_tag *)node->content;
		if (tag == LIGHT_SOURCE)
			return ((t_light_source *)node->content);
		node = node->next;
		if (scene == node)
			break ;
	}
	return (NULL);
}
