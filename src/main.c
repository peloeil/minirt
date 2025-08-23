/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:21:53 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/04 19:21:55 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser.h>
#include <minirt/scene.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>

static void	validate_rt_file_path(const char file_path[static 1])
{
	const int			fd = open(file_path, O_RDONLY);
	const size_t		len = ft_strlen(file_path);
	const char *const	ext = file_path - 3 + len;

	if (fd == -1)
		exit(EXIT_FAILURE);
	close(fd);
	if (len < 3 || ft_strcmp(ext, ".rt") != 0)
		exit(EXIT_FAILURE);
}

int	main(const int argc, const char *const argv[static argc])
{
	t_scene	*scene;

	if (argc != 2)
		return (EXIT_FAILURE);
	validate_rt_file_path(argv[1]);
	scene = parse_rt_file(argv[1]);
	ft_list_clear(&scene, free);
	return (EXIT_SUCCESS);
}
