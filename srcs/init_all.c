/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:23:07 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/18 16:38:57 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		intensive(float *kek)
{
	float	coef;
	float	dig;
	int		i;

	i = -1;
	coef = 0.5 / (float)(W_HEIGHT / 2);
	dig = 1;
	while (++i < W_HEIGHT)
	{
		kek[i] = dig;
		if (i < W_HEIGHT / 2)
			dig -= coef;
		else
			dig += coef;
	}
	return (0);
}

static int		init_mlx(t_mlx *mlx)
{
	int		bpp;
	int		sl;
	int		end;

	if (!(mlx->mlx_ptr = mlx_init()) ||
	!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, W_WIDTH, W_HEIGHT, "Wolf3d"))
	|| !(mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, W_WIDTH, W_HEIGHT)) ||
	!(mlx->data = mlx_get_data_addr(mlx->img_ptr, &bpp, &sl, &end)))
		return (0);
	return (1);
}

static int		init_rcast(t_rcast *rcast)
{
	if (!(rcast->map = (t_map*)ft_memalloc(sizeof(t_map))))
		return (0);
	rcast->map->angle = 270;
	rcast->fov = 60;
	rcast->p_length = (P_WIDTH / 2) / tan(rcast->fov / 2 * DEGREE);
	return (1);
}

int				init_all(t_params *content)
{
	if (!(content->mlx = (t_mlx*)ft_memalloc(sizeof(t_mlx))) ||
	!(init_mlx(content->mlx)) || !(content->pistol =
	(t_pistol*)ft_memalloc(sizeof(t_pistol))) || !(init_pistol(content))
	|| !(content->rcast = (t_rcast*)ft_memalloc(sizeof(t_rcast))) ||
	!(init_rcast(content->rcast)) || !(content->rcast->texture =
	(t_texture*)ft_memalloc(sizeof(t_texture))) ||
	!(init_pics(content->rcast->texture, content->mlx)) || !(content->menu =
	(t_main*)ft_memalloc(sizeof(t_main))) ||
	!(init_menu(content->menu, content->mlx)) || !(content->mlx->line =
	(t_line*)ft_memalloc(sizeof(t_line))) || !(content->temp =
	(t_temp*)ft_memalloc(sizeof(t_temp))) || !(content->mov =
	(t_mov*)ft_memalloc(sizeof(t_mov))) || !(content->bkg =
	(t_bkg*)ft_memalloc(sizeof(t_bkg))))
		return (0);
	intensive(content->mlx->line->intensive);
	return (1);
}
