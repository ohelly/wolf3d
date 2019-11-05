/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:17:45 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/18 17:40:00 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			is_it_h_wall(int ax, int ay, t_rcast *rcast, t_map *map)
{
	int		w;

	w = 0;
	ax = (ax < 0) ? 0 : ax;
	ay = (ay < 0) ? 0 : ay;
	ay = (ay / 64 > map->c_i - 1) ? 64 * (map->c_i - 1) : ay;
	if (ax / 64 > map->c_j - 1)
	{
		rcast->h_len[rcast->n] =
		sqrt(pow(map->x - ax, 2) + pow(map->y - ay, 2));
		rcast->texture->h_offset = ax % 64;
		return (1);
	}
	w = map->data[ay / 64][ax / 64];
	if (w == 1 || w == 2 || w == 3 || w == 4 || w == 7)
	{
		rcast->w_h = (w != 5 && w != 7) ? w : rcast->w_h;
		rcast->h_door = (w == 7) ? 1 : 0;
		rcast->h_len[rcast->n] =
		sqrt(pow(map->x - ax, 2) + pow(map->y - ay, 2));
		rcast->texture->h_offset = ax % 64;
	}
	else
		return (0);
	return (1);
}

int			find_h_walls(t_rcast *rcast, t_map *map, int ay, int ya)
{
	int		ax;
	int		xa;
	int		t;

	while (1)
	{
		if (rcast->cur_angle > 90 && rcast->cur_angle < 270)
			t = 1;
		else
			t = 0;
		ax = (map->x + (map->y - ay) / tan(rcast->cur_angle * DEGREE)) + t;
		xa = (ya / tan(rcast->cur_angle * DEGREE));
		if (is_it_h_wall(ax, ay, rcast, map))
			break ;
		else
		{
			ax += xa;
			ay += ya;
		}
	}
	return (0);
}

int			is_it_v_wall(int bx, int by, t_rcast *rcast, t_map *map)
{
	int		w;

	w = 0;
	bx = (bx < 0) ? 0 : bx;
	by = (by < 0) ? 0 : by;
	bx = (bx / 64 > map->c_j - 1) ? 64 * (map->c_j - 1) : bx;
	if (by / 64 > map->c_i - 1)
	{
		rcast->v_len[rcast->n] =
		sqrt(pow(map->x - bx, 2) + pow(map->y - by, 2));
		rcast->texture->v_offset = by % 64;
		return (1);
	}
	w = map->data[by / 64][bx / 64];
	if (w == 1 || w == 2 || w == 3 || w == 4 || w == 7)
	{
		rcast->w_v = (w != 5 && w != 7) ? w : rcast->w_v;
		rcast->v_door = (w == 7) ? 1 : 0;
		rcast->v_len[rcast->n] =
		sqrt(pow(map->x - bx, 2) + pow(map->y - by, 2));
		rcast->texture->v_offset = by % 64;
	}
	else
		return (0);
	return (1);
}

int			find_v_walls(t_rcast *rcast, t_map *map, int bx, int xa)
{
	int		ya;
	int		by;
	int		t;

	while (1)
	{
		if (rcast->cur_angle > 0 && rcast->cur_angle < 180)
			t = 1;
		else
			t = 0;
		by = (map->y + (map->x - bx) * tan(rcast->cur_angle * DEGREE));
		ya = (xa * tan(rcast->cur_angle * DEGREE));
		if (is_it_v_wall(bx, by, rcast, map))
			break ;
		else
		{
			bx += xa;
			by += ya;
		}
	}
	return (0);
}

int			find_walls(t_rcast *rcast)
{
	int		ay;
	int		ya;
	int		bx;
	int		xa;

	ay = (rcast->cur_angle > 0 && rcast->cur_angle < 180) ?
	((rcast->map->y / 64) * 64 - 1) : ((rcast->map->y / 64) * 64 + 64);
	ya = (rcast->cur_angle > 0 && rcast->cur_angle < 180) ?
	-64 : 64;
	find_h_walls(rcast, rcast->map, ay, ya);
	bx = (rcast->cur_angle > 90 && rcast->cur_angle < 270) ?
	((rcast->map->x / 64) * 64 - 1) : ((rcast->map->x / 64) * 64 + 64);
	xa = (rcast->cur_angle > 90 && rcast->cur_angle < 270) ?
	-64 : 64;
	find_v_walls(rcast, rcast->map, bx, xa);
	return (0);
}
