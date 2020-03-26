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


void	draw_quad(t_system *system, t_model *model, t_coords *coords)
{
	// coords->tris_xy[0][0] = coords->d_quad[0][0];
	// coords->tris_xy[0][1] = coords->d_quad[0][1];
	// coords->tris_z[0] = coords->f_quad[0][2]
	// coords->tris_xy[1][0] = coords->d_quad[1][0];
	// coords->tris_xy[1][1] = coords->d_quad[1][1];
	// coords->tris_z[1] = coords->f_quad[1][2]
	draw_line(system, coords->d_quad[0], coords->d_quad[1], model->color_f);

	// coords->tris_xy[0][0] = coords->d_quad[0][0];
	// coords->tris_xy[0][1] = coords->d_quad[0][1];
	// coords->tris_z[0] = coords->f_quad[0][2]
	// coords->tris_xy[1][0] = coords->d_quad[1][0];
	// coords->tris_xy[1][1] = coords->d_quad[1][1];
	// coords->tris_z[1] = coords->f_quad[1][2]
	draw_line(system, coords->d_quad[0], coords->d_quad[2], model->color_f);

	// if (model->diagonal[coords->counter[0] + coords->counter[1] * (model->width - 1)])
	// 	draw_line(system, coords->d_quad[1], coords->d_quad[2], COLOR_W);
	// else
	// 	draw_line(system, coords->d_quad[0], coords->d_quad[3], COLOR_W);

	if (coords->counter[0] == model->width - 2)
		draw_line(system, coords->d_quad[2], coords->d_quad[3], model->color_f);
	if (coords->counter[1] == model->height - 2)
		draw_line(system, coords->d_quad[1], coords->d_quad[3], model->color_f);
}


void	draw_line(t_system *system, int *vertex_0, int *vertex_1, char color_f)
{
	char	d[2];
	int		len[2];
	int		overflow;
	int		coord[2];

	d[0] = vertex_1[0] < vertex_0[0] ? -1 : 1;
	d[1] = vertex_1[1] < vertex_0[1] ? -1 : 1;
	len[0] = (vertex_1[0] - vertex_0[0]) * d[0];
	len[1] = (vertex_1[1] - vertex_0[1]) * d[1];


	if (vertex_0[1] == vertex_1[1])
	{
		draw_horizontal(system, vertex_0, vertex_1, color_f);
		return ;
	}

}


void	draw_horizontal(t_system *system, int *vertex_0, int *vertex_1, char color_f)
{
	char	dx;
	int		cursor;

	if (vertex_0[1] < 0 || vertex_0[1] > HEIGHT - 1)
		return ;



	dx = vertex_1[0] < vertex_0[0] ? -1 : 1;
	cursor = vertex_0[0];

	if (color_f && system->render & 64)
	{
		while (cursor != vertex_1[0])
		{
			if (cursor >= 0 && cursor < WIDTH)
				system->output[cursor + vertex_0[1] * WIDTH] = set_colorhor(vertex_0, vertex_1, cursor);
			cursor += dx;
		}
		if (cursor >= 0 && cursor < WIDTH)
			system->output[cursor + vertex_0[1] * WIDTH] = vertex_1[2];
		return ;
	}

	while (cursor != vertex_1[0])
	{
		if (cursor >= 0 && cursor < WIDTH)
			system->output[cursor + vertex_0[1] * WIDTH] = COLOR_W;
		cursor += dx;
	}
	if (cursor >= 0 && cursor < WIDTH)
		system->output[cursor + vertex_0[1] * WIDTH] = COLOR_W;
}


int		set_colorhor(int *vertex_0, int *vertex_1, int cursor)
{

	unsigned char	color_pars[2][3];
	char			d_color[3];
	unsigned char	len[3];
	float			int_color;
	int				color;
	
	color_pars[0][0] = ((vertex_0[2] & (255 << 16)) >> 16);
	color_pars[0][1] = ((vertex_0[2] & (255 << 8)) >> 8);
	color_pars[0][2] = (vertex_0[2] & 255);
	color_pars[1][0] = ((vertex_1[2] & (255 << 16)) >> 16);
	color_pars[1][1] = ((vertex_1[2] & (255 << 8)) >> 8);
	color_pars[1][2] = (vertex_1[2] & 255);
	d_color[0] = color_pars[1][0] > color_pars[0][0] ? 1 : -1;
	d_color[1] = color_pars[1][1] > color_pars[0][1] ? 1 : -1;
	d_color[2] = color_pars[1][2] > color_pars[0][2] ? 1 : -1;
	len[0] = abs(color_pars[1][0] - color_pars[0][0]);
	len[1] = abs(color_pars[1][1] - color_pars[0][1]);
	len[2] = abs(color_pars[1][2] - color_pars[0][2]);

	int_color = (float)(abs(cursor - vertex_0[0])) /
				(float)(abs(vertex_0[0] - vertex_1[0]));

	color = ((lround(color_pars[0][0] + len[0] * int_color * d_color[0])) << 16) + ((lround(color_pars[0][1] + len[1] * int_color * d_color[1])) << 8) + ((lround(color_pars[0][2] + len[2] * int_color * d_color[2])) << 0);
	return (color);
}


























