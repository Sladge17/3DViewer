/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 18:05:43 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/16 20:02:47 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scalepos(t_model *model, t_coords *coords)
{
	static char	first = 0;
	float		vert_min[2];
	float		vert_max[2];
	float		o_len[2];

	fill_overtex(model, coords);
	set_minmaxvert(model, vert_min, vert_max);
	o_len[0] = vert_max[0] - vert_min[0];
	o_len[1] = vert_max[1] - vert_min[1];
	model->scale = WIDTH / o_len[0] < HEIGHT / o_len[1] ?
					(WIDTH - 100) / o_len[0] :
					(HEIGHT - 100) / o_len[1];
	model->pos[0] = WIDTH / 2 - model->scale * (vert_min[0] + o_len[0] / 2);
	model->pos[1] = HEIGHT / 2 - model->scale * (vert_min[1] + o_len[1] / 2);
	if (!first)
	{
		model->first_scale = model->scale;
		model->first_pos[0] = model->pos[0];
		model->first_pos[1] = model->pos[1];
		first = 1;
	}
}

void	fill_overtex(t_model *model, t_coords *coords)
{
	int		k;

	coords->counter[1] = 0;
	while (coords->counter[1] < model->height - 1)
	{
		coords->counter[0] = 0;
		while (coords->counter[0] < model->width - 1)
		{
			setup_quad(model, coords, &k);
			while (k < 4)
			{
				rotate_quad(model, coords, k);
				model->o_vertex[coords->index[k]][0] = coords->f_quad[k][0];
				model->o_vertex[coords->index[k]][1] = coords->f_quad[k][1];
				k += 1;
			}
			coords->counter[0] += 1;
		}
		coords->counter[1] += 1;
	}
}

void	setup_quad(t_model *model, t_coords *coords, int *k)
{
	if (!coords->counter[0])
	{
		*k = 0;
		coords->index[0] = coords->counter[0]
						+ coords->counter[1] * model->width;
		coords->index[1] = coords->counter[0] + model->width
						+ coords->counter[1] * model->width;
	}
	else
	{
		*k = 2;
		shift_quadvert(coords);
	}
	coords->index[2] = coords->counter[0]
					+ coords->counter[1] * model->width + 1;
	coords->index[3] = coords->counter[0] + model->width
					+ coords->counter[1] * model->width + 1;
}

void	shift_quadvert(t_coords *coords)
{
	coords->index[0] = coords->index[2];
	coords->index[1] = coords->index[3];

	coords->f_quad[0][0] = coords->f_quad[2][0];
	coords->f_quad[0][1] = coords->f_quad[2][1];
	coords->f_quad[0][2] = coords->f_quad[2][2];
	coords->f_quad[1][0] = coords->f_quad[3][0];
	coords->f_quad[1][1] = coords->f_quad[3][1];
	coords->f_quad[1][2] = coords->f_quad[3][2];
	coords->d_quad[0][0] = coords->d_quad[2][0];
	coords->d_quad[0][1] = coords->d_quad[2][1];
	coords->d_quad[0][2] = coords->d_quad[2][2];
	coords->d_quad[1][0] = coords->d_quad[3][0];
	coords->d_quad[1][1] = coords->d_quad[3][1];
	coords->d_quad[1][2] = coords->d_quad[3][2];
}

void	set_minmaxvert(t_model *model, float *vert_min, float *vert_max)
{
	int		i;

	vert_min[0] = model->o_vertex[0][0];
	vert_min[1] = model->o_vertex[0][1];
	vert_max[0] = model->o_vertex[0][0];
	vert_max[1] = model->o_vertex[0][1];
	i = 1;
	while (i < model->area)
	{
		vert_min[0] = model->o_vertex[i][0] < vert_min[0] ?
							model->o_vertex[i][0] : vert_min[0];
		vert_min[1] = model->o_vertex[i][1] < vert_min[1] ?
							model->o_vertex[i][1] : vert_min[1];
		vert_max[0] = model->o_vertex[i][0] > vert_max[0] ?
							model->o_vertex[i][0] : vert_max[0];
		vert_max[1] = model->o_vertex[i][1] > vert_max[1] ?
							model->o_vertex[i][1] : vert_max[1];
		i += 1;
	}
}
