/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:34:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/04/15 21:46:52 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_model(t_sys *sys, t_model *model, t_coords *coords)
{
	if (sys->render & 8)
	{
		fill_qmesh(sys, model, coords);
		return ;
	}
	if (sys->render & 4)
	{
		fill_quad(sys, model, coords);
		return ;
	}
	if (sys->render & 2)
	{
		draw_quad(sys, model, coords);
		return ;
	}
	draw_qvertex(sys, model, coords);
}

void	draw_quad(t_sys *sys, t_model *model, t_coords *coords)
{
	if (model->color_f && sys->render & 64)
	{
		quad_zbuf(sys, model, coords);
		return ;
	}
	quad_nozbuf(sys, model, coords);
}

void	fill_quad(t_sys *sys, t_model *model, t_coords *coords)
{
	if (model->color_f && sys->render & 64)
	{
		if (lastvert_qcolor(sys, model, coords))
			return ;
		fquad_zbuf(sys, model, coords);
		lastl_zbuf(sys, model, coords);
		return ;
	}
	lastvert_qnocol(sys, model, coords);
	fquad_nozbuf(sys, model, coords);
	lastl_nozbuf(sys, model, coords);
}

void	fill_qmesh(t_sys *sys, t_model *model, t_coords *coords)
{
	if (lastvert_qmesh(sys, model, coords))
		return ;
	if (model->color_f && sys->render & 64)
	{
		fqmesh_color(sys, model, coords);
		if (firsthor_qmcolor(sys, model, coords))
			return ;
		if (lasthor_qmcolor(sys, model, coords))
			return ;
		return ;
	}
	fqmesh_nocolor(sys, model, coords);
	if (firsthor_qmnocol(sys, model, coords))
		return ;
	if (lasthor_qmnocol(sys, model, coords))
		return ;
}

void	re_render(t_setting *setting)
{
	clean_frame(&setting->sys, &setting->model);
	transform_model(&setting->sys, &setting->model, &setting->coords);
	ui_buttons(setting);
	if (setting->sys.render & 32)
		ui_boxinfo(setting);
	if (setting->sys.render & 16)
		ui_boxcontrols(setting);
	mlx_put_image_to_window(setting->sys.mlx,
		setting->sys.win, setting->sys.img, 0, 0);
	if (setting->sys.render & 16)
		print_left_text(setting, COLOR_TEXT);
	if (setting->sys.render & 32)
		print_right_text(setting, COLOR_TEXT);
	print_two_small_buttons_text(setting, COLOR_TEXT);
}
