/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:34:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/11 12:55:35 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	draw_zeroscale(t_system *system, t_model *model)
{
	if (model->scale)
		return (0);
	if (model->color_f && system->render & 64)
	{
		system->output[model->pos[0] + model->pos[1] * WIDTH] =
			model->vertex[model->area / 2][3];
		return (1);
	}
	if (system->render & 12)
	{
		system->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_S;
		return (1);
	}
		if (system->render & 2)
	{
		system->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_W;
		return (1);
	}
	system->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_V;
	return (1);
}



void	draw_model(t_system *system, t_model *model, t_coords *coords)
{
	if (system->render & 8)
	{
		return ;
	}
	if (system->render & 4)
	{
		return ;
	}
	if (system->render & 2)
	{
		draw_quad(system, model, coords);
		return ;
	}
	draw_qvertex(system, model, coords);
	// if (system->render & 1)
	// {
	// 	draw_qvertex(system, model, coords);
	// 	return ;
	// }
}


void	draw_quad(t_system *system, t_model *model, t_coords *coords)
{
	if (model->color_f && system->render & 64)
	{
		quad_zbuf(system, model, coords);
		return ;
	}
	quad_nozbuf(system, model, coords);
}


void	linex_zbuf(t_system *system, int *vertex_0, int *vertex_1, float *tris_z)
{
	char	dx;
	int		cursor;
	float	int_z;
	float	cur_z;

	if (vertex_0[1] < 0 || vertex_0[1] > HEIGHT - 1)
		return ;
	dx = vertex_1[0] < vertex_0[0] ? -1 : 1;
	cursor = vertex_0[0];

	

	while (cursor != vertex_1[0])
	{
		if (cursor >= 0 && cursor < WIDTH)
		{
			int_z = (float)(abs(cursor - vertex_0[0])) / (float)(abs(vertex_1[0] - vertex_0[0]));

			cur_z = tris_z[0] + (tris_z[1] - tris_z[0]) * int_z;
			if (cur_z >= system->z_buf[cursor + vertex_0[1] * WIDTH])
			{
				system->output[cursor + vertex_0[1] * WIDTH] = set_xrgb(vertex_0, vertex_1, cursor);
				system->z_buf[cursor + vertex_0[1] * WIDTH] = cur_z;
			}
		}
		cursor += dx;
	}
	return ;
}

void	linex_nozbuf(t_system *system, int *vertex_0, int *vertex_1)
{
	char	dx;
	int		cursor;

	if (vertex_0[1] < 0 || vertex_0[1] > HEIGHT - 1)
		return ;
	dx = vertex_1[0] < vertex_0[0] ? -1 : 1;
	cursor = vertex_0[0];
	while (cursor != vertex_1[0])
	{
		if (cursor >= 0 && cursor < WIDTH)
			system->output[cursor + vertex_0[1] * WIDTH] = COLOR_W;
		cursor += dx;
	}
	// if (cursor >= 0 && cursor < WIDTH)
	// 	system->output[cursor + vertex_0[1] * WIDTH] = COLOR_W;
}

char	check_zbuf(t_system *system, t_coords *coords, int *cursor, char dir)
{

	float	int_z;
	float	cursor_z;

	int_z = (float)(abs(cursor[dir] - coords->d_tris[0][dir])) /
		(float)(abs(coords->d_tris[1][dir] - coords->d_tris[0][dir]));	
	cursor_z = coords->f_tris[0] +
		(coords->f_tris[1] - coords->f_tris[0]) * int_z;
	if (cursor_z > system->z_buf[cursor[0] + cursor[1] * WIDTH])
	{
		system->z_buf[cursor[0] + cursor[1] * WIDTH] = cursor_z;
		return (1);
	}
	return (0);
}

int		set_xrgb(int *vertex_0, int *vertex_1, int cursor)
{
	unsigned char	rgb[2][3];
	char			d_rgb[3];
	unsigned char	len[3];
	float			int_color;
	int				color;
	
	rgb[0][0] = ((vertex_0[2] & (255 << 16)) >> 16);
	rgb[0][1] = ((vertex_0[2] & (255 << 8)) >> 8);
	rgb[0][2] = (vertex_0[2] & 255);
	rgb[1][0] = ((vertex_1[2] & (255 << 16)) >> 16);
	rgb[1][1] = ((vertex_1[2] & (255 << 8)) >> 8);
	rgb[1][2] = (vertex_1[2] & 255);
	d_rgb[0] = rgb[1][0] > rgb[0][0] ? 1 : -1;
	d_rgb[1] = rgb[1][1] > rgb[0][1] ? 1 : -1;
	d_rgb[2] = rgb[1][2] > rgb[0][2] ? 1 : -1;
	len[0] = abs(rgb[1][0] - rgb[0][0]);
	len[1] = abs(rgb[1][1] - rgb[0][1]);
	len[2] = abs(rgb[1][2] - rgb[0][2]);
	int_color = (float)(abs(cursor - vertex_0[0])) /
				(float)(abs(vertex_0[0] - vertex_1[0]));
	color = ((lround(rgb[0][0] + len[0] * int_color * d_rgb[0])) << 16) +
			((lround(rgb[0][1] + len[1] * int_color * d_rgb[1])) << 8) +
			((lround(rgb[0][2] + len[2] * int_color * d_rgb[2])) << 0);
	return (color);
}

int		set_yrgb(int *vertex_0, int *vertex_1, int cursor)
{
	unsigned char	rgb[2][3];
	char			d_rgb[3];
	unsigned char	len[3];
	float			int_color;
	int				color;
	
	rgb[0][0] = ((vertex_0[2] & (255 << 16)) >> 16);
	rgb[0][1] = ((vertex_0[2] & (255 << 8)) >> 8);
	rgb[0][2] = (vertex_0[2] & 255);
	rgb[1][0] = ((vertex_1[2] & (255 << 16)) >> 16);
	rgb[1][1] = ((vertex_1[2] & (255 << 8)) >> 8);
	rgb[1][2] = (vertex_1[2] & 255);
	d_rgb[0] = rgb[1][0] > rgb[0][0] ? 1 : -1;
	d_rgb[1] = rgb[1][1] > rgb[0][1] ? 1 : -1;
	d_rgb[2] = rgb[1][2] > rgb[0][2] ? 1 : -1;
	len[0] = abs(rgb[1][0] - rgb[0][0]);
	len[1] = abs(rgb[1][1] - rgb[0][1]);
	len[2] = abs(rgb[1][2] - rgb[0][2]);
	int_color = (float)(abs(cursor - vertex_0[1])) /
				(float)(abs(vertex_0[1] - vertex_1[1]));
	color = ((lround(rgb[0][0] + len[0] * int_color * d_rgb[0])) << 16) +
			((lround(rgb[0][1] + len[1] * int_color * d_rgb[1])) << 8) +
			((lround(rgb[0][2] + len[2] * int_color * d_rgb[2])) << 0);
	return (color);
}

