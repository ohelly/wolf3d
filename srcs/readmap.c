/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:25:51 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/18 18:54:56 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		check_pos_start_and_door(t_map *map)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (map->pos_x == 0 || map->pos_x == map->c_j - 1 ||
	map->pos_y == 0 || map->pos_y == map->c_i - 1)
		return (0);
	map->x = map->pos_x * 64 + 32;
	map->y = map->pos_y * 64 + 32;
	while (++i < map->c_i)
	{
		j = -1;
		while (++j < map->c_j)
			if (((i == 0 || i == map->c_i - 1) && map->data[i][j] == 7) ||
			((j == 0 || j == map->c_j - 1) && map->data[i][j] == 7))
				return (0);
	}
	close(map->fd);
	return (1);
}

static int		check_surface(t_map *map, t_rcast *rcast)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	j = -1;
	count = 0;
	if (!(check_pos_start_and_door(rcast->map)))
		return (0);
	while (++i < map->c_i)
	{
		while (++j < map->c_j)
		{
			if (((i == 0 || i == map->c_i - 1) && map->data[i][j] == 0) ||
			((j == 0 || j == map->c_j - 1) && map->data[i][j] == 0))
				return (0);
			if (map->data[i][j] == 5)
				count++;
		}
		j = -1;
	}
	if (count != 1)
		return (0);
	return (1);
}

static int		input_to_pointer(t_map *map, char *line, int x)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(map->data[x] = (int*)ft_memalloc(sizeof(int) * map->c_j)))
		return (0);
	while (++i < (int)ft_strlen(line))
	{
		if ((line[i] >= '0' && line[i] <= '5') || line[i] == '7')
		{
			if (line[i] == '5')
			{
				map->pos_x = j + 1;
				map->pos_y = x;
			}
			if (line[i] == '0')
				map->data[x][++j] = 0;
			else
				map->data[x][++j] = ft_atoi(&line[i]);
			while (ft_isdigit(line[i]))
				i++;
		}
	}
	return (1);
}

static int		check_line(char *line, t_map *map)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i <= (int)ft_strlen(line))
	{
		if (line[i] >= '0' && line[i] <= '7')
		{
			if (line[i + 1] != ' ' && line[i + 1] != '\0')
				return (0);
			while (ft_isdigit(line[i]))
				i++;
			count++;
		}
		else if (line[i] != ' ' && line[i] != '\0')
			return (0);
	}
	if (!(map->c_j))
		map->c_j = count;
	else if (map->c_j != count)
		return (0);
	map->c_i++;
	free(line);
	return (1);
}

int				readmap(t_rcast *rcast)
{
	char	*line;
	int		i;

	i = 0;
	if ((rcast->map->fd = open("maps/map", O_RDONLY)) == -1)
		return (0);
	while (get_next_line(rcast->map->fd, &line))
		if (!(check_line(line, rcast->map)))
			return (0);
	if (rcast->map->c_i < 3)
		return (0);
	close(rcast->map->fd);
	if (((rcast->map->fd = open("maps/map", O_RDONLY)) == -1) ||
	!(rcast->map->data = (int**)ft_memalloc(sizeof(int*) * (rcast->map->c_i))))
		return (0);
	while (get_next_line(rcast->map->fd, &line))
	{
		if (!(input_to_pointer(rcast->map, line, i++)))
			return (0);
		free(line);
	}
	if (!(check_surface(rcast->map, rcast)))
		return (0);
	return (1);
}
