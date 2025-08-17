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
#include <stdlib.h>

int	main(const int argc, const char *const argv[static argc])
{
	if (argc != 2)
		return (EXIT_FAILURE);
	if (!is_rt_file_path(argv[1]))
		return (EXIT_FAILURE);
	parse_rt_file(argv[1]);
	return (EXIT_SUCCESS);
}
