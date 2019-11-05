/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:19:41 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/18 16:38:44 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(void)
{
	t_params *content;

	if (!(content = (t_params*)ft_memalloc(sizeof(t_params))))
		return (0);
	if (!(init_all(content)))
		return (die(content, 1));
	if (!(readmap(content->rcast)))
		return (die(content, 2));
	mlx_hook(content->mlx->win_ptr, 2, 0, key_press, content);
	mlx_hook(content->mlx->win_ptr, 17, 0, close_prog, content);
	mlx_loop_hook(content->mlx->mlx_ptr, output, content);
	mlx_loop(content->mlx->mlx_ptr);
	return (0);
}
