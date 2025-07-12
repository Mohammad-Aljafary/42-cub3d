# include <cub3D.h>

t_map *new_map_node (char *line, int row_num)
{
    t_map *new_node;

    new_node = malloc(sizeof(t_map));
    if (!new_node)
        return (NULL);
    new_node->data = line;
    new_node->row_num = row_num;
    new_node->next = NULL;
    new_node->prev = NULL;
    return (new_node);
}

void add_node_map(t_map **head, t_map *new_node)
{
    t_map *current;

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

void free_map(t_map *head)
{
    t_map *temp;

    while (head)
    {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

t_texture *create_node_texture(char *name, char *path, char **tokens, int red, int green, int blue)
{
    t_texture *new_node;

    new_node = malloc(sizeof(t_texture));
    if (!new_node)
        return (NULL);
    new_node->name = name;
    new_node->path = path;
    new_node->tokens = tokens;
    new_node->red = red;
    new_node->green = green;
    new_node->blue = blue;
    new_node->next = NULL;
    return (new_node);
}

void add_node_texture(t_texture **head, t_texture *new_node)
{
    t_texture *current;

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

void free_textures(t_texture *head)
{
    t_texture *temp;

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


t_texture *get_name_texture(t_texture *texture, char *name)
{
    t_texture *current;

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

void free_cub3d(t_cub3d *cub3d)
{
    if (!cub3d)
        return;
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
