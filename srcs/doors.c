/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 19:25:30 by ohelly            #+#    #+#             */
/*   Updated: 2019/08/18 17:38:25 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int			v_doors(t_rcast *rcast, t_temp *temp)
{
	if (rcast->cur_angle > 90 && rcast->cur_angle < 270)
	{
		temp->bx = ((rcast->map->x / 64) * 64 - 1);
		temp->xa = -64;
	}
	else
	{
		temp->bx = ((rcast->map->x / 64) * 64 + 64);
		temp->xa = 64;
	}
	temp->by = (rcast->map->y + (rcast->map->x - temp->bx) *
	tan(rcast->cur_angle * DEGREE));
	temp->ya = (temp->xa * tan(rcast->cur_angle * DEGREE));
	temp->bx += temp->xa / 1.5;
	temp->by += temp->ya / 1.5;
	if (temp->bx < 0 || temp->by < 0 || temp->by / 64 > rcast->map->c_i - 1 ||
	temp->bx / 64 > rcast->map->c_j - 1)
		return (0);
	if ((rcast->map->data[temp->by / 64][temp->bx / 64] == 7) &&
		(rcast->map->data[temp->by / 64][temp->bx / 64] = 6) &&
		(temp->t = 1))
		;
	if (rcast->map->data[temp->by / 64][temp->bx / 64] == 6 && temp->t == 0)
		rcast->map->data[temp->by / 64][temp->bx / 64] = 7;
	return (0);
}

static int			h_doors(t_rcast *rcast, t_temp *temp)
{
	if (rcast->map->angle > 0 && rcast->map->angle < 180)
	{
		temp->by = ((rcast->map->y / 64) * 64 - 1);
		temp->ya = -64;
	}
	if (rcast->map->angle > 180 && rcast->map->angle < 360)
	{
		temp->by = ((rcast->map->y / 64) * 64 + 64);
		temp->ya = 64;
	}
	temp->bx = (rcast->map->x + (rcast->map->y - temp->by) /
	tan(rcast->cur_angle * DEGREE));
	temp->xa = (temp->ya / tan(rcast->cur_angle * DEGREE));
	temp->bx += temp->xa / 1.5;
	temp->by += temp->ya / 1.5;
	if (temp->bx < 0 || temp->by < 0 || temp->by / 64 > rcast->map->c_i - 1 ||
	temp->bx / 64 > rcast->map->c_j - 1)
		return (0);
	if ((rcast->map->data[temp->by / 64][temp->bx / 64] == 7) &&
		(rcast->map->data[temp->by / 64][temp->bx / 64] = 6) &&
		(temp->t = 1))
		;
	if (rcast->map->data[temp->by / 64][temp->bx / 64] == 6 && temp->t == 0)
		rcast->map->data[temp->by / 64][temp->bx / 64] = 7;
	return (0);
}

void				doors(t_rcast *rcast, t_temp *temp)
{
	*temp = (t_temp){ 0, 0, 0, 0, 0 };
	h_doors(rcast, temp);
	*temp = (t_temp){ 0, 0, 0, 0, 0 };
	v_doors(rcast, temp);
}
