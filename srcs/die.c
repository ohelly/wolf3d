/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:37:20 by ohelly            #+#    #+#             */
/*   Updated: 2019/08/18 18:32:18 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			free_pistol_rcast(t_rcast *rcast, t_pistol *pistol)
{
	int		i;

	i = -1;
	if (pistol)
		free(pistol);
	if (rcast)
	{
		if (rcast->texture)
			free(rcast->texture);
		if (rcast->map)
		{
			if (rcast->map->data)
			{
				while (++i < rcast->map->c_i)
					free(rcast->map->data[i]);
				free(rcast->map->data);
			}
			free(rcast->map);
		}
		free(rcast);
	}
}

static void			free_menu(t_main *menu, t_mlx *mlx)
{
	if (menu)
	{
		if (menu->pic_cont)
			mlx_destroy_image(mlx->mlx_ptr, menu->pic_cont);
		if (menu->pic_exit)
			mlx_destroy_image(mlx->mlx_ptr, menu->pic_exit);
		if (menu->pic_font_one)
			mlx_destroy_image(mlx->mlx_ptr, menu->pic_font_one);
		if (menu->pic_font_two)
			mlx_destroy_image(mlx->mlx_ptr, menu->pic_font_two);
		if (menu->pic_ng)
			mlx_destroy_image(mlx->mlx_ptr, menu->pic_ng);
		free(menu);
	}
}

static void			free_mlx(t_mlx *mlx)
{
	if (mlx)
	{
		if (mlx->win_ptr)
			mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		if (mlx->img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		if (mlx->line)
			free(mlx->line);
		if (mlx->mlx_ptr)
			free(mlx->mlx_ptr);
		free(mlx);
	}
}

int					die(t_params *content, int err)
{
	if (err == 1)
		ft_putendl("can't init!");
	if (err == 2)
		ft_putendl("Not a valid map!");
	if (content)
	{
		free_pistol_rcast(content->rcast, content->pistol);
		free_menu(content->menu, content->mlx);
		if (content->temp)
			free(content->temp);
		if (content->mov)
			free(content->mov);
		if (content->bkg)
			free(content->bkg);
		free_mlx(content->mlx);
		free(content);
	}
	content = 0;
	exit(0);
}

int					close_prog(t_params *content)
{
	die(content, 0);
	exit(0);
}
