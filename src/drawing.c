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
	if (model->color_f)
	{
		system->output[model->pos[0] + model->pos[1] * WIDTH] =
			model->vertex[model->area / 2][3];
		return (1);
	}
	if (system->render == 1)
		system->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_V;
	if (system->render == 2)
		system->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_W;
	return (1);
}



void	draw_model(t_system *system, t_model *model, t_coords *coords)
{
	if (system->render & 1)
		draw_qvertex(system, model, coords);
	if (system->render & 2)
		draw_quad(system, model, coords);

	
	// // if (system->render & 4)
	// // 	fill_quad(system, coords);
	// if (system->render & 12)
	// 	fill_qmesh(system, model, coords);
}

// void	draw_quad(t_system *system, t_model *model, t_coords *coords)
// {
// 	draw_line(system, coords->d_quad[0], coords->d_quad[1], COLOR_W);
// 	draw_line(system, coords->d_quad[0], coords->d_quad[2], COLOR_W);

// 	// if (model->diagonal[coords->counter[0] + coords->counter[1] * (model->width - 1)])
// 	// 	draw_line(system, coords->d_quad[1], coords->d_quad[2], COLOR_W);
// 	// else
// 	// 	draw_line(system, coords->d_quad[0], coords->d_quad[3], COLOR_W);


// 	if (coords->counter[0] == model->width - 2)
// 		draw_line(system, coords->d_quad[2], coords->d_quad[3], COLOR_W);
// 	if (coords->counter[1] == model->height - 2)
// 		draw_line(system, coords->d_quad[1], coords->d_quad[3], COLOR_W);
// }



// LINE UNCOMMENT




// void	draw_qvertex(t_system *system, t_model *model, t_coords *coords)
// {
// 	if (model->color_f && system->render & 64)
// 	{
// 		vert_zbuf(system, coords, 0);
// 		if (coords->counter[0] == model->width - 2)
// 			vert_zbuf(system, coords, 2);
// 		if (coords->counter[1] == model->height - 2)
// 			vert_zbuf(system, coords, 1);
// 		if (coords->index[3] == model->area - 1)
// 			vert_zbuf(system, coords, 3);
// 		return ;
// 	}
// 	vert_nozbuf(system, coords, 0);
// 	if (coords->counter[0] == model->width - 2)
// 		vert_nozbuf(system, coords, 2);
// 	if (coords->counter[1] == model->height - 2)
// 		vert_nozbuf(system, coords, 1);
// 	if (coords->index[3] == model->area - 1)
// 		vert_nozbuf(system, coords, 3);
// }





void	draw_quad(t_system *system, t_model *model, t_coords *coords)
{
	if (model->color_f && system->render & 64)
	{

		coords->tris_z[0] = coords->f_quad[0][2];
		coords->tris_z[1] = coords->f_quad[1][2];
		line_zbuf(system, coords->d_quad[0], coords->d_quad[1], coords->tris_z);

		// coords->tris_z[0] = coords->f_quad[0][2]; //MAYBE DELL
		coords->tris_z[1] = coords->f_quad[2][2];
		line_zbuf(system, coords->d_quad[0], coords->d_quad[2], coords->tris_z);

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
		((int)coords->f_quad[3][2] > system->z_buf[coords->d_quad[3][0] + coords->d_quad[3][1] * WIDTH]))
			system->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] = coords->d_quad[3][2];

		return ;
	}
	line_nozbuf(system, coords->d_quad[0], coords->d_quad[1]);
	line_nozbuf(system, coords->d_quad[0], coords->d_quad[2]);
	if (coords->counter[0] == model->width - 2)
		line_nozbuf(system, coords->d_quad[2], coords->d_quad[3]);
	if (coords->counter[1] == model->height - 2)
		line_nozbuf(system, coords->d_quad[1], coords->d_quad[3]);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT))
		system->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] = COLOR_W;
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
					system->output[cursor[0] + cursor[1] * WIDTH] = set_colorrgb(vertex_0, vertex_1, cursor[0], 0);
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
					system->output[cursor[0] + cursor[1] * WIDTH] = set_colorrgb(vertex_0, vertex_1, cursor[1], 1);
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
				system->output[cursor + vertex_0[1] * WIDTH] = set_colorrgb(vertex_0, vertex_1, cursor, 0);
				system->z_buf[cursor + vertex_0[1] * WIDTH] = cur_z;
			}
		}
		cursor += dx;
	}
	return ;
}



void	line_nozbuf(t_system *system, int *vertex_0, int *vertex_1)
{
	char	d[2];
	int		len[2];
	int		overflow;
	int		coord[2];

	// if (vertex_0[1] == vertex_1[1])
	// {
	// 	linex_nozbuf(system, vertex_0, vertex_1);
	// 	return ;
	// }

	d[0] = vertex_1[0] < vertex_0[0] ? -1 : 1;
	d[1] = vertex_1[1] < vertex_0[1] ? -1 : 1;
	len[0] = (vertex_1[0] - vertex_0[0]) * d[0];
	len[1] = (vertex_1[1] - vertex_0[1]) * d[1];
	coord[0] = vertex_0[0];
	coord[1] = vertex_0[1];
	overflow = 0;

	if (len[0] > len[1])
	{

		while (coord[0] != vertex_1[0])
		{
			if ((0 <= coord[0] && coord[0] < WIDTH)
				&& (0 <= coord[1] && coord[1] < HEIGHT))

				system->output[coord[0] + coord[1] * WIDTH] = COLOR_W;
			overflow += len[1] + 1;
			if (overflow >= len[0] + 1)
			{
				coord[1] += d[1];
				overflow -= len[0] + 1;
			}
			coord[0] += d[0];
		}
	}

	else
	{
		while (coord[1] != vertex_1[1])
		{
			if ((0 <= coord[0] && coord[0] < WIDTH)
				&& (0 <= coord[1] && coord[1] < HEIGHT))
				system->output[coord[0] + coord[1] * WIDTH] = COLOR_W;
			overflow += len[0] + 1;
			if (overflow >= len[1] + 1)
			{
				coord[0] += d[0];
				overflow -= len[1] + 1;
			}
			coord[1] += d[1];
		}
	}

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


int		set_colorrgb(int *vertex_0, int *vertex_1, int cursor, char dir)
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
	if (dir)
		int_color = (float)(abs(cursor - vertex_0[1])) /
					(float)(abs(vertex_0[1] - vertex_1[1]));
	else
		int_color = (float)(abs(cursor - vertex_0[0])) /
					(float)(abs(vertex_0[0] - vertex_1[0]));
	color = ((lround(rgb[0][0] + len[0] * int_color * d_rgb[0])) << 16) +
			((lround(rgb[0][1] + len[1] * int_color * d_rgb[1])) << 8) +
			((lround(rgb[0][2] + len[2] * int_color * d_rgb[2])) << 0);
	return (color);
}


























