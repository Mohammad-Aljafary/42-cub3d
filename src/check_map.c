/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:12:31 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/12 17:12:32 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	set_player_pos(int *player_count, t_map *map, int i, t_cub3d *cub3d)
{
	(*player_count)++;
	cub3d->player_y = map->row_num + .5;
	cub3d->player_x = i + .5;
	if (map->data[i] == 'N')
		cub3d->player_angle = (PI / 2);
	else if (map->data[i] == 'S')
		cub3d->player_angle = 3 * (PI / 2);
	else if (map->data[i] == 'E')
		cub3d->player_angle = 0;
	else if (map->data[i] == 'W')
		cub3d->player_angle = PI;
}

int	check_player(t_map *map, t_cub3d *cub3d)
{
	int	player_count;
	int	i;

	player_count = 0;
	while (map)
	{
		i = 0;
		while (map->data[i])
		{
			if (map->data[i] == 'N' || map->data[i] == 'S'
				|| map->data[i] == 'E' || map->data[i] == 'W')
				set_player_pos(&player_count, map, i, cub3d);
			i++;
		}
		map = map->next;
	}
	if (player_count != 1)
	{
		ft_fprintf(2, "Error: Invalid player count in map.\n");
		return (-1);
	}
	return (1);
}

int	check_invalid_characters(t_map *map)
{
	int	j;

	while (map)
	{
		j = 0;
		while (map->data[j])
		{
			if (map->data[j] != '1' && map->data[j] != '0'
				&& map->data[j] != ' ' && map->data[j] != 'N'
				&& map->data[j] != 'S' && map->data[j] != 'E'
				&& map->data[j] != 'W')
			{
				ft_fprintf(2, "Error: Invalid character '%c' in map at row%d.\n", map->data[j], map->row_num);
				return (-1);
			}
			j++;
		}
		map = map->next;
	}
	return (1);
}

int	check_map(t_cub3d *cub3d)
{
	t_map	*temp;

	if (!cub3d || !cub3d->map)
	{
		ft_fprintf(2, "Error: Map is not initialized.\n");
		return (-1);
	}
	temp = cub3d->map;
	if (check_player(temp, cub3d) == -1)
		return (-1);
	if (check_invalid_characters(temp) == -1)
		return (-1);
	fill_spaces(temp);
	if (valid_border(temp) == -1)
		return (-1);
	cub3d->map_height = 600;
	cub3d->map_width = 800;
	return (1);
}
