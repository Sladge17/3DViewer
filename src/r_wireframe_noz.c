/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wireframe_noz.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 18:22:34 by student           #+#    #+#             */
/*   Updated: 2020/04/10 16:53:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	quad_nozbuf(t_sys *sys, t_model *model, t_coords *coords)
{
	defline_nozbuf(coords, 0, 1);
	line_nozbuf(sys, coords);
	coords->d_tris[1][0] = coords->d_quad[2][0];
	coords->d_tris[1][1] = coords->d_quad[2][1];
	line_nozbuf(sys, coords);
	if (coords->counter[0] == model->width - 2)
	{
		defline_nozbuf(coords, 2, 3);
		line_nozbuf(sys, coords);
	}
	if (coords->counter[1] == model->height - 2)
	{
		defline_nozbuf(coords, 1, 3);
		line_nozbuf(sys, coords);
	}
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT))
		sys->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] = COLOR_W;
}

void	defline_nozbuf(t_coords *coords, int v1, int v2)
{
	coords->d_tris[0][0] = coords->d_quad[v1][0];
	coords->d_tris[0][1] = coords->d_quad[v1][1];
	coords->d_tris[1][0] = coords->d_quad[v2][0];
	coords->d_tris[1][1] = coords->d_quad[v2][1];
}

void	line_nozbuf(t_sys *sys, t_coords *coords)
{
	char	d[2];
	int		len[2];

	if (coords->d_tris[0][1] == coords->d_tris[1][1])
	{
		linex_nozbuf(sys, coords->d_tris[0], coords->d_tris[1]);
		return ;
	}
	if (coords->d_tris[0][0] == coords->d_tris[1][0])
	{
		liney_nozbuf(sys, coords->d_tris[0], coords->d_tris[1]);
		return ;
	}
	d[0] = coords->d_tris[1][0] < coords->d_tris[0][0] ? -1 : 1;
	d[1] = coords->d_tris[1][1] < coords->d_tris[0][1] ? -1 : 1;
	len[0] = (coords->d_tris[1][0] - coords->d_tris[0][0]) * d[0];
	len[1] = (coords->d_tris[1][1] - coords->d_tris[0][1]) * d[1];
	coords->d_tris[0][2] = sys->render & 2 ? COLOR_W : COLOR_S;
	if (len[0] > len[1])
	{
		xmore_nozbuf(sys, coords, d, len);
		return ;
	}
	ymore_nozbuf(sys, coords, d, len);
}

void	xmore_nozbuf(t_sys *sys, t_coords *coords, char *d, int *len)
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
			sys->output[cursor[0] + cursor[1] * WIDTH] =
				coords->d_tris[0][2];
		overflow += len[1] + 1;
		if (overflow >= len[0] + 1)
		{
			cursor[1] += d[1];
			overflow -= len[0] + 1;
		}
		cursor[0] += d[0];
	}
}

void	ymore_nozbuf(t_sys *sys, t_coords *coords, char *d, int *len)
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
			sys->output[cursor[0] + cursor[1] * WIDTH] =
				coords->d_tris[0][2];
		overflow += len[0] + 1;
		if (overflow >= len[1] + 1)
		{
			cursor[0] += d[0];
			overflow -= len[1] + 1;
		}
		cursor[1] += d[1];
	}
}
