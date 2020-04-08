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

void	draw_model(t_system *system, t_model *model, t_coords *coords)
{
	if (system->render & 8)
	{
		fill_qmesh(system, model, coords);
		return ;
	}
	if (system->render & 4)
	{
		fill_quad(system, model, coords);
		return ;
	}
	if (system->render & 2)
	{
		draw_quad(system, model, coords);
		return ;
	}
	draw_qvertex(system, model, coords);
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

void	fill_quad(t_system *system, t_model *model, t_coords *coords)
{
	if (model->color_f && system->render & 64)
	{
		
		if (lastvert_qcolor(system, model, coords))
			return ;
		fquad_zbuf(system, model, coords);
		lastl_zbuf(system, model, coords);
		return ;
	}
	lastvert_qnocol(system, model, coords);
	fquad_nozbuf(system, model, coords);
	lastl_nozbuf(system, model, coords);
}

void	fill_qmesh(t_system *system, t_model *model, t_coords *coords)
{
	if (lastvert_qmesh(system, model, coords))
		return ;
	if (model->color_f && system->render & 64)
	{
		fqmesh_color(system, model, coords);
		if (firsthor_qmcolor(system, model, coords))
			return ;
		if (lasthor_qmcolor(system, model, coords))
			return ;
		return ;
	}
	fqmesh_nocolor(system, model, coords);
	if (firsthor_qmnocol(system, model, coords))
		return ;
	if (lasthor_qmnocol(system, model, coords))
		return ;
}

char	lastvert_qmesh(t_system *system, t_model *model, t_coords *coords)
{
	if (coords->d_quad[0][0] != coords->d_quad[2][0] ||
		coords->d_quad[0][1] != coords->d_quad[2][1] ||
		coords->d_quad[1][0] != coords->d_quad[3][0] ||
		coords->d_quad[1][1] != coords->d_quad[3][1] ||
		coords->counter[0] != model->width - 2)
		return (0);
	defline_zbuf(coords, 0, 1);
	coords->d_tris[0][2] = 0;
	coords->d_tris[1][2] = 0;
	line_zbuf(system, coords);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > system->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		system->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] = 0;
	return (1);
}

char	firsthor_qmcolor(t_system *system, t_model *model, t_coords *coords)
{
	if (coords->counter[1] != 0)
		return (0);
	defline_zbuf(coords, 0, 2);
	// coords->f_tris[2] = coords->f_line[2];
	coords->d_tris[0][2] =
		shade_color(coords->d_tris[0][2], coords->f_line[2]);
	coords->d_tris[1][2] =
		shade_color(coords->d_tris[1][2], coords->f_line[2]);
	coords->f_tris[2] = coords->f_line[2];
	line_zbuf(system, coords);
	if ((coords->counter[0] == model->width - 2) &&
		(0 <= coords->d_quad[2][0] && coords->d_quad[2][0] < WIDTH) &&
		(0 <= coords->d_quad[2][1] && coords->d_quad[2][1] < HEIGHT) &&
		((int)coords->f_quad[2][2] > system->z_buf[coords->d_quad[2][0] +
		coords->d_quad[2][1] * WIDTH]))
		system->output[coords->d_quad[2][0] +
			coords->d_quad[2][1] * WIDTH] =
			shade_color(coords->d_quad[2][2], coords->f_line[2]);
	return (1);
}

char	lasthor_qmnocol(t_system *system, t_model *model, t_coords *coords)
{
	if (coords->counter[1] != model->height - 2)
		return (0);
	defline_zbuf(coords, 1, 3);
	coords->d_tris[0][2] = shade_color(COLOR_S, coords->f_line[2]);
	coords->d_tris[1][2] = shade_color(COLOR_S, coords->f_line[2]);
	coords->f_tris[2] = coords->f_line[2];
	line_zbuf(system, coords);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > system->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		system->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] =
			shade_color(COLOR_S, coords->f_line[2]);
	return (1);
}




char	firsthor_qmnocol(t_system *system, t_model *model, t_coords *coords)
{
	if (coords->counter[1] != 0)
		return (0);
	defline_zbuf(coords, 0, 2);
	coords->d_tris[0][2] = shade_color(COLOR_S, coords->f_line[2]);
	coords->d_tris[1][2] = shade_color(COLOR_S, coords->f_line[2]);
	coords->f_tris[2] = coords->f_line[2];
	line_zbuf(system, coords);
	if ((coords->counter[0] == model->width - 2) &&
		(0 <= coords->d_quad[2][0] && coords->d_quad[2][0] < WIDTH) &&
		(0 <= coords->d_quad[2][1] && coords->d_quad[2][1] < HEIGHT) &&
		((int)coords->f_quad[2][2] > system->z_buf[coords->d_quad[2][0] +
		coords->d_quad[2][1] * WIDTH]))
		system->output[coords->d_quad[2][0] +
			coords->d_quad[2][1] * WIDTH] =
			shade_color(COLOR_S, coords->f_line[2]);
	return (1);
}



char	lasthor_qmcolor(t_system *system, t_model *model, t_coords *coords)
{
	if (coords->counter[1] != model->height - 2)
		return (0);
	defline_zbuf(coords, 1, 3);
	// coords->f_tris[2] = coords->f_line[2];
	coords->d_tris[0][2] =
		shade_color(coords->d_tris[0][2], coords->f_line[2]);
	coords->d_tris[1][2] =
		shade_color(coords->d_tris[1][2], coords->f_line[2]);
	coords->f_tris[2] = coords->f_line[2];
	line_zbuf(system, coords);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > system->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		system->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] =
			shade_color(coords->d_quad[3][2], coords->f_line[2]);
	return (1);
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

	rgb[0][0] = vertex_0[2] >> 16;
	rgb[0][1] = vertex_0[2] >> 8;
	rgb[0][2] = vertex_0[2];
	rgb[1][0] = vertex_1[2] >> 16;
	rgb[1][1] = vertex_1[2] >> 8;
	rgb[1][2] = vertex_1[2];
	d_rgb[0] = rgb[1][0] > rgb[0][0] ? 1 : -1;
	d_rgb[1] = rgb[1][1] > rgb[0][1] ? 1 : -1;
	d_rgb[2] = rgb[1][2] > rgb[0][2] ? 1 : -1;
	len[0] = abs(rgb[1][0] - rgb[0][0]);
	len[1] = abs(rgb[1][1] - rgb[0][1]);
	len[2] = abs(rgb[1][2] - rgb[0][2]);
	int_color = (float)(abs(cursor - vertex_0[0])) /
				(float)(abs(vertex_0[0] - vertex_1[0]));
	color = (lround(rgb[0][0] + len[0] * int_color * d_rgb[0]) << 16) +
			(lround(rgb[0][1] + len[1] * int_color * d_rgb[1]) << 8) +
			lround(rgb[0][2] + len[2] * int_color * d_rgb[2]);
	return (color);
}

int		set_yrgb(int *vertex_0, int *vertex_1, int cursor)
{
	unsigned char	rgb[2][3];
	char			d_rgb[3];
	unsigned char	len[3];
	float			int_color;
	int				color;

	rgb[0][0] = vertex_0[2] >> 16;
	rgb[0][1] = vertex_0[2] >> 8;
	rgb[0][2] = vertex_0[2];
	rgb[1][0] = vertex_1[2] >> 16;
	rgb[1][1] = vertex_1[2] >> 8;
	rgb[1][2] = vertex_1[2];
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

