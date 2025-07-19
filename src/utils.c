/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:10:41 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/19 08:53:20 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	del_new_line(char **str)
{
	int	len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	if (len > 0 && (*str)[len - 1] == '\n')
		(*str)[len - 1] = '\0';
}

void	free_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	element_exist(char *line, int index)
{
	if (index < 0 || index >= (int)ft_strlen(line))
		return (0);
	while (index >= 0)
	{
		if (line[index] == '1' || line[index] == 'N' || line[index] == 'S'
			|| line[index] == 'E' || line[index] == 'W')
			return (1);
		index--;
	}
	return (0);
}

void	fill_spaces(t_map *map)
{
	int	j;

	if (!map || !map->data)
		return ;
	while (map)
	{
		j = ft_strlen(map->data) - 1;
		while (j >= 0)
		{
			if (map->data[j] == ' ')
			{
				if (element_exist(map->data, j - 1))
					map->data[j] = '1';
			}
			j--;
		}
		map = map->next;
	}
}

int	is_invalid_border_char(char c)
{
	return (c != '1' && c != ' ');
}
