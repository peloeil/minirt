/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:21:53 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/15 22:54:06 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene.h>
#include <minirt/parser.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <libft/std_string.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>

static t_string	read_rt_file(const char file_path[static 1])
{
	const int	fd = open(file_path, O_RDONLY);
	char		buf[BUF_SIZE];
	ssize_t		nbyte;
	t_string	res;

	if (ft_str_new(&res) == -1)
		exit_with_message("malloc() failed");
	while (true)
	{
		nbyte = read(fd, buf, BUF_SIZE - 1);
		if (nbyte == -1)
			exit_with_message("read() failed");
		if (nbyte == 0)
			break ;
		buf[nbyte] = '\0';
		if (ft_str_push_str(&res, buf) == -1)
			exit_with_message("malloc() failed");
	}
	close(fd);
	return (res);
}

static char	**read_rt_lines(const char file_path[static 1])
{
	const t_string				file = read_rt_file(file_path);
	const char *const *const	lines = (const char **)ft_split(file.str, '\n');

	if (lines == NULL)
		exit_with_message("malloc() failed");
	if (lines[0] == NULL)
		exit_with_message("rt file only contains newline characters");
	free(file.str);
	return ((char **)lines);
}

static void	validate_unique_tag(
				const t_scene *const scene,
				const t_tag tag)
{
	const t_scene	*cur = scene;
	int				count;

	count = 0;
	while (true)
	{
		if (tag == *(t_tag *)cur->content)
			count++;
		cur = cur->next;
		if (count > 1 || cur == scene)
			break ;
	}
	if (count != 1)
		exit_with_message("camera, ambient light and light source"
			" must be unique in a scene");
}

static void	validate_scene_tag(const t_scene *const scene)
{
	validate_unique_tag(scene, CAMERA);
	validate_unique_tag(scene, AMBIENT_LIGHT);
	validate_unique_tag(scene, LIGHT_SOURCE);
}

t_scene	*parse_rt_file(const char file_path[static 1])
{
	const char *const *const	lines = (const char **)read_rt_lines(file_path);
	size_t						i;
	const t_scene				*scene;

	i = 0;
	scene = NULL;
	while (lines[i] != NULL)
	{
		ft_list_push_back(
			(t_list **)&scene,
			parse_rt_line(lines[i])
			);
		i++;
	}
	free_2darray((void **)lines);
	validate_scene_tag(scene);
	return ((t_scene *)scene);
}
