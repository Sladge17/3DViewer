/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wireframe_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 17:38:15 by student           #+#    #+#             */
/*   Updated: 2020/04/10 16:53:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	quad_zbuf(t_sys *sys, t_model *model, t_coords *coords)
{
	defline_zbuf(coords, 0, 1);
	line_zbuf(sys, coords);
	coords->d_tris[1][0] = coords->d_quad[2][0];
	coords->d_tris[1][1] = coords->d_quad[2][1];
	coords->d_tris[1][2] = coords->d_quad[2][2];
	coords->f_tris[1] = coords->f_quad[2][2];
	line_zbuf(sys, coords);
	if (coords->counter[0] == model->width - 2)
	{
		defline_zbuf(coords, 2, 3);
		line_zbuf(sys, coords);
	}
	if (coords->counter[1] == model->height - 2)
	{
		defline_zbuf(coords, 1, 3);
		line_zbuf(sys, coords);
	}
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > sys->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		sys->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] = coords->d_quad[3][2];
}

void	defline_zbuf(t_coords *coords, int v1, int v2)
{
	coords->d_tris[0][0] = coords->d_quad[v1][0];
	coords->d_tris[0][1] = coords->d_quad[v1][1];
	coords->d_tris[0][2] = coords->d_quad[v1][2];
	coords->f_tris[0] = coords->f_quad[v1][2];
	coords->d_tris[1][0] = coords->d_quad[v2][0];
	coords->d_tris[1][1] = coords->d_quad[v2][1];
	coords->d_tris[1][2] = coords->d_quad[v2][2];
	coords->f_tris[1] = coords->f_quad[v2][2];
}

void	line_zbuf(t_sys *sys, t_coords *coords)
{
	char	d[2];
	int		len[2];

	if (vertz_zbuf(sys, coords))
		return ;
	if (coords->d_tris[0][1] == coords->d_tris[1][1])
	{
		linex_zbuf(sys, coords->d_tris[0], coords->d_tris[1], coords->f_tris);
		return ;
	}
	if (coords->d_tris[0][0] == coords->d_tris[1][0])
	{
		liney_zbuf(sys, coords->d_tris[0], coords->d_tris[1], coords->f_tris);
		return ;
	}
	d[0] = coords->d_tris[1][0] < coords->d_tris[0][0] ? -1 : 1;
	d[1] = coords->d_tris[1][1] < coords->d_tris[0][1] ? -1 : 1;
	len[0] = (coords->d_tris[1][0] - coords->d_tris[0][0]) * d[0];
	len[1] = (coords->d_tris[1][1] - coords->d_tris[0][1]) * d[1];
	if (len[0] > len[1])
	{
		xmore_zbuf(sys, coords, d, len);
		return ;
	}
	ymore_zbuf(sys, coords, d, len);
}

void	xmore_zbuf(t_sys *sys, t_coords *coords, char *d, int *len)
{
	int		cursor[2];
	int		overflow;

	cursor[0] = coords->d_tris[0][0];
	cursor[1] = coords->d_tris[0][1];
	overflow = 0;
	while (cursor[0] != coords->d_tris[1][0])
	{
		if ((0 <= cursor[0] && cursor[0] < WIDTH)
			&& (0 <= cursor[1] && cursor[1] < HEIGHT))
			if (check_zbuf(sys, coords, cursor, 0))
			{
				sys->output[cursor[0] + cursor[1] * WIDTH] =
				set_xrgb(coords->d_tris[0], coords->d_tris[1], cursor[0]);
			}
		overflow += len[1] + 1;
		if (overflow >= len[0] + 1)
		{
			cursor[1] += d[1];
			overflow -= len[0] + 1;
		}
		cursor[0] += d[0];
	}
}

void	ymore_zbuf(t_sys *sys, t_coords *coords, char *d, int *len)
{
	int		cursor[2];
	int		overflow;

	cursor[0] = coords->d_tris[0][0];
	cursor[1] = coords->d_tris[0][1];
	overflow = 0;
	while (cursor[1] != coords->d_tris[1][1])
	{
		if ((0 <= cursor[0] && cursor[0] < WIDTH)
			&& (0 <= cursor[1] && cursor[1] < HEIGHT))
			if (check_zbuf(sys, coords, cursor, 1))
			{
				sys->output[cursor[0] + cursor[1] * WIDTH] =
				set_yrgb(coords->d_tris[0], coords->d_tris[1], cursor[1]);
			}
		overflow += len[0] + 1;
		if (overflow >= len[1] + 1)
		{
			cursor[0] += d[0];
			overflow -= len[1] + 1;
		}
		cursor[1] += d[1];
	}
}
