/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:19:46 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/17 23:25:45 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			solve(t_rcast *rcast, int **side, int wall)
{
	if (wall == 1)
	{
		rcast->len[rcast->n] = rcast->h_len[rcast->n];
		rcast->texture->offset[rcast->n] = rcast->texture->h_offset;
		rcast->door = rcast->h_door;
		rcast->wall = rcast->w_h;
		**side = wall;
	}
	else if (wall == 0)
	{
		rcast->len[rcast->n] = rcast->v_len[rcast->n];
		rcast->texture->offset[rcast->n] = rcast->texture->v_offset;
		rcast->door = rcast->v_door;
		rcast->wall = rcast->w_v;
		**side = wall;
	}
	else
	{
		rcast->side[rcast->n] = 16;
		rcast->v_door = 0;
		rcast->h_door = 0;
		rcast->wall = 0;
	}
	return (0);
}

int			take_len(t_rcast *rcast, t_texture *texture, int *side)
{
	if (rcast->v_len[rcast->n] < rcast->h_len[rcast->n])
		rcast->cur_angle == 270 ?
		solve(rcast, &side, 1) : solve(rcast, &side, 0);
	else if (rcast->v_len[rcast->n] > rcast->h_len[rcast->n])
		(rcast->cur_angle == 0) ?
		solve(rcast, &side, 0) : solve(rcast, &side, 1);
	else
	{
		rcast->len[rcast->n] = rcast->h_len[rcast->n];
		if (rcast->cur_angle > 90 && rcast->cur_angle < 270)
		{
			texture->offset[rcast->n] = texture->v_offset;
			rcast->wall = rcast->w_v;
		}
		else
		{
			texture->offset[rcast->n] = texture->h_offset;
			rcast->wall = rcast->w_h;
		}
	}
	return (0);
}

int			change_texture(t_rcast *rcast, int wall, int t)
{
	if (rcast->door != 1)
	{
		if (wall == 0 && rcast->cur_angle >= 0 && rcast->cur_angle < 90)
			rcast->side[rcast->n] = 0 + t;
		else if (wall == 1 && rcast->cur_angle > 0 && rcast->cur_angle < 90)
			rcast->side[rcast->n] = 1 + t;
		else if (wall == 1 && rcast->cur_angle >= 90 && rcast->cur_angle < 180)
			rcast->side[rcast->n] = 1 + t;
		else if (wall == 0 && rcast->cur_angle > 90 && rcast->cur_angle < 180)
			rcast->side[rcast->n] = 2 + t;
		else if (wall == 0 && rcast->cur_angle >= 180 && rcast->cur_angle < 270)
			rcast->side[rcast->n] = 2 + t;
		else if (wall == 1 && rcast->cur_angle > 180 && rcast->cur_angle < 270)
			rcast->side[rcast->n] = 3 + t;
		else if (wall == 1 && rcast->cur_angle >= 270 && rcast->cur_angle < 360)
			rcast->side[rcast->n] = 3 + t;
		else if (wall == 0 && rcast->cur_angle > 270 && rcast->cur_angle < 360)
			rcast->side[rcast->n] = 0 + t;
		else
			rcast->side[rcast->n] = 0 + t;
	}
	else
		solve(rcast, 0, 2);
	return (0);
}

int			cast_a_ray(t_rcast *rcast)
{
	double	angle;
	double	tmp;
	int		wall;
	int		t;

	tmp = (double)rcast->fov / (double)P_WIDTH;
	rcast->cur_angle = rcast->map->angle + rcast->fov / 2;
	rcast->n = 0;
	while (rcast->n < P_WIDTH)
	{
		if ((int)rcast->cur_angle < 0)
			rcast->cur_angle += 360;
		if ((int)rcast->cur_angle >= 360)
			rcast->cur_angle -= 360;
		find_walls(rcast);
		take_len(rcast, rcast->texture, &wall);
		t = abs(rcast->wall - 1) * 4;
		change_texture(rcast, wall, t);
		angle = rcast->map->angle - rcast->cur_angle;
		rcast->len[rcast->n] = rcast->len[rcast->n] * cos(angle * DEGREE);
		rcast->cur_angle -= tmp;
		rcast->n++;
	}
	return (0);
}

int			raycast(t_params *content)
{
	cast_a_ray(content->rcast);
	put_walls(content->rcast, content->rcast->texture, content->mlx);
	return (0);
}
