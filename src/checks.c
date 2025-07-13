/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:09:55 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/13 14:07:33 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;

	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len < extension_len)
		return (-1);
	if (ft_strcmp(filename + filename_len - extension_len, extension) != 0)
		return (-1);
	return (0);
}

int	read_texture(int fd, t_cub3d *cub3d)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		del_new_line(&line);
		result = process_input(line, cub3d);
		free(line);
		if (result == -1)
			return (-1);
		else if (result == 2)
			break ;
		line = get_next_line(fd);
	}
	return (0);
}

int	handle_line(char *line, int index, t_cub3d *cub3d)
{
	t_map	*new_map;

	del_new_line(&line);
	if (line[0] == '\0')
	{
		free(line);
		return (-1);
	}
	new_map = new_map_node(line, index);
	if (!new_map)
	{
		free(line);
		return (-1);
	}
	add_node_map(&cub3d->map, new_map);
	return (0);
}

int	read_map(int fd, t_cub3d *cub3d)
{
	char	*line;
	int		i;

	i = 2;
	line = get_next_line(fd);
	while (line)
	{
		if (handle_line(line, i, cub3d) == -1)
			return (-1);
		line = get_next_line(fd);
		i++;
	}
	if (!cub3d->map)
		return (-1);
	return (0);
}

int	read_file(int fd, t_cub3d *cub3d)
{
	if (read_texture(fd, cub3d) == -1)
	{
		free_lines(fd);
		return (-1);
	}
	if (read_map(fd, cub3d) == -1)
	{
		free_lines(fd);
		return (-1);
	}
	if (is_all_text_exist(cub3d) == -1)
		return (-1);
	if (open_textures(cub3d) == -1)
		return (-1);
	if (check_map(cub3d) == -1)
		return (-1);
	print_cub3d(cub3d);
	return (0);
}
