/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:18:31 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/17 22:12:08 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				init_pistol(t_params *content)
{
	int		w;
	int		h;

	w = 0;
	h = 0;
	if (!(content->pistol->pic_pistol[0] = mlx_xpm_file_to_image(
	content->mlx->mlx_ptr, "pics/pistol/REVIA0.xpm", &w, &h)))
		return (0);
	if (!(content->pistol->pic_pistol[1] = mlx_xpm_file_to_image(
	content->mlx->mlx_ptr, "pics/pistol/REVFA0.xpm", &w, &h)))
		return (0);
	if (!(content->pistol->pic_pistol[2] = mlx_xpm_file_to_image(
	content->mlx->mlx_ptr, "pics/pistol/REVFB0.xpm", &w, &h)))
		return (0);
	if (!(content->pistol->pic_pistol[3] = mlx_xpm_file_to_image(
	content->mlx->mlx_ptr, "pics/pistol/REVFC0.xpm", &w, &h)))
		return (0);
	if (!(content->pistol->pic_pistol[4] = mlx_xpm_file_to_image(
	content->mlx->mlx_ptr, "pics/pistol/REVFD0.xpm", &w, &h)))
		return (0);
	return (1);
}

static void		play_sound(void)
{
	if (system("ps | grep afplay | grep -v grep | > /dev/null") != 0)
		system("kill $(ps aux | grep afplay | grep -v grep | awk '{print$2}')");
	system("afplay sounds/Pistol.wav &");
}

static void		put_image(t_pistol *pist, t_mlx *mlx, t_params *cont, int i)
{
	mlx_clear_window(cont->mlx->mlx_ptr, cont->mlx->win_ptr);
	play_gay(cont, cont->bkg);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, pist->pic_pistol[i],
	W_WIDTH / 3 - 108, W_HEIGHT - 335);
}

static int		output_pistol(t_pistol *pistol, t_mlx *mlx, t_params *content)
{
	static int		i = 0;

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, pistol->pic_pistol[i],
	W_WIDTH / 3 - 108, W_HEIGHT - 335);
	if (pistol->delay == DELAY_PISTOL && pistol->app == 1)
	{
		if (i == 1)
			play_sound();
		put_image(pistol, mlx, content, i++);
		if (i == 5)
		{
			i = 0;
			pistol->app = 0;
			put_image(pistol, mlx, content, i);
		}
		pistol->delay = 0;
	}
	else if (pistol->app == 1 && pistol->delay != DELAY_PISTOL)
		pistol->delay++;
	return (1);
}

int				output(t_params *content)
{
	if (content->app != 1)
		out_menu(content);
	else
		output_pistol(content->pistol, content->mlx, content);
	return (1);
}
