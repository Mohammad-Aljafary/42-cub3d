/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:10:10 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/13 13:54:54 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_map	*new_map_node(char *line, int row_num)
{
	t_map	*new_node;

	new_node = malloc(sizeof(t_map));
	if (!new_node)
		return (NULL);
	new_node->data = line;
	new_node->row_num = row_num;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_node_map(t_map **head, t_map *new_node)
{
	t_map	*current;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
}

t_texture	*create_node_texture(char *name, char *path, char **tokens,
								t_color color)
{
	t_texture	*new_node;

	new_node = malloc(sizeof(t_texture));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->path = path;
	new_node->tokens = tokens;
	new_node->red = color.red;
	new_node->green = color.green;
	new_node->blue = color.blue;
	new_node->next = NULL;
	if (!(!ft_strcmp(name, "F") || !ft_strcmp(name, "C")))
	{
		new_node->xpm = mlx_load_xpm42(path);
		if (!new_node->xpm)
			return (NULL);
	}
	else
		new_node->xpm = NULL;
	return (new_node);
}

void	add_node_texture(t_texture **head, t_texture *new_node)
{
	t_texture	*current;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_texture	*get_name_texture(t_texture *texture, char *name)
{
	t_texture	*current;

	current = texture;
	if (!texture || !name)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
