/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:09:59 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/12 17:10:00 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_fprintf(2, "Error: RGB number should be between 0-255\n");
		return (-1);
	}
	return (0);
}

static int	check_rgb_format(char **colors)
{
	if (colors[0] && colors[1] && colors[2] && colors[3])
	{
		ft_fprintf(2, "Error: the RGB number should be 3 numbers\n");
		ft_free_split(colors);
		return (-1);
	}
	return (0);
}

static int	parse_color_values(char **colors, int *r, int *g, int *b)
{
	*r = ft_atoi(colors[0]);
	*g = ft_atoi(colors[1]);
	*b = ft_atoi(colors[2]);
	if (validate_rgb_values(*r, *g, *b) == -1)
		return (-1);
	return (0);
}

static int	create_and_add_texture(char **token, t_cub3d *cub3d, int r, int g,
		int b)
{
	t_texture	*new_texture;

	new_texture = create_node_texture(token[0], token[1], token, r, g, b);
	if (!new_texture)
	{
		ft_fprintf(2, "Error: malloc failed\n");
		return (-1);
	}
	add_node_texture(&cub3d->textures, new_texture);
	return (1);
}

int	check_color(char **token, t_cub3d *cub3d)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	if (ft_strcmp(token[0], "F") != 0 && ft_strcmp(token[0], "C") != 0)
		return (0);
	colors = ft_split(token[1], ',');
	if (!colors)
		return (-1);
	if (check_rgb_format(colors) == -1)
		return (-1);
	if (parse_color_values(colors, &r, &g, &b) == -1)
	{
		ft_free_split(colors);
		return (-1);
	}
	ft_free_split(colors);
	if (create_and_add_texture(token, cub3d, r, g, b) == -1)
		return (-1);
	return (1);
}
