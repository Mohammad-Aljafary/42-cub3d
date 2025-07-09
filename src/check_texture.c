# include <cub3D.h>

int check_dir_text(char **tokens, t_cub3d *cub3d)
{
    t_texture *new_texture;

    new_texture = NULL;
     if (ft_strcmp(tokens[0], "NO") == 0 || ft_strcmp(tokens[0], "SO") == 0 ||
        ft_strcmp(tokens[0], "WE") == 0 || ft_strcmp(tokens[0], "EA") == 0)
    {
        if (tokens[1] && tokens[2] == NULL)
        {
            new_texture = create_node_texture(tokens[0], tokens[1], -1, -1, -1);
            if (!new_texture)
                return (-1);
            new_texture->next = cub3d->textures;
            cub3d->textures = new_texture;
        }
        else
            return (-1);
        return (1);
    }
    return (0);
}

int check_color(char **token, t_cub3d *cub3d)
{
    int red;
    int green;
    int blue;
    t_texture   *new_texture;
    char    **colors;

    colors = NULL;
    if (ft_strcmp(token[0], "F") == 0 || ft_strcmp(token[0], "C") == 0)
    {
        colors = ft_split(token[1], ',');
        if (!colors)
            return (-1);
        if (colors[0] && colors[1] && colors[2] && !colors[3])
        {
            red = ft_atoi(colors[0]);
            green = ft_atoi(colors[1]);
            blue = ft_atoi(colors[2]);
            ft_free_split(colors);
            if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
                return (-1);
            new_texture = create_node_texture(token[0], token[1], red, green, blue);
            if (!new_texture)
                return (-1);
            add_node_texture(&cub3d->textures, new_texture);
        }
        else
            return (-1);
        return (1);
    }
    return (0);
}

int is_all_text_exist(t_cub3d *cub3d)
{
    int no_count;
    int so_count;
    int we_count;
    int ea_count;
    int color_count;
    t_texture *temp;

    no_count = 0;
    so_count = 0;
    we_count = 0;
    ea_count = 0;
    color_count = 0;
    temp = cub3d->textures;
    while (temp)
    {
        if (ft_strcmp(temp->name, "NO") == 0)
            no_count++;
        else if (ft_strcmp(temp->name, "SO") == 0)
            so_count++;
        else if (ft_strcmp(temp->name, "WE") == 0)
            we_count++;
        else if (ft_strcmp(temp->name, "EA") == 0)
            ea_count++;
        else if (ft_strcmp(temp->name, "F") == 0 
                || ft_strcmp(temp->name, "C") == 0)
            color_count++;
        temp = temp->next;
    }
    if (no_count != 1 || so_count != 1 || we_count != 1 || ea_count != 1 || color_count < 2)
    {
        ft_fprintf(2, "Error: Missing or duplicate texture definitions.\n");
        return (-1);
    }
    return (1);
}

int open_textures(t_cub3d *cub3d)
{
    t_texture *temp;
    int fd;

    temp = cub3d->textures;
    fd = 0;
    while (temp)
    {
        if (temp->path)
        {
            if (ft_strcmp(temp->name, "F") == 0 || ft_strcmp(temp->name, "C") == 0)
            {
                temp = temp->next;
                continue;
            }
            fd = open(temp->path, O_RDONLY);
            if (fd < 0)
            {
                ft_fprintf(2, "Error: Could not open texture file: %s\n", temp->path);
                return (-1);
            }
            close(fd);
        }
        temp = temp->next;
    }
    return (0);
}
