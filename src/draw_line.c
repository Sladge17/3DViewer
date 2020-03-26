/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:52:04 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/12 15:45:00 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_system *system, int *vertex_0, int *vertex_1, int color)
{
	int		len[2];
	char	d[2];

	if (vertex_0[0] == vertex_1[0] && vertex_0[1] == vertex_1[1]
		&& (0 <= vertex_0[0] && vertex_0[0] <= WIDTH)
		&& (0 <= vertex_0[1] && vertex_0[1] <= HEIGHT))
	{
		system->output[vertex_0[0] + vertex_0[1] * WIDTH] = color;
		return ;
	}
	d[0] = vertex_1[0] < vertex_0[0] ? -1 : 1;
	d[1] = vertex_1[1] < vertex_0[1] ? -1 : 1;
	len[0] = (vertex_1[0] - vertex_0[0]) * d[0];
	len[1] = (vertex_1[1] - vertex_0[1]) * d[1];
	if (len[0] > len[1])
		x_more_y(system, vertex_0, vertex_1, color);
	else
		y_more_x(system, vertex_0, vertex_1, color);
	if ((0 <= vertex_1[0] && vertex_1[0] <= WIDTH)
		&& (0 <= vertex_1[1] && vertex_1[1] <= HEIGHT))
		system->output[vertex_1[0] + vertex_1[1] * WIDTH] = color;
}

void	x_more_y(t_system *system, int *vertex_0, int *vertex_1, int color)
{
	int		len[2];
	int		overflow;
	int		coord[2];
	char	d[2];

	d[0] = vertex_1[0] < vertex_0[0] ? -1 : 1;
	d[1] = vertex_1[1] < vertex_0[1] ? -1 : 1;
	len[0] = (vertex_1[0] - vertex_0[0]) * d[0];
	len[1] = (vertex_1[1] - vertex_0[1]) * d[1];
	coord[0] = vertex_0[0];
	coord[1] = vertex_0[1];
	overflow = 0;
	while (coord[0] != vertex_1[0])
	{
		if ((0 <= coord[0] && coord[0] < WIDTH)
			&& (0 <= coord[1] && coord[1] <= HEIGHT))
			system->output[coord[0] + coord[1] * WIDTH] = color;
		overflow += len[1] + 1;
		if (overflow >= len[0] + 1)
		{
			coord[1] += d[1];
			overflow -= len[0] + 1;
		}
		coord[0] += d[0];
	}
}

void	y_more_x(t_system *system, int *vertex_0, int *vertex_1, int color)
{
	int		len[2];
	int		overflow;
	int		coord[2];
	char	d[2];

	d[0] = vertex_1[0] < vertex_0[0] ? -1 : 1;
	d[1] = vertex_1[1] < vertex_0[1] ? -1 : 1;
	len[0] = (vertex_1[0] - vertex_0[0]) * d[0];
	len[1] = (vertex_1[1] - vertex_0[1]) * d[1];
	coord[0] = vertex_0[0];
	coord[1] = vertex_0[1];
	overflow = 0;
	while (coord[1] != vertex_1[1])
	{
		if ((0 <= coord[0] && coord[0] < WIDTH)
			&& (0 <= coord[1] && coord[1] <= HEIGHT))
			system->output[coord[0] + coord[1] * WIDTH] = color;
		overflow += len[0] + 1;
		if (overflow >= len[1] + 1)
		{
			coord[0] += d[0];
			overflow -= len[1] + 1;
		}
		coord[1] += d[1];
	}
}

int		set_diffuse(int *vertex_0, int *vertex_1, int *coord)
{

	unsigned char	color_pars[2][3];
	char			d_color[3];
	unsigned char	len[3];
	float			int_color;
	int				diffuse;
	
	color_pars[0][0] = ((vertex_0[3] & (255 << 16)) >> 16);
	color_pars[0][1] = ((vertex_0[3] & (255 << 8)) >> 8);
	color_pars[0][2] = (vertex_0[3] & 255);
	color_pars[1][0] = ((vertex_1[3] & (255 << 16)) >> 16);
	color_pars[1][1] = ((vertex_1[3] & (255 << 8)) >> 8);
	color_pars[1][2] = (vertex_1[3] & 255);
	d_color[0] = color_pars[1][0] > color_pars[0][0] ? 1 : -1;
	d_color[1] = color_pars[1][1] > color_pars[0][1] ? 1 : -1;
	d_color[2] = color_pars[1][2] > color_pars[0][2] ? 1 : -1;
	len[0] = color_pars[1][0] - color_pars[0][0] * d_color[0];
	len[1] = color_pars[1][1] - color_pars[0][1] * d_color[1];
	len[2] = color_pars[1][2] - color_pars[0][2] * d_color[2];
	int_color = (float)(abs(coord[1] - vertex_0[1])) /
				(float)(abs(vertex_0[1] - vertex_1[1]));
	diffuse = ((lround(color_pars[0][0] + len[0] * int_color * d_color[0])) << 16) +
			((lround(color_pars[0][1] + len[1] * int_color * d_color[1])) << 8) +
			((lround(color_pars[0][2] + len[2] * int_color * d_color[2])) << 0);
	return (diffuse);
}
