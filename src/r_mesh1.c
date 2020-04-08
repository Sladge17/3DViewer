/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_mesh1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:38:40 by student           #+#    #+#             */
/*   Updated: 2020/04/01 12:38:51 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (model->diagonal[coords->counter[0] +
		coords->counter[1] * (model->width - 1)])
	{
		deftris_zbuf(coords, 0, 1, 3);
		ftris_zbuf(system, coords);
		deftris_zbuf(coords, 0, 2, 3);
		ftris_zbuf(system, coords);
		return ;
	}
	deftris_zbuf(coords, 0, 1, 2);
	ftris_zbuf(system, coords);
	deftris_zbuf(coords, 1, 2, 3);
	ftris_zbuf(system, coords);
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

void	fqmesh_color(t_system *system, t_model *model, t_coords *coords)
{
	if (model->diagonal[coords->counter[0] +
		coords->counter[1] * (model->width - 1)])
	{
		set_light(coords, 0, 1, 3);
		deftris_zbuf(coords, 0, 1, 3);
		shade_vtris(coords);
		ftris_zbuf(system, coords);
		if (model->vertex[coords->index[0]][2] !=
			model->vertex[coords->index[3]][2])
			set_light(coords, 0, 2, 3);
		deftris_zbuf(coords, 0, 2, 3);
		shade_vtris(coords);
		ftris_zbuf(system, coords);
		return ;
	}
	set_light(coords, 0, 1, 2);
	deftris_zbuf(coords, 0, 1, 2);
	shade_vtris(coords);
	ftris_zbuf(system, coords);
	if (model->vertex[coords->index[1]][2] !=
		model->vertex[coords->index[2]][2])
		set_light(coords, 1, 2, 3);
	deftris_zbuf(coords, 1, 2, 3);
	shade_vtris(coords);
	ftris_zbuf(system, coords);
}

void	set_light(t_coords *coords, char v0, char v1, char v2)
{
	float	vector[2][3];
	float	normal[3];
	float	norm_len;

	vector[0][0] = coords->f_quad[v2][0] - coords->f_quad[v0][0];
	vector[0][1] = coords->f_quad[v2][1] - coords->f_quad[v0][1];
	vector[0][2] = coords->f_quad[v2][2] - coords->f_quad[v0][2];
	vector[1][0] = coords->f_quad[v1][0] - coords->f_quad[v0][0];
	vector[1][1] = coords->f_quad[v1][1] - coords->f_quad[v0][1];
	vector[1][2] = coords->f_quad[v1][2] - coords->f_quad[v0][2];
	normal[0] = vector[0][1] * vector[1][2] - vector[1][1] * vector[0][2];
	normal[1] = vector[1][0] * vector[0][2] - vector[0][0] * vector[1][2];
	normal[2] = vector[0][0] * vector[1][1] - vector[1][0] * vector[0][1];
	norm_len = sqrt((normal[0] * normal[0]) +
					(normal[1] * normal[1]) +
					(normal[2] * normal[2]));
	coords->f_line[2] = fabs(normal[2] / norm_len);
	coords->f_line[2] = coords->f_line[2] * (2 - coords->f_line[2]);
}
