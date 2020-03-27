/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_vertex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:53:00 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:53:06 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_qvertex(t_system *system, t_model *model, t_coords *coords)
{
	if (model->color_f && system->render & 64)
	{
		vert_zbuf(system, coords, 0);
		if (coords->counter[0] == model->width - 2)
			vert_zbuf(system, coords, 2);
		if (coords->counter[1] == model->height - 2)
			vert_zbuf(system, coords, 1);
		if (coords->index[3] == model->area - 1)
			vert_zbuf(system, coords, 3);
		return ;
	}
	vert_nozbuf(system, coords, 0);
	if (coords->counter[0] == model->width - 2)
		vert_nozbuf(system, coords, 2);
	if (coords->counter[1] == model->height - 2)
		vert_nozbuf(system, coords, 1);
	if (coords->index[3] == model->area - 1)
		vert_nozbuf(system, coords, 3);
}

void	vert_zbuf(t_system *system, t_coords *coords, int i)
{
	int		j;

	if (!(vert_onscreen(&i, coords)))
		return ;
	j = -1;
	while (j < 2)
	{
		if (coords->f_quad[i][2] > system->z_buf[(coords->d_quad[i][0]) +
			(coords->d_quad[i][1] - j) * WIDTH])
		{
			system->output[(coords->d_quad[i][0]) +
				(coords->d_quad[i][1] - j) * WIDTH] = coords->d_quad[i][2];
			system->z_buf[(coords->d_quad[i][0]) +
				(coords->d_quad[i][1] - j) * WIDTH] =
				lround(coords->f_quad[i][2]);
		}
		vert_updownlines(system, coords, &i, &j);
		j += 1;
	}
}

void	vert_updownlines(t_system *system, t_coords *coords, int *i, int *j)
{
	if (coords->d_quad[*i][0] && coords->f_quad[*i][2] >
		system->z_buf[(coords->d_quad[*i][0] - 1) +
		(coords->d_quad[*i][1] - *j) * WIDTH])
	{
		system->output[(coords->d_quad[*i][0] - 1) +
			(coords->d_quad[*i][1] - *j) * WIDTH] = coords->d_quad[*i][2];
		system->z_buf[(coords->d_quad[*i][0] - 1) +
			(coords->d_quad[*i][1] - *j) * WIDTH] =
			lround(coords->f_quad[*i][2]);
	}
	if (coords->d_quad[*i][0] != WIDTH - 1 && coords->f_quad[*i][2] >
		system->z_buf[(coords->d_quad[*i][0] + 1) +
		(coords->d_quad[*i][1] - *j) * WIDTH])
	{
		system->output[(coords->d_quad[*i][0] + 1) +
			(coords->d_quad[*i][1] - *j) * WIDTH] = coords->d_quad[*i][2];
		system->z_buf[(coords->d_quad[*i][0] + 1) +
			(coords->d_quad[*i][1] - *j) * WIDTH] =
			lround(coords->f_quad[*i][2]);
	}
}

void	vert_nozbuf(t_system *system, t_coords *coords, int i)
{
	int		j;

	if (!(vert_onscreen(&i, coords)))
		return ;
	j = -1;
	while (j < 2)
	{
		if (coords->d_quad[i][0])
			system->output[(coords->d_quad[i][0] - 1) +
				(coords->d_quad[i][1] - j) * WIDTH] = COLOR_V;
		system->output[(coords->d_quad[i][0]) +
			(coords->d_quad[i][1] - j) * WIDTH] = COLOR_V;
		if (coords->d_quad[i][0] != WIDTH - 1)
			system->output[(coords->d_quad[i][0] + 1) +
				(coords->d_quad[i][1] - j) * WIDTH] = COLOR_V;
		j += 1;
	}
}

char	vert_onscreen(int *i, t_coords *coords)
{
	if ((coords->d_quad[*i][0] < 0) ||
		(coords->d_quad[*i][0] > WIDTH - 1) ||
		(coords->d_quad[*i][1] < 0) ||
		(coords->d_quad[*i][1] > HEIGHT - 2))
	{
		*i += 1;
		return (0);
	}
	return (1);
}
