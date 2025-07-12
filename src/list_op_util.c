/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_op_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:10:17 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/12 17:10:18 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	free_map(t_map *head)
{
	t_map	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->data);
		free(temp);
	}
}

void	free_textures(t_texture *head)
{
	t_texture	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp->path);
		free(temp->tokens);
		if (temp->xpm)
			mlx_delete_xpm42(temp->xpm);
		free(temp);
	}
}

void	free_cub3d(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->textures)
	{
		free_textures(cub3d->textures);
		cub3d->textures = NULL;
	}
	if (cub3d->map)
	{
		free_map(cub3d->map);
		cub3d->map = NULL;
	}
	if (cub3d->mlx)
	{
		if (cub3d->img)
		{
			mlx_delete_image(cub3d->mlx, cub3d->img);
			cub3d->img = NULL;
		}
		mlx_terminate(cub3d->mlx);
		cub3d->mlx = NULL;
	}
	free(cub3d);
}
