/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 16:16:02 by ohelly            #+#    #+#             */
/*   Updated: 2019/08/17 18:39:01 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				init_menu(t_main *menu, t_mlx *mlx)
{
	int		w;
	int		h;

	w = 0;
	h = 0;
	menu->pos = 1;
	if (!(menu->pic_ng = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/menu/play.xpm", &w, &h)))
		return (0);
	if (!(menu->pic_cont = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/menu/resume.xpm", &w, &h)))
		return (0);
	if (!(menu->pic_exit = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/menu/quitgame.xpm", &w, &h)))
		return (0);
	if (!(menu->pic_font_one = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/menu/font_one.xpm", &w, &h)))
		return (0);
	if (!(menu->pic_font_two = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/menu/font_two.xpm", &w, &h)))
		return (0);
	return (1);
}

static int		out_menu_two(t_mlx *mlx, t_main *menu)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
	menu->pic_font_two, 0, 0);
	if (menu->pos == 1)
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		menu->pic_cont, 426, 257);
	else
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		menu->pic_cont, 416, 250);
	if (menu->pos == 2)
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		menu->pic_exit, 426, 389);
	else
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		menu->pic_exit, 416, 382);
	return (1);
}

static int		out_menu_one(t_mlx *mlx, t_main *menu)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
	menu->pic_font_two, 0, 0);
	if (menu->pos == 1)
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		menu->pic_ng, 426, 257);
	else
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		menu->pic_ng, 416, 250);
	if (menu->pos == 2)
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		menu->pic_exit, 426, 389);
	else
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		menu->pic_exit, 416, 382);
	return (1);
}

static int		out_menu_zero(t_mlx *mlx, t_main *menu)
{
	static int		x1 = -400;
	static int		x2 = 1232;

	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
	menu->pic_font_one, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
	menu->pic_ng, x1, 250);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
	menu->pic_exit, x2, 382);
	x1 += 6;
	x2 -= 6;
	if (x1 >= 415)
		menu->app = 1;
	return (1);
}

int				out_menu(t_params *content)
{
	if (content->menu->app == 0)
		out_menu_zero(content->mlx, content->menu);
	if (content->menu->app == 1)
		out_menu_one(content->mlx, content->menu);
	if (content->menu->app == 2)
		out_menu_two(content->mlx, content->menu);
	return (1);
}
