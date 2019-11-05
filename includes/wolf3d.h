/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:17:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/18 17:09:02 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlx.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# define W_WIDTH 1280
# define W_HEIGHT 720
# define P_WIDTH 1280
# define P_HEIGHT 720
# define BUFF_SIZE 1
# define DELAY_PISTOL 4
# define T_SIZE 64
# define DEGREE (1 / 57.2958)

typedef struct			s_bkg
{
	int					tmp_r;
	int					tmp_g;
	int					tmp_b;
	int					y;
	int					x;
}						t_bkg;

typedef struct			s_mov
{
	int					p_x;
	int					p_y;
	int					i;
	int					j;
}						t_mov;

typedef struct			s_temp
{
	int					xa;
	int					ya;
	int					bx;
	int					by;
	int					t;
}						t_temp;

typedef struct			s_map
{
	int					fd;
	int					c_i;
	int					c_j;
	int					pos_x;
	int					pos_y;
	int					x;
	int					y;
	int					angle;
	int					**data;
}						t_map;

typedef struct			s_pistol
{
	int					app;
	int					delay;
	void				*pic_pistol[5];
}						t_pistol;

typedef struct			s_main
{
	int					app;
	int					pos;
	void				*pic_ng;
	void				*pic_cont;
	void				*pic_exit;
	void				*pic_font_one;
	void				*pic_font_two;
}						t_main;

typedef struct			s_line
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					r;
	int					g;
	int					b;
	float				intensive[P_WIDTH];
}						t_line;

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*data;
	t_line				*line;
}						t_mlx;

typedef struct			s_texture
{
	void				*walls[17];
	char				*data_walls[17];
	int					offset[P_WIDTH];
	int					v_offset;
	int					h_offset;
	int					colheight;
	int					toppoint;
	int					x;
	int					y;
}						t_texture;

typedef struct			s_rcast
{
	t_map				*map;
	t_texture			*texture;
	int					fov;
	int					p_length;
	double				cur_angle;
	double				len[P_WIDTH];
	int					h_len[P_WIDTH];
	int					v_len[P_WIDTH];
	int					side[P_WIDTH];
	int					door;
	int					v_door;
	int					h_door;
	int					wall;
	int					w_h;
	int					w_v;
	int					n;
}						t_rcast;

typedef struct			s_params
{
	t_mlx				*mlx;
	t_pistol			*pistol;
	t_rcast				*rcast;
	t_main				*menu;
	t_temp				*temp;
	t_mov				*mov;
	t_bkg				*bkg;
	int					app;
}						t_params;

int						readmap(t_rcast *rcast);
int						init_all(t_params *content);
int						get_next_line(const int fd, char **line);
int						out_menu(t_params *content);
int						key_press(int key, t_params *content);
int						play_gay(t_params *content, t_bkg *bkg);
int						output(t_params *content);
int						raycast(t_params *content);
int						find_walls(t_rcast *rcast);
int						close_prog(t_params *content);
int						change_walls(t_rcast *rcast, t_texture *texture);
int						put_walls(t_rcast *rcast, t_texture *texture,
t_mlx *mlx);
int						init_menu(t_main *menu, t_mlx *mlx);
int						init_pistol(t_params *content);
int						init_pics(t_texture *texture, t_mlx *mlx);
int						die(t_params *content, int err);
void					doors(t_rcast *rcast, t_temp *temp);
void					moving(t_rcast *rcast, t_mov *mov, int key);

#endif
