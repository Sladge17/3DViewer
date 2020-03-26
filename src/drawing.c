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

void	draw_quad(t_system *system, t_model *model, t_coords *coords)
{
	draw_line(system, coords->d_quad[0], coords->d_quad[1], COLOR_W);
	draw_line(system, coords->d_quad[0], coords->d_quad[2], COLOR_W);

	// if (model->diagonal[coords->counter[0] + coords->counter[1] * (model->width - 1)])
	// 	draw_line(system, coords->d_quad[1], coords->d_quad[2], COLOR_W);
	// else
	// 	draw_line(system, coords->d_quad[0], coords->d_quad[3], COLOR_W);


	if (coords->counter[0] == model->width - 2)
		draw_line(system, coords->d_quad[2], coords->d_quad[3], COLOR_W);
	if (coords->counter[1] == model->height - 2)
		draw_line(system, coords->d_quad[1], coords->d_quad[3], COLOR_W);
}











