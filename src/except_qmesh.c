/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   except_qmesh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:03:57 by student           #+#    #+#             */
/*   Updated: 2020/04/10 16:53:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	lastvert_qmesh(t_sys *sys, t_model *model, t_coords *coords)
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
	line_zbuf(sys, coords);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > sys->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		sys->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] = 0;
	return (1);
}

char	firsthor_qmcolor(t_sys *sys, t_model *model, t_coords *coords)
{
	if (coords->counter[1] != 0)
		return (0);
	defline_zbuf(coords, 0, 2);
	coords->d_tris[0][2] =
		shade_color(coords->d_tris[0][2], coords->f_line[2]);
	coords->d_tris[1][2] =
		shade_color(coords->d_tris[1][2], coords->f_line[2]);
	coords->f_tris[2] = coords->f_line[2];
	line_zbuf(sys, coords);
	if ((coords->counter[0] == model->width - 2) &&
		(0 <= coords->d_quad[2][0] && coords->d_quad[2][0] < WIDTH) &&
		(0 <= coords->d_quad[2][1] && coords->d_quad[2][1] < HEIGHT) &&
		((int)coords->f_quad[2][2] > sys->z_buf[coords->d_quad[2][0] +
		coords->d_quad[2][1] * WIDTH]))
		sys->output[coords->d_quad[2][0] +
			coords->d_quad[2][1] * WIDTH] =
			shade_color(coords->d_quad[2][2], coords->f_line[2]);
	return (1);
}

char	lasthor_qmcolor(t_sys *sys, t_model *model, t_coords *coords)
{
	if (coords->counter[1] != model->height - 2)
		return (0);
	defline_zbuf(coords, 1, 3);
	coords->d_tris[0][2] =
		shade_color(coords->d_tris[0][2], coords->f_line[2]);
	coords->d_tris[1][2] =
		shade_color(coords->d_tris[1][2], coords->f_line[2]);
	coords->f_tris[2] = coords->f_line[2];
	line_zbuf(sys, coords);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > sys->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		sys->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] =
			shade_color(coords->d_quad[3][2], coords->f_line[2]);
	return (1);
}

char	firsthor_qmnocol(t_sys *sys, t_model *model, t_coords *coords)
{
	if (coords->counter[1] != 0)
		return (0);
	defline_zbuf(coords, 0, 2);
	coords->d_tris[0][2] = shade_color(COLOR_S, coords->f_line[2]);
	coords->d_tris[1][2] = shade_color(COLOR_S, coords->f_line[2]);
	coords->f_tris[2] = coords->f_line[2];
	line_zbuf(sys, coords);
	if ((coords->counter[0] == model->width - 2) &&
		(0 <= coords->d_quad[2][0] && coords->d_quad[2][0] < WIDTH) &&
		(0 <= coords->d_quad[2][1] && coords->d_quad[2][1] < HEIGHT) &&
		((int)coords->f_quad[2][2] > sys->z_buf[coords->d_quad[2][0] +
		coords->d_quad[2][1] * WIDTH]))
		sys->output[coords->d_quad[2][0] +
			coords->d_quad[2][1] * WIDTH] =
			shade_color(COLOR_S, coords->f_line[2]);
	return (1);
}

char	lasthor_qmnocol(t_sys *sys, t_model *model, t_coords *coords)
{
	if (coords->counter[1] != model->height - 2)
		return (0);
	defline_zbuf(coords, 1, 3);
	coords->d_tris[0][2] = shade_color(COLOR_S, coords->f_line[2]);
	coords->d_tris[1][2] = shade_color(COLOR_S, coords->f_line[2]);
	coords->f_tris[2] = coords->f_line[2];
	line_zbuf(sys, coords);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > sys->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		sys->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] =
			shade_color(COLOR_S, coords->f_line[2]);
	return (1);
}
