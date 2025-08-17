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

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>

void	parse_rt_file(const char file_path[static 1])
{
	const int	fd = open(file_path, O_RDONLY);
	char		*lineptr;

	if (fd == -1)
		exit(EXIT_FAILURE);
	while (ft_getline(&lineptr, 0, fd) != -1)
	{
		// [TODO] オブジェクトの識別子を探してオブジェクトの種類を判定する
		// [TODO] 識別子が存在しなければエラー
		// [TODO] 仕様で定義された識別子 (A・C・L・sp・pl・cy) 以外があったらエラー
		// [TODO] 大文字の識別で表されるオブジェクトが 2 個以上あればエラー
	}
}

bool	is_rt_file_path(const char file_path[static 1])
{
	const int			fd = open(file_path, O_RDONLY);
	const size_t		len = ft_strlen(file_path);
	const char *const	ext = file_path - 3 + len;

	if (fd == -1)
		return (false);
	close(fd);
	if (len < 3 || ft_strcmp(ext, ".rt") != 0)
		return (false);
	return (true);
}
