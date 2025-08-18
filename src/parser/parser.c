/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:21:53 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/04 19:21:55 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

static int	get_next_line(const char **lineptr, const int fd)
{
	size_t	size;
	int		status;

	*lineptr = NULL;
	size = 0;
	status = ft_getline((char **)lineptr, &size, fd);
	if (status == -2)
		exit(EXIT_FAILURE);
	return (status);
}

t_scene	*parse_rt_file(const char file_path[static 1])
{
	const int		fd = open(file_path, O_RDONLY);
	const t_scene	*scene;
	const char		*line;
	int				status;

	scene = NULL;
	while (true)
	{
		status = get_next_line(&line, fd);
		ft_list_push_back(
			(t_list **)&scene,
			convert_line_into_object(scene, line)
		);
		free((void *)line);
		if (status == -1)
			break ;
	}
	close(fd);
	return ((t_scene *)scene);
}
