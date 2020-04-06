/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ortholines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 09:18:31 by student           #+#    #+#             */
/*   Updated: 2020/03/29 09:18:39 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	linex_nozbuf(t_system *system, int *vertex_0, int *vertex_1)
{
	char	dx;
	int		cursor;

	if (vertex_0[1] < 0 || vertex_0[1] > HEIGHT - 1)
		return ;
	vertex_0[2] = system->render & 2 ? COLOR_W : COLOR_S;
	dx = vertex_1[0] < vertex_0[0] ? -1 : 1;
	cursor = vertex_0[0];
	while (cursor != vertex_1[0])
	{
		if (cursor >= 0 && cursor < WIDTH)
			system->output[cursor + vertex_0[1] * WIDTH] = vertex_0[2];
		cursor += dx;
	}
}

void	liney_nozbuf(t_system *system, int *vertex_0, int *vertex_1)
{
	char	dy;
	int		cursor;

	if (vertex_0[0] < 0 || vertex_0[0] > WIDTH - 1)
		return ;
	vertex_0[2] = system->render & 2 ? COLOR_W : COLOR_S;
	dy = vertex_1[1] < vertex_0[1] ? -1 : 1;
	cursor = vertex_0[1];
	while (cursor != vertex_1[1])
	{
		if (cursor >= 0 && cursor < HEIGHT)
			system->output[vertex_0[0] + cursor * WIDTH] = vertex_0[2];
		cursor += dy;
	}
}

void	linex_zbuf(t_system *system, int *vertex_0, int *vertex_1, float *tris_z)
{
	char	dx;
	int		cursor;
	float	int_z;
	float	cursor_z;

	if (vertex_0[1] < 0 || vertex_0[1] > HEIGHT - 1)
		return ;
	dx = vertex_1[0] < vertex_0[0] ? -1 : 1;
	cursor = vertex_0[0];
	while (cursor != vertex_1[0])
	{
		if (cursor >= 0 && cursor < WIDTH)
		{
			int_z = (float)(abs(cursor - vertex_0[0])) /
				(float)(abs(vertex_1[0] - vertex_0[0]));
			cursor_z = tris_z[0] + (tris_z[1] - tris_z[0]) * int_z;
			if (cursor_z >= system->z_buf[cursor + vertex_0[1] * WIDTH])
			{
				if (system->render & 64)
					system->output[cursor + vertex_0[1] * WIDTH] =
						set_xrgb(vertex_0, vertex_1, cursor);
				else
					system->output[cursor + vertex_0[1] * WIDTH] =
						vertex_1[2];
				system->z_buf[cursor + vertex_0[1] * WIDTH] = cursor_z;
			}
		}
		cursor += dx;
	}
}

void	liney_zbuf(t_system *system, int *vertex_0, int *vertex_1, float *tris_z)
{
	char	dy;
	int		cursor;
	float	int_z;
	float	cursor_z;

	if (vertex_0[0] < 0 || vertex_0[0] > WIDTH - 1)
		return ;
	dy = vertex_1[1] < vertex_0[1] ? -1 : 1;
	cursor = vertex_0[1];
	while (cursor != vertex_1[1])
	{
		if (cursor >= 0 && cursor < WIDTH)
		{
			int_z = (float)(abs(cursor - vertex_0[1])) /
				(float)(abs(vertex_1[1] - vertex_0[1]));
			cursor_z = tris_z[0] + (tris_z[1] - tris_z[0]) * int_z;
			if (cursor_z > system->z_buf[vertex_0[0] + cursor * WIDTH])
			{
				system->output[vertex_0[0] + cursor * WIDTH] =
					set_yrgb(vertex_0, vertex_1, cursor);
				system->z_buf[vertex_0[0] + cursor * WIDTH] = cursor_z;
			}
		}
		cursor += dy;
	}
}
