/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:34:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/11 12:55:35 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_model(t_system *system, t_model *model, t_coords *coords)
{
	if (system->render & 8)
	{
		fill_qmesh(system, model, coords);
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

void	fill_quad(t_system *system, t_model *model, t_coords *coords)
{
	if (model->color_f && system->render & 64)
	{
		if (lastvert_qcolor(system, model, coords))
			return ;
		fquad_zbuf(system, model, coords);
		lastl_zbuf(system, model, coords);
		return ;
	}
	lastvert_qnocol(system, model, coords);
	fquad_nozbuf(system, model, coords);
	lastl_nozbuf(system, model, coords);
}

void	fill_qmesh(t_system *system, t_model *model, t_coords *coords)
{
	if (lastvert_qmesh(system, model, coords))
		return ;
	if (model->color_f && system->render & 64)
	{
		fqmesh_color(system, model, coords);
		if (firsthor_qmcolor(system, model, coords))
			return ;
		if (lasthor_qmcolor(system, model, coords))
			return ;
		return ;
	}
	fqmesh_nocolor(system, model, coords);
	if (firsthor_qmnocol(system, model, coords))
		return ;
	if (lasthor_qmnocol(system, model, coords))
		return ;
}
