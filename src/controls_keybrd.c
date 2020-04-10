/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keybrd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:05:28 by student           #+#    #+#             */
/*   Updated: 2020/04/10 12:05:32 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	render_mode1(t_setting *setting, int keycode)
{
	if (keycode == 21)
	{
		setting->system.render &= 240;
		setting->system.render |= 8;
		re_render(setting);
		return (1);
	}
	if (keycode == 20)
	{
		setting->system.render &= 240;
		setting->system.render |= 4;
		re_render(setting);
		return (1);
	}
	return (0);
}

char	render_mode2(t_setting *setting, int keycode)
{
	if (keycode == 19)
	{
		setting->system.render &= 240;
		setting->system.render |= 2;
		re_render(setting);
		return (1);
	}
	if (keycode == 18)
	{
		setting->system.render &= 240;
		setting->system.render |= 1;
		re_render(setting);
		return (1);
	}
	return (0);
}

char	render_option(t_setting *setting, int keycode)
{
	if (keycode == 35)
	{
		setting->system.render ^= 128;
		re_render(setting);
		return (1);
	}
	if (keycode == 50)
	{
		if (!setting->model.color_f)
			return (1);
		setting->system.render ^= 64;
		re_render(setting);
		return (1);
	}
	return (0);
}

char	switch_uipanels(t_setting *setting, int keycode)
{
	if (keycode == 8)
	{
		setting->system.render ^= 16;
		re_render(setting);
		return (1);
	}
	if (keycode == 34)
	{
		setting->system.render ^= 32;
		re_render(setting);
		return (1);
	}
	return (0);
}

char	rescale(t_setting *setting, int keycode)
{
	if (keycode == 15)
	{
		if (setting->system.render & 128)
			setting->system.render ^= 128;
		setting->model.rot[0] = ROT_X;
		setting->model.rot[1] = ROT_Y;
		setting->model.rot[2] = ROT_Z;
		setting->model.scale = setting->model.first_scale;
		setting->model.pos[0] = setting->model.first_pos[0];
		setting->model.pos[1] = setting->model.first_pos[1];
		re_render(setting);
		return (1);
	}
	if (keycode == 3 && !(setting->system.render & 128))
	{
		set_scalepos(&setting->model, &setting->coords);
		re_render(setting);
		return (1);
	}
	return (0);
}
