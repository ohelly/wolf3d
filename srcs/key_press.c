/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:33:18 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/18 18:25:09 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		key_menu(t_params *content, t_main *menu, int key)
{
	if (key == 125)
		menu->pos += 1;
	if (key == 126)
		menu->pos -= 1;
	if (menu->pos == 3)
		menu->pos = 1;
	if (menu->pos == 0)
		menu->pos = 2;
	if (key == 36)
	{
		if (content->menu->pos == 1)
			content->app = 1;
		else if (content->menu->pos == 2)
			die(content, 0);
	}
}

static void		check_angle_and_out(t_params *content)
{
	int		a;
	int		b;
	int		c;

	if (content->rcast->map->angle < 0)
		content->rcast->map->angle += 360;
	if (content->rcast->map->angle >= 360)
		content->rcast->map->angle -= 360;
	mlx_destroy_image(content->mlx->mlx_ptr, content->mlx->img_ptr);
	content->mlx->img_ptr = mlx_new_image(content->mlx->mlx_ptr,
	W_WIDTH, W_HEIGHT);
	content->mlx->data = mlx_get_data_addr(content->mlx->img_ptr, &a, &b, &c);
	if (content->pistol->app != 1)
	{
		play_gay(content, content->bkg);
		mlx_put_image_to_window(content->mlx->mlx_ptr, content->mlx->win_ptr,
		content->pistol->pic_pistol[0], W_WIDTH / 3 - 108, W_HEIGHT - 335);
	}
}

int				key_press(int key, t_params *content)
{
	if (content->app != 1 && content->menu->app != 0)
		key_menu(content, content->menu, key);
	if (content->app == 1)
	{
		if (key == 35)
		{
			content->app = 2;
			content->menu->app = 2;
		}
		if (key == 49)
			content->pistol->app = 1;
		if (key == 0 && content->pistol->app != 1)
			content->rcast->map->angle += 5;
		if (key == 2 && content->pistol->app != 1)
			content->rcast->map->angle -= 5;
		if (key == 14)
			doors(content->rcast, content->temp);
		if (content->pistol->app != 1 && (key == 1 || key == 13))
			moving(content->rcast, content->mov, key);
		check_angle_and_out(content);
	}
	if (key == 53)
		die(content, 0);
	return (1);
}
