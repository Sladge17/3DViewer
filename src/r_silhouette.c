/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_silhouette.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:43:49 by student           #+#    #+#             */
/*   Updated: 2020/04/10 16:53:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fquad_nozbuf(t_sys *sys, t_model *model, t_coords *coords)
{
	if ((coords->d_quad[0][0] == coords->d_quad[1][0] &&
		coords->d_quad[1][0] == coords->d_quad[2][0] &&
		coords->d_quad[2][0] == coords->d_quad[3][0]) ||
		(coords->d_quad[0][1] == coords->d_quad[1][1] &&
		coords->d_quad[1][1] == coords->d_quad[2][1] &&
		coords->d_quad[2][1] == coords->d_quad[3][1]))
	{
		quad_nozbuf(sys, model, coords);
		return ;
	}
	if (model->diagonal[coords->counter[0] +
		coords->counter[1] * (model->width - 1)])
	{
		deftris_nozbuf(coords, 0, 1, 3);
		ftris_nozbuf(sys, coords);
		deftris_nozbuf(coords, 0, 2, 3);
		ftris_nozbuf(sys, coords);
		return ;
	}
	deftris_nozbuf(coords, 0, 1, 2);
	ftris_nozbuf(sys, coords);
	deftris_nozbuf(coords, 1, 2, 3);
	ftris_nozbuf(sys, coords);
}

void	deftris_nozbuf(t_coords *coords, char v1, char v2, char v3)
{
	coords->d_tris[0][0] = coords->d_quad[v1][0];
	coords->d_tris[0][1] = coords->d_quad[v1][1];
	coords->d_tris[1][0] = coords->d_quad[v2][0];
	coords->d_tris[1][1] = coords->d_quad[v2][1];
	coords->d_tris[2][0] = coords->d_quad[v3][0];
	coords->d_tris[2][1] = coords->d_quad[v3][1];
}

void	ftris_nozbuf(t_sys *sys, t_coords *coords)
{
	int		height[2];
	int		i;

	sorty_nozbuf(coords);
	height[0] = coords->d_tris[2][1] - coords->d_tris[0][1];
	coords->d_line[0][1] = coords->d_tris[0][1];
	i = coords->d_tris[0][1] == coords->d_tris[1][1] ? 1 : 0;
	while (i < 2)
	{
		height[1] = coords->d_tris[i + 1][1] - coords->d_tris[i][1];
		while (coords->d_line[0][1] < coords->d_tris[i + 1][1])
		{
			setlinex_nozbuf(coords, height, i);
			linex_nozbuf(sys, coords->d_line[0], coords->d_line[1]);
			if ((0 <= coords->d_line[1][0] && coords->d_line[1][0] < WIDTH)
			&& (0 <= coords->d_line[1][1] && coords->d_line[1][1] < HEIGHT))
				sys->output[coords->d_line[1][0] +
				coords->d_line[1][1] * WIDTH] = COLOR_S;
			coords->d_line[0][1] += 1;
		}
		if (coords->d_tris[1][1] == coords->d_tris[2][1])
			break ;
		i += 1;
	}
}

void	sorty_nozbuf(t_coords *coords)
{
	int		i;
	int		j;
	int		tmp_d;

	j = 0;
	while (j < 2)
	{
		i = 0;
		while (i < 2 - j)
		{
			if (coords->d_tris[i][1] > coords->d_tris[i + 1][1])
			{
				tmp_d = coords->d_tris[i][0];
				coords->d_tris[i][0] = coords->d_tris[i + 1][0];
				coords->d_tris[i + 1][0] = tmp_d;
				tmp_d = coords->d_tris[i][1];
				coords->d_tris[i][1] = coords->d_tris[i + 1][1];
				coords->d_tris[i + 1][1] = tmp_d;
			}
			i += 1;
		}
		j += 1;
	}
}

void	setlinex_nozbuf(t_coords *coords, int *height, int i)
{
	float	int_x[2];

	coords->d_line[1][1] = coords->d_line[0][1];
	int_x[0] = (float)(coords->d_line[0][1] - coords->d_tris[0][1]) /
		height[0];
	int_x[1] = (float)(coords->d_line[0][1] - coords->d_tris[i][1]) /
		height[1];
	coords->d_line[0][0] = coords->d_tris[0][0] +
		(coords->d_tris[2][0] - coords->d_tris[0][0]) * int_x[0];
	coords->d_line[1][0] = coords->d_tris[i][0] +
		(coords->d_tris[i + 1][0] - coords->d_tris[i][0]) * int_x[1];
}
