/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:43 by sota              #+#    #+#             */
/*   Updated: 2025/09/15 22:47:54 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>

static void	validate_unique_tag(
				const t_scene *const scene,
				const t_scene *const obj)
{
	const t_scene	*cur = scene;
	t_tag			tag;
	int				count;

	tag = *(t_tag *)obj->content;
	if (scene == NULL
		|| (tag != CAMERA && tag != AMBIENT_LIGHT && tag != LIGHT_SOURCE))
		return ;
	count = 0;
	while (true)
	{
		if (tag == *(t_tag *)cur->content)
			count++;
		cur = cur->next;
		if (count == 2 || cur == scene)
			break ;
	}
	if (count != 1)
		exit_with_message("camera, ambient light and light source"
			" must be unique in a scene");
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
	exit_with_message("invalid number of fields in a line");
}

t_scene	*parse_rt_line(
			const t_scene *const scene,
			const char line[static 1])
{
	t_scene *const				obj = ft_list_new(NULL);
	const char *const *const	info = (const char **)ft_split(line, ' ');
	size_t						i;

	if (obj == NULL || info == NULL)
		exit_with_message("malloc() failed");
	i = 0;
	while (info[i] != NULL)
	{
		assign_info_to_obj(obj, info[i], i);
		i++;
	}
	free_2darray((void **)info);
	validate_unique_tag(scene, obj);
	validate_object_filled(obj, i);
	return (obj);
}
