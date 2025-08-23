/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:43 by sota              #+#    #+#             */
/*   Updated: 2025/08/20 01:19:03 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>

static void	validate_duplicate_tag(
				const t_scene *const scene,
				const t_scene *const obj)
{
	const t_scene	*cur;
	t_tag			obj_tag;

	if (scene == NULL)
		return ;
	cur = scene;
	while (true)
	{
		obj_tag = *(t_tag *)obj->content;
		if ((obj_tag == CAMERA
				|| obj_tag == AMBIENT_LIGHT
				|| obj_tag == LIGHT_SOURCE)
			&& obj_tag == *(t_tag *)cur->content)
			exit(EXIT_FAILURE);
		cur = cur->next;
		if (cur == scene)
			break ;
	}
}

static void	validate_object_filled(const t_scene *const obj, const size_t i)
{
	const t_tag	tag = *(t_tag *)obj->content;

	if (tag == PLANE && i == 4)
		return ;
	if (tag == SPHERE && i == 4)
		return ;
	if (tag == CYLINDER && i == 6)
		return ;
	if (tag == CAMERA && i == 4)
		return ;
	if (tag == AMBIENT_LIGHT && i == 3)
		return ;
	if (tag == LIGHT_SOURCE && i == 4)
		return ;
	exit(EXIT_FAILURE);
}

t_scene	*parse_rt_line(
			const t_scene *const scene,
			const char line[static 1])
{
	t_scene *const				obj = ft_list_new(NULL);
	const char *const *const	info = (const char **)ft_split(line, ' ');
	size_t						i;

	if (obj == NULL || info == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (info[i] != NULL)
	{
		assign_info_to_obj(obj, info[i], i);
		i++;
	}
	free_2darray((void **)info);
	validate_object_filled(obj, i);
	validate_duplicate_tag(scene, obj);
	return (obj);
}
