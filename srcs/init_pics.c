/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 17:20:08 by ohelly            #+#    #+#             */
/*   Updated: 2019/08/17 18:38:16 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		get_pics_part_two(t_texture *texture, t_mlx *mlx, int w, int h)
{
	if (!(texture->walls[9] = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL54.xpm", &w, &h)) || !(texture->walls[10] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL53.xpm", &w, &h)) || !(texture->walls[11] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL6.xpm", &w, &h)) || !(texture->walls[12] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL11.xpm", &w, &h)) || !(texture->walls[13] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL4.xpm", &w, &h)) || !(texture->walls[14] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL11.xpm", &w, &h)) || !(texture->walls[15] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL4.xpm", &w, &h)) || !(texture->walls[16] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL105.xpm", &w, &h)))
		return (0);
	return (1);
}

static int		get_pics(t_texture *texture, t_mlx *mlx, int w, int h)
{
	if (!(texture->walls[0] = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL3.xpm", &w, &h)) || !(texture->walls[1] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL2.xpm", &w, &h)) || !(texture->walls[2] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL3.xpm", &w, &h)) || !(texture->walls[3] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL2.xpm", &w, &h)) || !(texture->walls[4] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL3.xpm", &w, &h)) || !(texture->walls[5] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL4.xpm", &w, &h)) || !(texture->walls[6] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL3.xpm", &w, &h)) || !(texture->walls[7] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL4.xpm", &w, &h)) || !(texture->walls[8] =
	mlx_xpm_file_to_image(mlx->mlx_ptr,
	"pics/walls/WALL3.xpm", &w, &h)) ||
	!(get_pics_part_two(texture, mlx, w, h)))
		return (0);
	return (1);
}

static int		get_data_part_two(t_texture *texture, int bpp, int sl, int end)
{
	if (!(texture->data_walls[9] =
	mlx_get_data_addr(texture->walls[9],
	&bpp, &sl, &end)) || !(texture->data_walls[10] =
	mlx_get_data_addr(texture->walls[10],
	&bpp, &sl, &end)) || !(texture->data_walls[11] =
	mlx_get_data_addr(texture->walls[11],
	&bpp, &sl, &end)) || !(texture->data_walls[12] =
	mlx_get_data_addr(texture->walls[12],
	&bpp, &sl, &end)) || !(texture->data_walls[13] =
	mlx_get_data_addr(texture->walls[13],
	&bpp, &sl, &end)) || !(texture->data_walls[14] =
	mlx_get_data_addr(texture->walls[14],
	&bpp, &sl, &end)) || !(texture->data_walls[15] =
	mlx_get_data_addr(texture->walls[15],
	&bpp, &sl, &end)) || !(texture->data_walls[16] =
	mlx_get_data_addr(texture->walls[16],
	&bpp, &sl, &end)))
		return (0);
	return (1);
}

static int		get_data(t_texture *texture, int bpp, int sl, int end)
{
	if (!(texture->data_walls[0] =
	mlx_get_data_addr(texture->walls[0],
	&bpp, &sl, &end)) || !(texture->data_walls[1] =
	mlx_get_data_addr(texture->walls[1],
	&bpp, &sl, &end)) || !(texture->data_walls[2] =
	mlx_get_data_addr(texture->walls[2],
	&bpp, &sl, &end)) || !(texture->data_walls[3] =
	mlx_get_data_addr(texture->walls[3],
	&bpp, &sl, &end)) || !(texture->data_walls[4] =
	mlx_get_data_addr(texture->walls[4],
	&bpp, &sl, &end)) || !(texture->data_walls[5] =
	mlx_get_data_addr(texture->walls[5],
	&bpp, &sl, &end)) || !(texture->data_walls[6] =
	mlx_get_data_addr(texture->walls[6],
	&bpp, &sl, &end)) || !(texture->data_walls[7] =
	mlx_get_data_addr(texture->walls[7],
	&bpp, &sl, &end)) || !(texture->data_walls[8] =
	mlx_get_data_addr(texture->walls[8],
	&bpp, &sl, &end)) || !(get_data_part_two(texture, bpp, sl, end)))
		return (0);
	return (1);
}

int				init_pics(t_texture *texture, t_mlx *mlx)
{
	int		w;
	int		h;
	int		bpp;
	int		sl;
	int		end;

	w = 0;
	h = 0;
	bpp = 0;
	sl = 0;
	end = 0;
	if (!(get_pics(texture, mlx, w, h)))
		return (0);
	if (!(get_data(texture, bpp, sl, end)))
		return (0);
	return (1);
}
