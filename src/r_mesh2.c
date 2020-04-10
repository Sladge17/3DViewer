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
