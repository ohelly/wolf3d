/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:26:19 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/17 23:05:02 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			take_texture(t_mlx *mlx, t_rcast *rcast, int j, int i)
{
	int	t;

	t = rcast->side[rcast->n];
	mlx->data[i * 4 * W_WIDTH + 4 * rcast->texture->x + 0] =
	rcast->texture->data_walls[t][j * 4 * 64 + 4 *
	rcast->texture->offset[rcast->n] + 0];
	mlx->data[i * 4 * W_WIDTH + 4 * rcast->texture->x + 1] =
	rcast->texture->data_walls[t][j * 4 * 64 + 4 *
	rcast->texture->offset[rcast->n] + 1];
	mlx->data[i * 4 * W_WIDTH + 4 * rcast->texture->x + 2] =
	rcast->texture->data_walls[t][j * 4 * 64 + 4 *
	rcast->texture->offset[rcast->n] + 2];
	mlx->data[i * 4 * W_WIDTH + 4 * rcast->texture->x + 3] =
	rcast->texture->data_walls[t][j * 4 * 64 + 4 *
	rcast->texture->offset[rcast->n] + 3];
	return (0);
}

int			put_texture_col(t_rcast *rcast, t_texture *texture, t_mlx *mlx)
{
	float	i;
	int		j;
	int		len;
	float	size;
	float	t;

	i = texture->y;
	j = 0;
	len = rcast->texture->colheight;
	size = (float)len / 64;
	while (i < len + rcast->texture->toppoint)
	{
		t = i + size;
		while (i < t)
		{
			t = -1;
			while (++t < size)
				if (t + i >= 0 && t + i < P_HEIGHT)
					take_texture(mlx, rcast, j, (int)(t + i));
			i += size;
			j++;
		}
	}
	return (0);
}

int			put_walls(t_rcast *rcast, t_texture *texture, t_mlx *mlx)
{
	rcast->n = 0;
	while (rcast->n < P_WIDTH)
	{
		texture->colheight = 64 / (rcast->len[rcast->n]) * rcast->p_length;
		texture->toppoint = P_HEIGHT / 2 - texture->colheight / 2;
		if (texture->colheight % 2 != 0)
			texture->colheight -= 1;
		texture->x = rcast->n;
		texture->y = texture->toppoint;
		put_texture_col(rcast, rcast->texture, mlx);
		rcast->n++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	return (0);
}
