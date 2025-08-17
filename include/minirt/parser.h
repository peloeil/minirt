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

# include <stdbool.h>

bool	is_rt_file_path(const char file_path[static 1]);
void	parse_rt_file(const char file_path[static 1]);

#endif
