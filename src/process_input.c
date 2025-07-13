/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:08:39 by mohammad-bo       #+#    #+#             */
/*   Updated: 2025/07/13 14:23:39 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	process_map_line(char *line, t_cub3d *cub3d)
{
	t_map	*new_map;
	char	*dup_line;

	if (!border_map(line))
	{
		ft_fprintf(2, "Error: Invalid Texture\n");
		return (-1);
	}
	dup_line = ft_strdup(line);
	if (!dup_line)
		return (-1);
	new_map = new_map_node(dup_line, 1);
	if (!new_map)
		return (-1);
	add_node_map(&cub3d->map, new_map);
	return (2);
}

int	process_texture_and_color(char **tokens, t_cub3d *cub3d)
{
	int	result;

	result = check_dir_text(tokens, cub3d);
	if (result == -1)
		return (-1);
	if (result == 1)
		return (0);
	result = check_color(tokens, cub3d);
	if (result == -1)
		return (-1);
	if (result == 1)
		return (0);
	ft_free_split(tokens);
	return (1);
}

int	handle_trim_and_split(char *line, char ***tokens)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (-1);
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		return (0);
	}
	*tokens = ft_split(trimmed, ' ');
	free(trimmed);
	if (!*tokens)
		return (-1);
	return (1);
}

int	process_input(char *line, t_cub3d *cub3d)
{
	char	**tokens;
	int		result;

	tokens = NULL;
	result = handle_trim_and_split(line, &tokens);
	if (result <= 0)
		return (result);
	result = process_texture_and_color(tokens, cub3d);
	if (result <= 0)
		return (result);
	return (process_map_line(line, cub3d));
}
