/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_mesh2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 15:33:26 by student           #+#    #+#             */
/*   Updated: 2020/04/08 15:33:29 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fqmesh_nocolor(t_system *system, t_model *model, t_coords *coords)
{
	if (model->diagonal[coords->counter[0] +
		coords->counter[1] * (model->width - 1)])
	{
		set_shadetris(coords, 0, 1, 3);
		deftris_zbuf(coords, 0, 1, 3);
		ftris_zbuf(system, coords);
		if (model->vertex[coords->index[0]][2] !=
			model->vertex[coords->index[3]][2])
			set_shadetris(coords, 0, 2, 3);
		deftris_zbuf(coords, 0, 2, 3);
		ftris_zbuf(system, coords);
		return ;
	}
	set_shadetris(coords, 0, 1, 2);
	deftris_zbuf(coords, 0, 1, 2);
	ftris_zbuf(system, coords);
	if (model->vertex[coords->index[1]][2] !=
		model->vertex[coords->index[2]][2])
		set_shadetris(coords, 1, 2, 3);
	deftris_zbuf(coords, 1, 2, 3);
	ftris_zbuf(system, coords);
}

void	set_shadetris(t_coords *coords, char v0, char v1, char v2)
{
	set_light(coords, v0, v1, v2);
	shade_tris(coords);
}

void	shade_tris(t_coords *coords)
{
	unsigned char	rgb[3];

	rgb[0] = COLOR_S >> 16;
	rgb[1] = COLOR_S >> 8;
	rgb[2] = (char)COLOR_S;
	coords->d_line[1][2] = (lround(coords->f_line[2] * rgb[0]) << 16) +
							(lround(coords->f_line[2] * rgb[1]) << 8) +
							lround(coords->f_line[2] * rgb[2]);
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
	unsigned char	rgb[3];

	rgb[0] = color >> 16;
	rgb[1] = color >> 8;
	rgb[2] = color;
	color = (lround(light * rgb[0]) << 16) +
			(lround(light * rgb[1]) << 8) +
			lround(light * rgb[2]);
	return (color);
}
