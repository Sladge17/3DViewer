/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 15:24:46 by student           #+#    #+#             */
/*   Updated: 2020/04/10 16:45:27 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press(int keycode, void *param)
{
	t_setting		*setting;

	setting = (t_setting *)param;
	if (keycode == 53)
		exit(0);
	if (render_mode1(setting, keycode))
		return (0);
	if (render_mode2(setting, keycode))
		return (0);
	if (render_option(setting, keycode))
		return (0);
	if (switch_uipanels(setting, keycode))
		return (0);
	if (rescale(setting, keycode))
		return (0);
	if (z_rotation(setting, keycode))
		return (0);
	debug_input(setting, keycode);
	return (0);
}

int		key_release(int keycode, void *param)
{
	t_setting		*setting;

	setting = (t_setting *)param;
	if (keycode == 257)
		setting->sys.control ^= 8;
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_setting		*setting;

	setting = (t_setting *)param;
	if (mouse_scale(setting, button, x, y))
		return (0);
	if (button == 1 && setting->model.scale)
	{
		if (mouse_uipanels(setting, x, y))
			return (0);
		setting->sys.control ^= 1;
		setting->sys.mouse_pos[0] = x;
		setting->sys.mouse_pos[1] = y;
		return (0);
	}
	if (button == 2)
	{
		setting->sys.control ^= 2;
		setting->sys.mouse_pos[0] = x;
		setting->sys.mouse_pos[1] = y;
		return (0);
	}
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_setting		*setting;

	x = 0;
	y = 0;
	setting = (t_setting *)param;
	if (button == 1 && setting->model.scale && setting->sys.control)
		setting->sys.control ^= 1;
	if (button == 2)
		setting->sys.control ^= 2;
	if (button == 3)
		setting->sys.control ^= 4;
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_setting		*setting;
	char			inv_y;

	inv_y = 0;
	setting = (t_setting *)param;
	if (!(setting->sys.control))
		return (0);
	if (mouse_mrotation(setting, x, y, inv_y))
		return (0);
	if (mouse_mmove(setting, x, y))
		return (0);
	if (mouse_mscale(setting, x, y))
		return (0);
	return (0);
}
