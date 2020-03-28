/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wirez.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 10:52:26 by student           #+#    #+#             */
/*   Updated: 2020/03/28 10:52:30 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

char	quad_zbuf(t_system *system, t_model *model, t_coords *coords)
{
	if (!model->color_f || !(system->render & 64))
		return (0);
	corner_zbuf(system, coords);
	if (coords->counter[0] == model->width - 2)
	{
		coords->tris_z[0] = coords->f_quad[2][2];
		coords->tris_z[1] = coords->f_quad[3][2];
		line_zbuf(system, coords->d_quad[2], coords->d_quad[3], coords->tris_z);
	}
	if (coords->counter[1] == model->height - 2)
	{
		coords->tris_z[0] = coords->f_quad[1][2];
		coords->tris_z[1] = coords->f_quad[3][2];
		line_zbuf(system, coords->d_quad[1], coords->d_quad[3], coords->tris_z);
	}
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > system->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		system->output[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH] = coords->d_quad[3][2];
	return (1);
}

void	corner_zbuf(t_system *system, t_coords *coords)
{
	coords->tris_z[0] = coords->f_quad[0][2];
	coords->tris_z[1] = coords->f_quad[1][2];
	line_zbuf(system, coords->d_quad[0], coords->d_quad[1], coords->tris_z);
	// coords->tris_z[0] = coords->f_quad[0][2]; //MAYBE DELL
	coords->tris_z[1] = coords->f_quad[2][2];
	line_zbuf(system, coords->d_quad[0], coords->d_quad[2], coords->tris_z);
}


void	line_zbuf(t_system *system, int *vertex_0, int *vertex_1, float *tris_z)
{
	char	d[2];
	int		len[2];
	int		overflow;
	int		cursor[2];

	float	int_z;
	float	cur_z;

	d[0] = vertex_1[0] < vertex_0[0] ? -1 : 1;
	d[1] = vertex_1[1] < vertex_0[1] ? -1 : 1;
	len[0] = (vertex_1[0] - vertex_0[0]) * d[0];
	len[1] = (vertex_1[1] - vertex_0[1]) * d[1];
	cursor[0] = vertex_0[0];
	cursor[1] = vertex_0[1];
	overflow = 0;

	// if (vertex_0[1] == vertex_1[1])
	// {
	// 	linex_zbuf(system, vertex_0, vertex_1, tris_z);
	// 	return ;
	// }

	if (len[0] > len[1])
	{

		while (cursor[0] != vertex_1[0])
		{
			if ((0 <= cursor[0] && cursor[0] < WIDTH)
				&& (0 <= cursor[1] && cursor[1] < HEIGHT))
			{
				int_z = (float)(abs(cursor[0] - vertex_0[0])) / (float)(abs(vertex_1[0] - vertex_0[0]));
				cur_z = tris_z[0] + (tris_z[1] - tris_z[0]) * int_z;
				if (cur_z > system->z_buf[cursor[0] + cursor[1] * WIDTH])
				{
					system->output[cursor[0] + cursor[1] * WIDTH] = set_xrgb(vertex_0, vertex_1, cursor[0]);
					system->z_buf[cursor[0] + cursor[1] * WIDTH] = cur_z;
				}
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

	else
	{
		while (cursor[1] != vertex_1[1])
		{
			if ((0 <= cursor[0] && cursor[0] < WIDTH)
				&& (0 <= cursor[1] && cursor[1] < HEIGHT))
			{
				int_z = (float)(abs(cursor[1] - vertex_0[1])) / (float)(abs(vertex_1[1] - vertex_0[1]));
				cur_z = tris_z[0] + (tris_z[1] - tris_z[0]) * int_z;
				if (cur_z > system->z_buf[cursor[0] + cursor[1] * WIDTH])
				{
					system->output[cursor[0] + cursor[1] * WIDTH] = set_yrgb(vertex_0, vertex_1, cursor[1]);
					system->z_buf[cursor[0] + cursor[1] * WIDTH] = cur_z;
				}
			}
			overflow += len[0] + 1;
			if (overflow >= len[1] + 1)
			{
				cursor[0] += d[0];
				overflow -= len[1] + 1;
			}
			cursor[1] += d[1];
		}
		return ;
	}

}


























