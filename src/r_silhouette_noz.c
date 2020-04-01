/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_silhouette_noz.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:43:49 by student           #+#    #+#             */
/*   Updated: 2020/04/01 12:44:01 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fquad_nozbuf(t_system *system, t_model *model, t_coords *coords)
{
	if ((coords->d_quad[0][0] == coords->d_quad[1][0] &&
		coords->d_quad[1][0] == coords->d_quad[2][0] &&
		coords->d_quad[2][0] == coords->d_quad[3][0]) ||
		(coords->d_quad[0][1] == coords->d_quad[1][1] &&
		coords->d_quad[1][1] == coords->d_quad[2][1] &&
		coords->d_quad[2][1] == coords->d_quad[3][1]))
	{
		quad_nozbuf(system, model, coords);
		return ;
	}
	if (model->diagonal[coords->counter[0] + coords->counter[1] * (model->width - 1)])
	{

		defline_nozbuf(coords, 0, 3);
		line_nozbuf(system, coords);
		
		deftris_nozbuf(coords, 0, 1, 3);
		ftris_nozbuf(system, coords);
		deftris_nozbuf(coords, 0, 2, 3);
		ftris_nozbuf(system, coords);

		return ;
	}

	defline_nozbuf(coords, 1, 2);
	line_nozbuf(system, coords);

	deftris_nozbuf(coords, 0, 1, 2);
	ftris_nozbuf(system, coords);
	deftris_nozbuf(coords, 1, 2, 3);
	ftris_nozbuf(system, coords);

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

void	ftris_nozbuf(t_system *system, t_coords *coords)	
{
	int		segment_height;
	int		total_height;
	int		i;
	float	int_x1;
	float	int_x2;
	int		cursor_y;
	int		cursor_x1;
	int		cursor_x2;

	int		vertex_0[2];
	int		vertex_1[2];

	// line_nozbuf(system, coords);
	// if ((0 <= coords->d_tris[1][0] && coords->d_tris[1][0] < WIDTH)
	// 	&& (0 <= coords->d_tris[1][1] && coords->d_tris[1][1] < HEIGHT))
	// 	system->output[coords->d_tris[1][0] +
	// 		coords->d_tris[1][1] * WIDTH] = COLOR_W;

	sorty_nozbuf(coords);

	// line_nozbuf(system, coords);


	total_height = coords->d_tris[2][1] - coords->d_tris[0][1];
	cursor_y = coords->d_tris[0][1];

	// i = 0;

	i = coords->d_tris[0][1] == coords->d_tris[1][1] ? 1 : 0;

	while (i < 2)
	{
		segment_height = coords->d_tris[i + 1][1] - coords->d_tris[i][1];
		while (cursor_y < coords->d_tris[i + 1][1])
		{

			int_x1 = (float)(cursor_y - coords->d_tris[0][1]) / total_height;
			int_x2 = (float)(cursor_y - coords->d_tris[i][1]) / segment_height;
			cursor_x1 = coords->d_tris[0][0] + (coords->d_tris[2][0] - coords->d_tris[0][0]) * int_x1;
			cursor_x2 = coords->d_tris[i][0] + (coords->d_tris[i + 1][0] - coords->d_tris[i][0]) * int_x2;

			vertex_0[0] = cursor_x1;
			vertex_0[1] = cursor_y;
			vertex_1[0] = cursor_x2;
			vertex_1[1] = cursor_y;


			linex_nozbuf(system, vertex_0, vertex_1);

			if ((0 <= vertex_1[0] && vertex_1[0] < WIDTH)
			&& (0 <= vertex_1[1] && vertex_1[1] < HEIGHT))
				system->output[vertex_1[0] +
				vertex_1[1] * WIDTH] = COLOR_S;

			cursor_y += 1;
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
