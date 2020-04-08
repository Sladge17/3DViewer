/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltris_zbuf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 14:24:01 by student           #+#    #+#             */
/*   Updated: 2020/04/08 14:24:06 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ftris_zbuf(t_system *system, t_coords *coords)
{
	int		height[2];
	int		i;

	sorty_zbuf(coords);
	height[0] = coords->d_tris[2][1] - coords->d_tris[0][1];
	coords->d_line[0][1] = coords->d_tris[0][1];
	i = coords->d_tris[0][1] == coords->d_tris[1][1] ? 1 : 0;
	while (i < 2)
	{
		height[1] = coords->d_tris[i + 1][1] - coords->d_tris[i][1];
		while (coords->d_line[0][1] < coords->d_tris[i + 1][1])
		{
			setlinex_zbuf(system, coords, height, i);
			linex_zbuf(system, coords->d_line[0],
				coords->d_line[1], coords->f_line);
			lastvlx_zbuf(system, coords);
			coords->d_line[0][1] += 1;
		}
		if (coords->d_tris[1][1] == coords->d_tris[2][1])
			break ;
		i += 1;
	}
}

void	sorty_zbuf(t_coords *coords)
{
	int		i;
	int		j;

	j = 0;
	while (j < 2)
	{
		i = 0;
		while (i < 2 - j)
		{
			if (coords->d_tris[i][1] > coords->d_tris[i + 1][1])
				sorty_zbuf2(coords, i);
			i += 1;
		}
		j += 1;
	}
}

void	sorty_zbuf2(t_coords *coords, int i)
{
	int		tmp_d;
	float	tmp_f;

	tmp_d = coords->d_tris[i][0];
	coords->d_tris[i][0] = coords->d_tris[i + 1][0];
	coords->d_tris[i + 1][0] = tmp_d;
	tmp_d = coords->d_tris[i][1];
	coords->d_tris[i][1] = coords->d_tris[i + 1][1];
	coords->d_tris[i + 1][1] = tmp_d;
	tmp_d = coords->d_tris[i][2];
	coords->d_tris[i][2] = coords->d_tris[i + 1][2];
	coords->d_tris[i + 1][2] = tmp_d;
	tmp_f = coords->f_tris[i];
	coords->f_tris[i] = coords->f_tris[i + 1];
	coords->f_tris[i + 1] = tmp_f;
}

void	setlinex_zbuf(t_system *system, t_coords *coords, int *height, int i)
{
	float	int_xz[2];

	coords->d_line[1][1] = coords->d_line[0][1];
	int_xz[0] = (float)(coords->d_line[0][1] - coords->d_tris[0][1]) /
		height[0];
	int_xz[1] = (float)(coords->d_line[0][1] - coords->d_tris[i][1]) /
		height[1];
	coords->d_line[0][0] = coords->d_tris[0][0] +
		(coords->d_tris[2][0] - coords->d_tris[0][0]) * int_xz[0];
	coords->d_line[1][0] = coords->d_tris[i][0] +
		(coords->d_tris[i + 1][0] - coords->d_tris[i][0]) * int_xz[1];
	if (system->render & 64)
	{
		coords->d_line[0][2] = set_yrgb(coords->d_tris[0],
			coords->d_tris[2], coords->d_line[0][1]);
		coords->d_line[1][2] = set_yrgb(coords->d_tris[i],
			coords->d_tris[i + 1], coords->d_line[0][1]);
	}
	coords->f_line[0] = coords->f_tris[0] +
		(coords->f_tris[2] - coords->f_tris[0]) * int_xz[0];
	coords->f_line[1] = coords->f_tris[i] +
		(coords->f_tris[i + 1] - coords->f_tris[i]) * int_xz[1];
}

void	lastvlx_zbuf(t_system *system, t_coords *coords)
{
	if ((0 <= coords->d_line[1][0] && coords->d_line[1][0] < WIDTH) &&
		(0 <= coords->d_line[1][1] && coords->d_line[1][1] < HEIGHT) &&
		(int)coords->f_line[1] >=
		system->z_buf[coords->d_line[1][0] + coords->d_line[1][1] * WIDTH])
	{
		system->output[coords->d_line[1][0] +
		coords->d_line[1][1] * WIDTH] = coords->d_line[1][2];
		system->z_buf[coords->d_line[1][0] + coords->d_line[1][1] * WIDTH] =
			(int)coords->f_line[1];
	}
}
