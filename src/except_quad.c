/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   except_quad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 11:45:49 by student           #+#    #+#             */
/*   Updated: 2020/04/10 16:53:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	lastvert_qcolor(t_sys *sys, t_model *model, t_coords *coords)
{
	if (coords->d_quad[0][0] != coords->d_quad[2][0] ||
		coords->d_quad[0][1] != coords->d_quad[2][1] ||
		coords->d_quad[1][0] != coords->d_quad[3][0] ||
		coords->d_quad[1][1] != coords->d_quad[3][1] ||
		coords->counter[0] != model->width - 2)
		return (0);
	defline_zbuf(coords, 0, 1);
	line_zbuf(sys, coords);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > sys->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		sys->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] = coords->d_quad[3][2];
	return (1);
}

void	lastl_zbuf(t_sys *sys, t_model *model, t_coords *coords)
{
	if (coords->counter[1] == 0)
	{
		defline_zbuf(coords, 0, 2);
		line_zbuf(sys, coords);
		if ((coords->counter[0] == model->width - 2) &&
			(0 <= coords->d_quad[2][0] && coords->d_quad[2][0] < WIDTH) &&
			(0 <= coords->d_quad[2][1] && coords->d_quad[2][1] < HEIGHT) &&
			((int)coords->f_quad[2][2] > sys->z_buf[coords->d_quad[2][0] +
			coords->d_quad[2][1] * WIDTH]))
			sys->output[coords->d_quad[2][0] +
				coords->d_quad[2][1] * WIDTH] = coords->d_quad[3][2];
		return ;
	}
	if (coords->counter[1] == model->height - 2)
	{
		defline_zbuf(coords, 1, 3);
		line_zbuf(sys, coords);
		if ((coords->index[3] == model->area - 1) &&
			(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
			(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
			((int)coords->f_quad[3][2] > sys->z_buf[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH]))
			sys->output[coords->d_quad[3][0] +
				coords->d_quad[3][1] * WIDTH] = coords->d_quad[3][2];
	}
}

void	lastvert_qnocol(t_sys *sys, t_model *model, t_coords *coords)
{
	if (coords->d_quad[0][0] == coords->d_quad[2][0] &&
		coords->d_quad[0][1] == coords->d_quad[2][1] &&
		coords->d_quad[1][0] == coords->d_quad[3][0] &&
		coords->d_quad[1][1] == coords->d_quad[3][1] &&
		coords->counter[0] == model->width - 2)
		return ;
	defline_nozbuf(coords, 0, 1);
	line_nozbuf(sys, coords);
	if ((coords->index[3] == model->area - 1) &&
		(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
		(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT) &&
		((int)coords->f_quad[3][2] > sys->z_buf[coords->d_quad[3][0] +
		coords->d_quad[3][1] * WIDTH]))
		sys->output[coords->d_quad[3][0] +
			coords->d_quad[3][1] * WIDTH] = COLOR_S;
}

void	lastl_nozbuf(t_sys *sys, t_model *model, t_coords *coords)
{
	if (coords->counter[1] == 0)
	{
		defline_nozbuf(coords, 0, 2);
		line_nozbuf(sys, coords);
		if ((coords->counter[0] == model->width - 2) &&
			(0 <= coords->d_quad[2][0] && coords->d_quad[2][0] < WIDTH) &&
			(0 <= coords->d_quad[2][1] && coords->d_quad[2][1] < HEIGHT))
			sys->output[coords->d_quad[2][0] +
				coords->d_quad[2][1] * WIDTH] = COLOR_S;
		return ;
	}
	if (coords->counter[1] == model->height - 2)
	{
		defline_nozbuf(coords, 1, 3);
		line_nozbuf(sys, coords);
		if ((coords->index[3] == model->area - 1) &&
			(0 <= coords->d_quad[3][0] && coords->d_quad[3][0] < WIDTH) &&
			(0 <= coords->d_quad[3][1] && coords->d_quad[3][1] < HEIGHT))
			sys->output[coords->d_quad[3][0] +
				coords->d_quad[3][1] * WIDTH] = COLOR_S;
	}
}

char	check_zbuf(t_sys *sys, t_coords *coords, int *cursor, char dir)
{
	float	int_z;
	float	cursor_z;

	int_z = (float)(abs(cursor[dir] - coords->d_tris[0][dir])) /
		(float)(abs(coords->d_tris[1][dir] - coords->d_tris[0][dir]));
	cursor_z = coords->f_tris[0] +
		(coords->f_tris[1] - coords->f_tris[0]) * int_z;
	if (cursor_z > sys->z_buf[cursor[0] + cursor[1] * WIDTH])
	{
		sys->z_buf[cursor[0] + cursor[1] * WIDTH] = cursor_z;
		return (1);
	}
	return (0);
}
