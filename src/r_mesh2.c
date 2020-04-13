/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_mesh2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 15:33:26 by student           #+#    #+#             */
/*   Updated: 2020/04/10 16:53:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fqmesh_color(t_sys *sys, t_model *model, t_coords *coords)
{
	if (model->diagonal[coords->counter[0] +
		coords->counter[1] * (model->width - 1)])
	{
		set_light(coords, 0, 1, 3);
		deftris_zbuf(coords, 0, 1, 3);
		shade_vtris(coords);
		ftris_zbuf(sys, coords);
		if (model->vertex[coords->index[0]][2] !=
			model->vertex[coords->index[3]][2])
			set_light(coords, 0, 2, 3);
		deftris_zbuf(coords, 0, 2, 3);
		shade_vtris(coords);
		ftris_zbuf(sys, coords);
		return ;
	}
	set_light(coords, 0, 1, 2);
	deftris_zbuf(coords, 0, 1, 2);
	shade_vtris(coords);
	ftris_zbuf(sys, coords);
	if (model->vertex[coords->index[1]][2] !=
		model->vertex[coords->index[2]][2])
		set_light(coords, 1, 2, 3);
	deftris_zbuf(coords, 1, 2, 3);
	shade_vtris(coords);
	ftris_zbuf(sys, coords);
}

void	shade_vtris(t_coords *coords)
{
	coords->d_tris[0][2] =
		shade_color(coords->d_tris[0][2], coords->f_line[2]);
	coords->d_tris[1][2] =
		shade_color(coords->d_tris[1][2], coords->f_line[2]);
	coords->d_tris[2][2] =
		shade_color(coords->d_tris[2][2], coords->f_line[2]);
}

int		shade_color(int color, float light)
{
	unsigned char	*chanal;

	chanal = (unsigned char *)&color;
	chanal[0] = lround(light * chanal[0]);
	chanal[1] = lround(light * chanal[1]);
	chanal[2] = lround(light * chanal[2]);
	return (color);
}

int		set_xrgb(int *vertex_0, int *vertex_1, int cursor)
{
	unsigned char	*rgb[2];
	char			d_rgb[3];
	unsigned char	len[3];
	float			int_color;
	int				color;

	rgb[0] = (unsigned char *)&vertex_0[2];
	rgb[1] = (unsigned char *)&vertex_1[2];
	d_rgb[0] = rgb[1][0] > rgb[0][0] ? 1 : -1;
	d_rgb[1] = rgb[1][1] > rgb[0][1] ? 1 : -1;
	d_rgb[2] = rgb[1][2] > rgb[0][2] ? 1 : -1;
	len[0] = abs(rgb[1][0] - rgb[0][0]);
	len[1] = abs(rgb[1][1] - rgb[0][1]);
	len[2] = abs(rgb[1][2] - rgb[0][2]);
	int_color = (float)(abs(cursor - vertex_0[0])) /
				(float)(abs(vertex_0[0] - vertex_1[0]));
	color = (lround(rgb[0][0] + len[0] * int_color * d_rgb[0])) +
			(lround(rgb[0][1] + len[1] * int_color * d_rgb[1]) << 8) +
			(lround(rgb[0][2] + len[2] * int_color * d_rgb[2]) << 16);
	return (color);
}

int		set_yrgb(int *vertex_0, int *vertex_1, int cursor)
{
	unsigned char	*rgb[2];
	char			d_rgb[3];
	unsigned char	len[3];
	float			int_color;
	int				color;

	rgb[0] = (unsigned char *)&vertex_0[2];
	rgb[1] = (unsigned char *)&vertex_1[2];
	d_rgb[0] = rgb[1][0] > rgb[0][0] ? 1 : -1;
	d_rgb[1] = rgb[1][1] > rgb[0][1] ? 1 : -1;
	d_rgb[2] = rgb[1][2] > rgb[0][2] ? 1 : -1;
	len[0] = abs(rgb[1][0] - rgb[0][0]);
	len[1] = abs(rgb[1][1] - rgb[0][1]);
	len[2] = abs(rgb[1][2] - rgb[0][2]);
	int_color = (float)(abs(cursor - vertex_0[1])) /
				(float)(abs(vertex_0[1] - vertex_1[1]));
	color = (lround(rgb[0][0] + len[0] * int_color * d_rgb[0])) +
			(lround(rgb[0][1] + len[1] * int_color * d_rgb[1]) << 8) +
			(lround(rgb[0][2] + len[2] * int_color * d_rgb[2]) << 16);
	return (color);
}
