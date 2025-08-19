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
#include <unistd.h>
#include <libft/std_string.h>
#include <libft/ft_string.h>

# define BUF_SIZE 1024 + 1

static t_string	read_rt_file(const char file_path[static 1])
{
	const int	fd = open(file_path, O_RDONLY);
	char		buf[BUF_SIZE];
	ssize_t		nbyte;
	t_string	res;

	if (ft_str_new(&res) == -1)
		exit(EXIT_FAILURE);
	while (true)
	{
		nbyte = read(fd, buf, BUF_SIZE - 1);
		if (nbyte == -1)
			exit(EXIT_FAILURE);
		if (nbyte == 0)
			break ;
		buf[nbyte] = '\0';
		if (ft_str_push_str(&res, buf) == -1)
			exit(EXIT_FAILURE);
	}
	close(fd);
	return (res);
}

static char	**read_rt_lines(const char file_path[static 1])
{
	const t_string	file = read_rt_file(file_path);
	const char *const *const lines = (const char **)ft_split(file.str, '\n');

	if (lines == NULL || lines[0] == NULL)
		exit(EXIT_FAILURE);
	free(file.str);
	return ((char **)lines);
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
			convert_line_into_object(scene, lines[i])
		);
		i++;
	}
	free_2darray((void **)lines);
	return ((t_scene *)scene);
}
