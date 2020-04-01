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
		fill_quad(system, model, coords);
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




void	fill_quad(t_system *system, t_model *model, t_coords *coords)
{
	if (model->color_f && system->render & 64)
	{
		fquad_zbuf(system, model, coords);
		
		if (coords->counter[1] == 0)
		{
			defline_zbuf(coords, 0, 2);
			line_zbuf(system, coords);
			if ((coords->counter[0] == model->width - 2) &&
				(0 <= coords->d_quad[2][0] && coords->d_quad[2][0] < WIDTH) &&
				(0 <= coords->d_quad[2][1] && coords->d_quad[2][1] < HEIGHT) &&
				((int)coords->f_quad[2][2] > system->z_buf[coords->d_quad[2][0] +
				coords->d_quad[2][1] * WIDTH]))
				system->output[coords->d_quad[2][0] +
					coords->d_quad[2][1] * WIDTH] = coords->d_quad[3][2];
		}



		if (coords->counter[1] == model->height - 2)
		{
			defline_zbuf(coords, 1, 3);
			line_zbuf(system, coords);
			if ((coords->index[3] == model->area - 1) &&
				(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
				(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
				((int)coords->f_quad[3][2] > system->z_buf[coords->d_quad[3][0] +
				coords->d_quad[3][1] * WIDTH]))
				system->output[coords->d_quad[3][0] +
					coords->d_quad[3][1] * WIDTH] = coords->d_quad[3][2];
		}
		return ;
	}
	fquad_nozbuf(system, model, coords);
	if (coords->counter[1] == 0)
	{
		defline_nozbuf(coords, 0, 2);
		line_nozbuf(system, coords);
		if ((coords->counter[0] == model->width - 2) &&
			(0 <= coords->d_quad[2][0] && coords->d_quad[2][0] < WIDTH) &&
			(0 <= coords->d_quad[2][1] && coords->d_quad[2][1] < HEIGHT))
			system->output[coords->d_quad[2][0] +
				coords->d_quad[2][1] * WIDTH] = COLOR_S;
	}



	if (coords->counter[1] == model->height - 2)
	{
		defline_nozbuf(coords, 1, 3);
		line_nozbuf(system, coords);
		if ((coords->index[3] == model->area - 1) &&
			(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
			(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT))
			system->output[coords->d_quad[3][0] +
				coords->d_quad[3][1] * WIDTH] = COLOR_S;
	}
	
}


void	fquad_zbuf(t_system *system, t_model *model, t_coords *coords)
{
	if ((coords->d_quad[0][0] == coords->d_quad[1][0] &&
		coords->d_quad[1][0] == coords->d_quad[2][0] &&
		coords->d_quad[2][0] == coords->d_quad[3][0]) ||
		(coords->d_quad[0][1] == coords->d_quad[1][1] &&
		coords->d_quad[1][1] == coords->d_quad[2][1] &&
		coords->d_quad[2][1] == coords->d_quad[3][1]))
	{
		quad_zbuf(system, model, coords);
		return ;
	}
	if (model->diagonal[coords->counter[0] + coords->counter[1] * (model->width - 1)])
	{
		
		deftris_zbuf(coords, 0, 1, 3);
		ftris_zbuf(system, coords);
		deftris_zbuf(coords, 0, 2, 3);
		ftris_zbuf(system, coords);

		// // if (coords->counter[1] == model->height - 2)
		// // {
			
		// 	coords->d_tris[0][0] = coords->d_tris[1][0];
		// 	coords->d_tris[0][1] = coords->d_tris[1][1];
		// 	coords->d_tris[0][2] = 0xFF;
		// 	coords->f_tris[0] = coords->f_tris[1];

		// 	coords->d_tris[1][0] = coords->d_tris[2][0];
		// 	coords->d_tris[1][1] = coords->d_tris[2][1];
		// 	coords->d_tris[1][2] = 0xFF;
		// 	coords->f_tris[1] = coords->f_tris[2];

		// // // defline_zbuf(coords, 1, 3);
		// line_zbuf(system, coords);
		// // }

		return ;
	}

	deftris_zbuf(coords, 0, 1, 2);
	ftris_zbuf(system, coords);
	deftris_zbuf(coords, 1, 2, 3);
	ftris_zbuf(system, coords);

	
	// // if (coords->counter[1] == model->height - 2)
	// // {
	// 	coords->d_tris[0][0] = coords->d_tris[1][0];
	// 	coords->d_tris[0][1] = coords->d_tris[1][1];
	// 	coords->d_tris[0][2] = 0xFF;
	// 	coords->f_tris[0] = coords->f_tris[1];

	// 	coords->d_tris[1][0] = coords->d_tris[2][0];
	// 	coords->d_tris[1][1] = coords->d_tris[2][1];
	// 	coords->d_tris[1][2] = 0xFF;
	// 	coords->f_tris[1] = coords->f_tris[2];
	// // // defline_zbuf(coords, 1, 3);
	// line_zbuf(system, coords);
	// // }

}

void	deftris_zbuf(t_coords *coords, char v1, char v2, char v3)
{
	coords->d_tris[0][0] = coords->d_quad[v1][0];
	coords->d_tris[0][1] = coords->d_quad[v1][1];
	coords->d_tris[0][2] = coords->d_quad[v1][2];
	coords->f_tris[0] = coords->f_quad[v1][2];
	coords->d_tris[1][0] = coords->d_quad[v2][0];
	coords->d_tris[1][1] = coords->d_quad[v2][1];
	coords->d_tris[1][2] = coords->d_quad[v2][2];
	coords->f_tris[1] = coords->f_quad[v2][2];
	coords->d_tris[2][0] = coords->d_quad[v3][0];
	coords->d_tris[2][1] = coords->d_quad[v3][1];
	coords->d_tris[2][2] = coords->d_quad[v3][2];
	coords->f_tris[2] = coords->f_quad[v3][2];
}

void	ftris_zbuf(t_system *system, t_coords *coords)	
{
	int		segment_height;
	int		total_height;
	int		i;
	float	int_x1;
	float	int_x2;
	int		cursor_y;
	int		cursor_x1;
	int		cursor_x2;

	int		color_1;
	int		color_2;

	int		vertex_0[3];
	int		vertex_1[3];

	float	z1;
	float	z2;
	float	cur_z[2];

	sorty_zbuf(coords);


	total_height = coords->d_tris[2][1] - coords->d_tris[0][1];
	cursor_y = coords->d_tris[0][1];

	// i = 0;

	// if (coords->d_tris[0][1] == coords->d_tris[1][1])
	// 	i = 1;

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

			color_1 = set_yrgb(coords->d_tris[0], coords->d_tris[2], cursor_y);
			color_2 = set_yrgb(coords->d_tris[i], coords->d_tris[i + 1], cursor_y);

			z1 = coords->f_tris[0] + (coords->f_tris[2] - coords->f_tris[0]) * int_x1;
			z2 = coords->f_tris[i] + (coords->f_tris[i + 1] - coords->f_tris[i]) * int_x2;

			vertex_0[0] = cursor_x1;
			vertex_0[1] = cursor_y;
			vertex_0[2] = color_1;

			vertex_1[0] = cursor_x2;
			vertex_1[1] = cursor_y;
			vertex_1[2] = color_2;

			cur_z[0] = z1;
			cur_z[1] = z2;


			linex_zbuf(system, vertex_0, vertex_1, cur_z);

			if ((0 <= vertex_1[0] && vertex_1[0] < WIDTH) &&
				(0 <= vertex_1[1] && vertex_1[1] < HEIGHT) &&
				(int)cur_z[1] > system->z_buf[vertex_1[0] + vertex_1[1] * WIDTH])
			{
				system->output[vertex_1[0] +
				vertex_1[1] * WIDTH] = vertex_1[2];
				system->z_buf[vertex_1[0] + vertex_1[1] * WIDTH] = (int)cur_z[1];
			}



			cursor_y += 1;
		}
		if (coords->d_tris[1][1] == coords->d_tris[2][1])
			break ;
		i += 1;
	}
}

void	sorty_zbuf(t_coords *coords)
{
	int		i;
	int		j;
	int		tmp_d;
	float	tmp_f;

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
				tmp_d = coords->d_tris[i][2];
				coords->d_tris[i][2] = coords->d_tris[i + 1][2];
				coords->d_tris[i + 1][2] = tmp_d;
				tmp_f = coords->f_tris[i];
				coords->f_tris[i] = coords->f_tris[i + 1];
				coords->f_tris[i + 1] = tmp_f;
			}
			i += 1;
		}
		j += 1;
	}
}



void	fquad_nozbuf(t_system *system, t_model *model, t_coords *coords)
{
	// quad_nozbuf(system, model, coords);
	// if ((coords->d_quad[0][0] == coords->d_quad[1][0] &&
	// 	coords->d_quad[1][0] == coords->d_quad[2][0] &&
	// 	coords->d_quad[2][0] == coords->d_quad[3][0]) ||
	// 	(coords->d_quad[0][1] == coords->d_quad[1][1] &&
	// 	coords->d_quad[1][1] == coords->d_quad[2][1] &&
	// 	coords->d_quad[2][1] == coords->d_quad[3][1]))
	// 	return ;
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

		// if (coords->counter[1] == model->height - 2)
		// {
		// 	defline_nozbuf(coords, 1, 3);
		// 	line_nozbuf(system, coords);
		// }

		// if ((coords->index[3] == model->area - 1) &&
		// 	(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		// 	(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT))
		// 	system->output[coords->d_quad[3][0] +
		// 		// coords->d_quad[3][1] * WIDTH] = COLOR_W;
		// 		coords->d_quad[3][1] * WIDTH] = 0xFF00;

		

		// if ((coords->index[3] == model->area - 1) &&
		// 	(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		// 	(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT))
		// {
		// 	defline_nozbuf(coords, 1, 3);
		// 	line_nozbuf(system, coords);
		// 	system->output[coords->d_quad[3][0] +
		// 		coords->d_quad[3][1] * WIDTH] = COLOR_S;
		// }
		return ;
	}

	defline_nozbuf(coords, 1, 2);
	line_nozbuf(system, coords);

	deftris_nozbuf(coords, 0, 1, 2);
	ftris_nozbuf(system, coords);
	deftris_nozbuf(coords, 1, 2, 3);
	ftris_nozbuf(system, coords);



	// if (coords->counter[1] == model->height - 2)
	// 	{
	// 		defline_nozbuf(coords, 1, 3);
	// 		line_nozbuf(system, coords);
	// 	}

	// if ((coords->index[3] == model->area - 1) &&
	// 	(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
	// 	(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT))
	// 	system->output[coords->d_quad[3][0] +
	// 		// coords->d_quad[3][1] * WIDTH] = COLOR_W;
	// 		coords->d_quad[3][1] * WIDTH] = 0xFF00;

	// if ((coords->index[3] == model->area - 1) &&
	// 	(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
	// 	(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT))
	// {
	// 	defline_nozbuf(coords, 1, 3);
	// 	line_nozbuf(system, coords);
	// 	system->output[coords->d_quad[3][0] +
	// 		coords->d_quad[3][1] * WIDTH] = COLOR_S;
	// }
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
				vertex_1[1] * WIDTH] = COLOR_W;

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



void	draw_quad(t_system *system, t_model *model, t_coords *coords)
{
	if (model->color_f && system->render & 64)
	{
		quad_zbuf(system, model, coords);
		return ;
	}
	quad_nozbuf(system, model, coords);
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

