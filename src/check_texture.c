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
    
}