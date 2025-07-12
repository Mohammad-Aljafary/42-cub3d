/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:10:03 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/12 17:10:04 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	print_texture(t_cub3d *cub3d, t_texture *texture, t_dda *dda,
		double wall_x)
{
	t_tex_help	tex;

	tex.tex_x = (int)(wall_x * (double)texture->xpm->texture.width);
	if (dda->side == 0 && dda->ray_dir_x > 0)
		tex.tex_x = texture->xpm->texture.width - tex.tex_x - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		tex.tex_x = texture->xpm->texture.width - tex.tex_x - 1;
	tex.step = 1.0 * texture->xpm->texture.height / dda->line_height;
	tex.tex_pos = (dda->draw_start - cub3d->map_height / 2 + dda->line_height
			/ 2) * tex.step;
	tex.tex_x = (int)(texture->xpm->texture.width * (wall_x));
	tex.y = dda->draw_start - 1;
	while (++tex.y < dda->draw_end)
	{
		tex.tex_y = (int)tex.tex_pos & (texture->xpm->texture.height - 1);
		tex.tex_pos += tex.step;
		tex.pixel = &texture->xpm->texture.pixels[(tex.tex_y
				* texture->xpm->texture.width + tex.tex_x) * 4];
		tex.color = (tex.pixel[0] << 24) | (tex.pixel[1] << 16) | (tex.pixel[2] << 8) | tex.pixel[3];
		mlx_put_pixel(cub3d->img, dda->x, tex.y, tex.color);
	}
}

void	print_floor_and_ceiling(t_cub3d *cub3d, t_dda *dda)
{
	t_texture		*floor_texture;
	t_texture		*ceiling_texture;
	int				y;
	unsigned int	color_c;
	unsigned int	color_f;

	floor_texture = get_name_texture(cub3d->textures, "F");
	ceiling_texture = get_name_texture(cub3d->textures, "C");
	color_c = (ceiling_texture->red << 24) | (ceiling_texture->green << 16) | (ceiling_texture->blue << 8) | 0xFF;
	color_f = (floor_texture->red << 24) | (floor_texture->green << 16) | (floor_texture->blue << 8) | 0xFF;
	y = -1;
	while (++y < cub3d->map_height)
	{
		if (y < dda->draw_start)
			mlx_put_pixel(cub3d->img, dda->x, y, color_c);
		else if (y >= dda->draw_end)
			mlx_put_pixel(cub3d->img, dda->x, y, color_f);
	}
}

void	start_drawing(t_cub3d *cub3d, t_dda *dda)
{
	double		wall_x;
	t_texture	*texture;

	if (dda->side == 0)
		wall_x = cub3d->player_y + dda->perp_wall_dist * dda->ray_dir_y;
	else
		wall_x = cub3d->player_x + dda->perp_wall_dist * dda->ray_dir_x;
	wall_x -= floor(wall_x);
	if (dda->side == 0)
	{
		if (dda->ray_dir_x < 0)
			texture = get_name_texture(cub3d->textures, "WE");
		else
			texture = get_name_texture(cub3d->textures, "EA");
	}
	else
	{
		if (dda->ray_dir_y < 0)
			texture = get_name_texture(cub3d->textures, "NO");
		else
			texture = get_name_texture(cub3d->textures, "SO");
	}
	print_texture(cub3d, texture, dda, wall_x);
	print_floor_and_ceiling(cub3d, dda);
}
