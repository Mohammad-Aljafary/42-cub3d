/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaman-alrifai <yaman-alrifai@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:09:42 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/17 08:36:58 by yaman-alrif      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_surrounding(t_map *map, int index)
{
	if (!map || !map->data || index <= 0)
		return (-1);
	if (map->data[index - 1] == ' ' || map->data[index + 1] == ' '
		|| map->data[index + 1] == '\0')
		return (-1);
	if (!map->prev || !map->prev->data)
		return (-1);
	if (map->prev->data[index] == ' ' || map->prev->data[index - 1] == ' '
		|| map->prev->data[index + 1] == ' '
		|| map->prev->data[index + 1] == '\0')
		return (-1);
	if (!map->next || !map->next->data)
		return (-1);
	if (map->next->data[index] == ' ' || map->next->data[index - 1] == ' '
		|| map->next->data[index + 1] == ' '
		|| map->next->data[index + 1] == '\0')
		return (-1);
	return (1);
}

static int	validate_first_row(t_map *map)
{
	int	i;

	i = 0;
	while (map->data[i])
	{
		if (is_invalid_border_char(map->data[i]))
		{
			ft_fprintf(2, "Error: Invalid border at row %d, column %d.\n",
				map->row_num, i + 1);
			return (-1);
		}
		i++;
	}
	return (1);
}

static int	validate_inner_row(t_map *map)
{
	int	i;

	i = 0;
	while (map->data[i])
	{
		if (is_invalid_border_char(map->data[i]))
		{
			if (check_surrounding(map, i) == -1)
			{
				ft_fprintf(2, "Error: Invalid border at row %d, column %d.\n",
					map->row_num, i + 1);
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

int	valid_border(t_map *map)
{
	if (!map || !map->data)
		return (-1);
	while (map)
	{
		if (map->row_num == 1)
		{
			if (validate_first_row(map) == -1)
				return (-1);
		}
		else
		{
			if (validate_inner_row(map) == -1)
				return (-1);
		}
		map = map->next;
	}
	return (1);
}

int	border_map(char *line)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(line);
	i = 1;
	while (i < len - 1)
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
