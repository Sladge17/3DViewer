/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 11:54:58 by student           #+#    #+#             */
/*   Updated: 2020/04/10 11:55:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	debug_input(t_setting *setting, int keycode)
{
	if (keycode == 257)
		setting->system.control ^= 8;
	debug_rotatex(setting, keycode);
	debug_rotatey(setting, keycode);
	debug_move(setting, keycode);
	if (keycode == 12)
	{
		if (setting->system.render & 128)
			setting->system.render ^= 128;
		setting->model.rot[0] = 0;
		setting->model.rot[1] = 0;
		setting->model.rot[2] = 0;
		set_scalepos(&setting->model, &setting->coords);
		setting->model.pos[0] =
			lround(setting->model.vertex[setting->model.area - 1][0] *
			setting->model.scale);
		setting->model.pos[1] =
			lround(setting->model.vertex[setting->model.area - 1][1] *
			setting->model.scale);
	}
	re_render(setting);
}

void	debug_rotatex(t_setting *setting, int keycode)
{
	if (keycode == 126)
	{
		if (setting->system.control & 8)
			setting->model.rot[0] -= 90;
		else
			setting->model.rot[0] -= 1;
	}
	if (keycode == 125)
	{
		if (setting->system.control & 8)
			setting->model.rot[0] += 90;
		else
			setting->model.rot[0] += 1;
	}
	if (setting->model.rot[0] == -360 || setting->model.rot[0] == 360)
		setting->model.rot[0] = 0;
}

void	debug_rotatey(t_setting *setting, int keycode)
{
	if (keycode == 123)
	{
		if (setting->system.control & 8)
			setting->model.rot[1] -= 90;
		else
			setting->model.rot[1] -= 1;
	}
	if (keycode == 124)
	{
		if (setting->system.control & 8)
			setting->model.rot[1] += 90;
		else
			setting->model.rot[1] += 1;
	}
	if (setting->model.rot[1] == -360 || setting->model.rot[1] == 360)
		setting->model.rot[1] = 0;
}

void	debug_move(t_setting *setting, int keycode)
{
	if (keycode == 2)
		setting->model.pos[0] += 1;
	if (keycode == 0)
		setting->model.pos[0] -= 1;
	if (keycode == 1)
		setting->model.pos[1] += 1;
	if (keycode == 13)
		setting->model.pos[1] -= 1;
}

char	z_rotation(t_setting *setting, int keycode)
{
	if (keycode == 6)
	{
		setting->model.rot[2] -= 1;
		if (setting->model.rot[2] == -360 || setting->model.rot[2] == 360)
			setting->model.rot[2] = 0;
		re_render(setting);
		return (1);
	}
	if (keycode == 7)
	{
		setting->model.rot[2] += 1;
		if (setting->model.rot[2] == -360 || setting->model.rot[2] == 360)
			setting->model.rot[2] = 0;
		re_render(setting);
		return (1);
	}
	return (0);
}
