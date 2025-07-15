/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:09:52 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/15 10:53:23 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_dir_text(char **tokens, t_cub3d *cub3d)
{
	t_texture	*new_texture;

	new_texture = NULL;
	if (ft_strcmp(tokens[0], "NO") == 0 || ft_strcmp(tokens[0], "SO") == 0
		|| ft_strcmp(tokens[0], "WE") == 0 || ft_strcmp(tokens[0], "EA") == 0)
	{
		if (tokens[1] && tokens[2])
		{
			ft_fprintf(2, "Error: multiple or no texture path\n");
			return (-1);
		}
		new_texture = create_node_texture(tokens[0], tokens[1], tokens,
				(t_color){0, 0, 0});
		if (!new_texture)
		{
			ft_fprintf(2, "Error: Invalid texture or malloc failed\n");
			return (-1);
		}
		new_texture->next = cub3d->textures;
		cub3d->textures = new_texture;
		return (1);
	}
	return (0);
}

void	check_number(t_texture *temp, t_check *check)
{
	if (ft_strcmp(temp->name, "NO") == 0)
		check->no_count++;
	else if (ft_strcmp(temp->name, "SO") == 0)
		check->so_count++;
	else if (ft_strcmp(temp->name, "WE") == 0)
		check->we_count++;
	else if (ft_strcmp(temp->name, "EA") == 0)
		check->ea_count++;
	else if (ft_strcmp(temp->name, "F") == 0 || ft_strcmp(temp->name, "C") == 0)
		check->color_count++;
}

int	is_all_text_exist(t_cub3d *cub3d)
{
	t_check		check;
	t_texture	*temp;

	ft_bzero(&check, sizeof(check));
	temp = cub3d->textures;
	while (temp)
	{
		check_number(temp, &check);
		temp = temp->next;
	}
	if (check.no_count != 1 || check.so_count != 1 || check.we_count != 1
		|| check.ea_count != 1 || check.color_count != 2)
	{
		ft_fprintf(2, "Error: Missing or duplicate texture definitions.\n");
		return (-1);
	}
	return (1);
}

int	test_open(int fd, t_texture *temp)
{
	fd = open(temp->path, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error: Could not open texture file: %s\n",
			temp->path);
		return (-1);
	}
	close(fd);
	return (0);
}

int	open_textures(t_cub3d *cub3d)
{
	t_texture	*temp;
	int			fd;

	temp = cub3d->textures;
	fd = 0;
	while (temp)
	{
		if (temp->path)
		{
			if (ft_strcmp(temp->name, "F") == 0 || ft_strcmp(temp->name,
					"C") == 0)
			{
				temp = temp->next;
				continue ;
			}
			if (test_open(fd, temp) == -1)
				return (-1);
		}
		temp = temp->next;
	}
	return (0);
}
