/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:39:37 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/17 22:18:10 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		put_in(t_mlx *mlx, char *data, t_bkg *bkg)
{
	mlx->line->r = (int)(mlx->line->r * mlx->line->intensive[bkg->y]);
	mlx->line->g = (int)(mlx->line->g * mlx->line->intensive[bkg->y]);
	mlx->line->b = (int)(mlx->line->b * mlx->line->intensive[bkg->y]);
	data[bkg->y * 4 * W_WIDTH + bkg->x * 4 + 0] = mlx->line->b;
	data[bkg->y * 4 * W_WIDTH + bkg->x * 4 + 1] = mlx->line->g;
	data[bkg->y * 4 * W_WIDTH + bkg->x * 4 + 2] = mlx->line->r;
	data[bkg->y * 4 * W_WIDTH + bkg->x * 4 + 3] = 0;
	mlx->line->r = bkg->tmp_r;
	mlx->line->g = bkg->tmp_g;
	mlx->line->b = bkg->tmp_b;
}

void		softline(t_mlx *mlx, char *data, t_bkg *bkg)
{
	bkg->y = mlx->line->y0;
	bkg->x = mlx->line->x0;
	bkg->tmp_r = mlx->line->r;
	bkg->tmp_g = mlx->line->g;
	bkg->tmp_b = mlx->line->b;
	while (bkg->y < mlx->line->y1 || bkg->x < mlx->line->x1)
	{
		if (bkg->y < P_HEIGHT - 1 && bkg->y >= 0)
			put_in(mlx, data, bkg);
		bkg->y++;
	}
	if (bkg->y < P_HEIGHT - 1 && bkg->y >= 0)
	{
		data[bkg->y * 4 * W_WIDTH + bkg->x * 4 + 0] = mlx->line->b;
		data[bkg->y * 4 * W_WIDTH + bkg->x * 4 + 1] = mlx->line->g;
		data[bkg->y * 4 * W_WIDTH + bkg->x * 4 + 2] = mlx->line->r;
		data[bkg->y * 4 * W_WIDTH + bkg->x * 4 + 3] = 0;
	}
}

int			background(t_mlx *mlx, t_bkg *bkg)
{
	int				i;

	i = -1;
	while (++i < P_WIDTH)
	{
		mlx->line->r = 40;
		mlx->line->g = 40;
		mlx->line->b = 40;
		mlx->line->x0 = i;
		mlx->line->y0 = 0;
		mlx->line->x1 = i;
		mlx->line->y1 = P_HEIGHT / 2 - 1;
		softline(mlx, mlx->data, bkg);
		mlx->line->r = 90;
		mlx->line->g = 5;
		mlx->line->b = 2;
		mlx->line->x0 = i;
		mlx->line->y0 = P_HEIGHT / 2;
		mlx->line->x1 = i;
		mlx->line->y1 = P_HEIGHT - 1;
		softline(mlx, mlx->data, bkg);
	}
	return (0);
}

int			play_gay(t_params *content, t_bkg *bkg)
{
	*bkg = (t_bkg){ 0, 0, 0, 0, 0 };
	background(content->mlx, bkg);
	mlx_put_image_to_window(content->mlx->mlx_ptr,
	content->mlx->win_ptr, content->mlx->img_ptr, 0, 0);
	raycast(content);
	return (0);
}
