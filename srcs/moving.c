/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:40:47 by ohelly            #+#    #+#             */
/*   Updated: 2019/08/18 18:34:36 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int			go_back_part_two(t_rcast *rcast, t_mov *mov, int **data)
{
	int		w;

	if ((mov->p_x + mov->j) < 0 || (mov->p_y + mov->i) < 0 ||
	(mov->p_y + mov->i) / 64 > rcast->map->c_i - 1 ||
	(mov->p_x + mov->j) / 64 > rcast->map->c_j - 1)
		return (0);
	w = data[(mov->p_y + mov->i) / 64][(mov->p_x + mov->j) / 64];
	if ((w >= 1 && w <= 4) || w == 7)
	{
		mov->p_x = 0;
		mov->p_y = 0;
	}
	else
	{
		rcast->map->x = mov->p_x;
		rcast->map->y = mov->p_y;
	}
	return (0);
}

static int			go_back(t_rcast *rcast, t_mov *mov)
{
	mov->p_x = rcast->map->x;
	mov->p_y = rcast->map->y;
	if (rcast->map->angle >= 0 && rcast->map->angle < 180)
	{
		mov->p_x = 1 + mov->p_x - cos(rcast->map->angle * (1 / 57.2958)) * 15;
		mov->i = 16;
	}
	else
	{
		mov->p_x = mov->p_x - cos(rcast->map->angle * (1 / 57.2958)) * 15;
		mov->i = -16;
	}
	if (rcast->map->angle >= 90 && rcast->map->angle < 270)
	{
		mov->p_y = mov->p_y + sin(rcast->map->angle * (1 / 57.2958)) * 15;
		mov->j = 16;
	}
	else
	{
		mov->p_y = 1 + mov->p_y + sin(rcast->map->angle * (1 / 57.2958)) * 15;
		mov->j = -16;
	}
	go_back_part_two(rcast, mov, rcast->map->data);
	return (0);
}

static int			go_forward_part_two(t_rcast *rcast, t_mov *mov, int **data)
{
	int		w;

	if ((mov->p_x + mov->j) < 0 || (mov->p_y + mov->i) < 0 ||
	(mov->p_y + mov->i) / 64 > rcast->map->c_i - 1 ||
	(mov->p_x + mov->j) / 64 > rcast->map->c_j - 1)
		return (0);
	w = data[(mov->p_y + mov->i) / 64][(mov->p_x + mov->j) / 64];
	if ((w >= 1 && w <= 4) || w == 7)
	{
		mov->p_x = 0;
		mov->p_y = 0;
	}
	else
	{
		rcast->map->x = mov->p_x;
		rcast->map->y = mov->p_y;
	}
	return (0);
}

static int			go_forward(t_rcast *rcast, t_mov *mov)
{
	mov->p_x = rcast->map->x;
	mov->p_y = rcast->map->y;
	if (rcast->map->angle > 0 && rcast->map->angle < 180)
	{
		mov->p_x = mov->p_x + cos(rcast->map->angle * (1 / 57.2958)) * 15;
		mov->i = -16;
	}
	else
	{
		mov->p_x = 1 + mov->p_x + cos(rcast->map->angle * (1 / 57.2958)) * 15;
		mov->i = 16;
	}
	if (rcast->map->angle > 90 && rcast->map->angle < 270)
	{
		mov->p_y = 1 + mov->p_y - sin(rcast->map->angle * (1 / 57.2958)) * 15;
		mov->j = -16;
	}
	else
	{
		mov->p_y = mov->p_y - sin(rcast->map->angle * (1 / 57.2958)) * 15;
		mov->j = 16;
	}
	go_forward_part_two(rcast, mov, rcast->map->data);
	return (0);
}

void				moving(t_rcast *rcast, t_mov *mov, int key)
{
	*mov = (t_mov){ 0, 0, 0, 0 };
	if (key == 13)
		go_forward(rcast, mov);
	if (key == 1)
		go_back(rcast, mov);
}
