/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:56:50 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/14 20:56:50 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minirt/scene.h>

void	free_2darray(void *array[static 1]);
t_scene	*convert_line_into_object(const t_scene *const scene, const char line[static 1]);
t_scene	*parse_rt_file(const char file_path[static 1]);

#endif
