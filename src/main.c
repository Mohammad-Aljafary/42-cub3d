/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:10:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/12 17:10:29 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/cub3D.h>

int	valid_file(int argc, char **argv, t_cub3d *cub3d)
{
	int	fd;

	if (argc != 2)
	{
		ft_fprintf(2, "Usage: %s <map_file>\n", argv[0]);
		return (-1);
	}
	if (check_extension(argv[1], ".cub") == -1)
	{
		ft_fprintf(2, "Error: Invalid file extension. Expected .cub file.\n");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	if (read_file(fd, cub3d) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	init_cub(t_cub3d *cub3d)
{
	mlx_image_t	*img;

	cub3d->dir_x = cos(cub3d->player_angle);
	cub3d->dir_y = sin(cub3d->player_angle);
	cub3d->plane_x = -cub3d->dir_y * 0.66f;
	cub3d->plane_y = cub3d->dir_x * 0.66f;
	cub3d->mlx = mlx_init(cub3d->map_width, cub3d->map_height, "cub3D", true);
	if (!cub3d->mlx)
		return ;
	img = mlx_new_image(cub3d->mlx, cub3d->map_width, cub3d->map_height);
	if (!img)
	{
		printf("Failed to create image\n");
		return ;
	}
	cub3d->img = img;
	if (mlx_image_to_window(cub3d->mlx, img, 0, 0) == -1)
	{
		printf("Failed to put image to window\n");
		return ;
	}
	mlx_loop_hook(cub3d->mlx, key_hook, cub3d);
	mlx_loop_hook(cub3d->mlx, render_loop, cub3d);
	mlx_loop(cub3d->mlx);
	free_cub3d(cub3d);
}

void	load_mlx(t_cub3d *cub3d)
{
	init_cub(cub3d);
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	if (valid_file(argc, argv, cub3d) == -1)
	{
		free_cub3d(cub3d);
		return (EXIT_FAILURE);
	}
	load_mlx(cub3d);
	free_cub3d(cub3d);
}
/*
int	main(void)
{
	t_cub3d *cub3d;
	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
	{
		printf("Failed to allocate memory for cub3d\n");
		return (1);
	}
	// printf("Memory allocated for cub3d\n");
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->map_width = 800;
	cub3d->map_height = 600;
	cub3d->player_x = 4.5f;
	cub3d->player_y = 4.5f;
	cub3d->player_angle = 0.0f;
	cub3d->dir_x = cos(cub3d->player_angle);
	cub3d->dir_y = sin(cub3d->player_angle);
	cub3d->plane_x = -cub3d->dir_y * 0.66f;
	cub3d->plane_y = cub3d->dir_x * 0.66f;
	cub3d->mlx = mlx_init(cub3d->map_width, cub3d->map_height, "cub3D", true);
	if (!cub3d->mlx)
	{
		printf("Failed to initialize MLX\n");
		free(cub3d);
		return (1);
	}
	cub3d->textures = NULL;
	cub3d->textures = create_node_texture("NO", "wall/wall_1.xpm42", 0, 0, 0);
	cub3d->textures->xpm = mlx_load_xpm42(cub3d->textures->path);
	cub3d->textures->next = create_node_texture("SO", "wall/wall_3.xpm42", 0, 0,
			0);
	cub3d->textures->next->xpm = mlx_load_xpm42(cub3d->textures->next->path);
	cub3d->textures->next->next = create_node_texture("WE", "wall/wall_4.xpm42",
			0, 0, 0);
	cub3d->textures->next->next->xpm = mlx_load_xpm42(cub3d->textures->next->next->path);
	cub3d->textures->next->next->next = create_node_texture("EA",
			"wall/wood.xpm42", 0, 0, 0);
	cub3d->textures->next->next->next->xpm = mlx_load_xpm42(cub3d->textures->next->next->next->path);
	cub3d->textures->next->next->next->next = create_node_texture("F", NULL,
			100, 100, 100);
	cub3d->textures->next->next->next->next->next = create_node_texture("C",
			NULL, 190, 189, 200);
	cub3d->map = NULL;
	add_node_map(&cub3d->map, create_node_map("1111111111", 0));
	add_node_map(&cub3d->map, create_node_map("10000000011111111111111111", 1));
	add_node_map(&cub3d->map, create_node_map("10000011000000000000000001", 2));
	add_node_map(&cub3d->map, create_node_map("10000000000000000000000001", 3));
	add_node_map(&cub3d->map, create_node_map("10000011000000000000000001", 4));
	add_node_map(&cub3d->map, create_node_map("10000000000000000000000001", 5));
	add_node_map(&cub3d->map, create_node_map("11111111111111111111111111", 6));

	main_1(cub3d);

	// free_map(cub3d->map);
	// free_textures(cub3d->textures);
	// free(cub3d); i will free it when finsh all the project
	return (0);
}*/
