# include <cub3D.h>

int check_player(t_map *map, t_cub3d *cub3d)
{
    int player_count;
    int i;

    player_count = 0;
    while (map)
    {
        i = 0;
        while (map->data[i])
        {
            if (map->data[i] == 'N' || map->data[i] == 'S' ||
                map->data[i] == 'E' || map->data[i] == 'W')
            {
                player_count++;
                cub3d->player_x = map->row_num;
                cub3d->player_y = i;
                if (map->data[i] == 'N')
                    cub3d->player_angle = (PI / 2);
                else if (map->data[i] == 'S')
                    cub3d->player_angle = 3 * (PI / 2);
                else if (map->data[i] == 'E')
                    cub3d->player_angle = 0;
                else if (map->data[i] == 'W')
                    cub3d->player_angle = PI;
            }
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

int check_invalid_characters(t_map *map)
{
    int j;

    while (map)
    {
        j = 0;
        while (map->data[j])
        {
            if (map->data[j] != '1' && map->data[j] != '0' &&
                map->data[j] != ' ' && map->data[j] != 'N' &&
                map->data[j] != 'S' && map->data[j] != 'E' &&
                map->data[j] != 'W')
            {
                ft_fprintf(2, "Error: Invalid character '%c' in map at row %d.\n", 
                           map->data[j], map->row_num);
                return (-1);
            }
            j++;
        }
        map = map->next;
    }
    return (1);
}

int element_exist(char *line, int index)
{
    if (index < 0 || index >= (int)ft_strlen(line))
        return (0);
    while (index >= 0)
    {
        if (line[index] == '1' || line[index] == 'N' || 
            line[index] == 'S' || line[index] == 'E' || 
            line[index] == 'W')
            return (1);
        index--;
    }
    return (0);
}

void fill_spaces (t_map *map)
{
    int j;

    if (!map || !map->data)
        return ;
    while (map)
    {
        j = ft_strlen(map->data) - 1;
        while (j >= 0)
        {
            if (map->data[j] == ' ')
            {
                if (element_exist(map->data, j) == 1)
                    map->data[j] = '1';
            }
            j--;
        }
        map = map->next;
    }
}

int check_surrounding(t_map *map, int index)
{
    if (!map || !map->data || index <= 0)
        return (-1);
    if (map->data[index - 1] == ' ' || map->data[index + 1] == ' ' ||
        map->data[index + 1] == '\0')
        return (-1);
    if (!map->prev || !map->prev->data)
        return (-1);
    if (map->prev->data[index] == ' ' ||
        map->prev->data[index - 1] == ' ' ||
        map->prev->data[index + 1] == ' ' ||
        map->prev->data[index + 1] == '\0')
        return (-1);
    if (!map->next || !map->next->data)
        return (-1);
    if (map->next->data[index] == ' ' ||
        map->next->data[index - 1] == ' ' ||
        map->next->data[index + 1] == ' ' ||
        map->next->data[index + 1] == '\0')
        return (-1);
    return (1);
}

int valid_border(t_map *map)
{
    int i;
    int len;

    if (!map || !map->data)
        return (-1);
    while (map)
    {
        i = 0;
        len = ft_strlen(map->data);
        if (map->row_num == 1)
        {
            while (i < len)
            {
                if (map->data[i] != '1' && map->data[i] != ' ')
                {
                    ft_fprintf(2, "Error: Invalid border at row %d, column %d.\n", 
                               map->row_num, i + 1);
                    return (-1);
                }
                i++;
            }
        }
        else 
        {
            while (i < len)
            {
                if (map->data[i] != '1' && map->data[i] != ' ')
                {
                    if (check_surrounding(map, i) == -1)
                    {
                        ft_fprintf(2, "Error: Invalid border at row %d, column %d.\n", 
                                   map->row_num, i + 1);
                        return (-1);
                    }
                }
                i++;
            }
        }
        map = map->next;
    }
    return (1);
}

int get_last_row(t_map *map)
{
    t_map *temp;

    temp = map;
    while (temp->next)
        temp = temp->next;
    return (temp->row_num);
}

int get_longest_row(t_map *map)
{
    t_map   *temp;
    int len;

    temp = map;
    len = ft_strlen(temp->data);
    while (temp)
    {
        if ((int)ft_strlen(temp->data) > len)
            len = ft_strlen(temp->data);
        temp = temp->next;
    }
    return (len);
}

void    set_height_width(t_cub3d *cub3d)
{
    cub3d->map_height = get_last_row(cub3d->map);
    cub3d->map_width = get_longest_row(cub3d->map);
}

int check_map(t_cub3d *cub3d)
{
    t_map *temp;

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
    set_height_width(cub3d);
    return (1);
}
