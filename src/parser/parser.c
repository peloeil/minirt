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

# include <minirt/parser.h>

void	parse_rt_file(const char *file_path)
{
	int		fd;
	char	*lineptr;

	if (validate_file_extension(file_path))
		exit(1);
	lineptr = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!lineptr)
		exit(1);
	fd = open(file_path, O_RDONLY);
	while (ft_getline(&lineptr, BUFFER_SIZE, fd) != -1)
	{
		// [TODO] オブジェクトの識別子を探してオブジェクトの種類を判定する
		// [TODO] 識別子が存在しなければエラー
		// [TODO] 仕様で定義された識別子 (A・C・L・sp・pl・cy) 以外があったらエラー
		// [TODO] 大文字の識別で表されるオブジェクトが 2 個以上あればエラー
	}
}

bool	validate_file_extension(const char *file_path)
{
	const char	*extension = ".rt";
	const char	*dotptr;

	dotptr = ft_strrchr(file_path, '.');
	if (dotptr && ft_strnstr(dotptr, extension, ft_strlen(dotptr)))
		return (true);
	return (false);
}
