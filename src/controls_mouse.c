/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:55:48 by student           #+#    #+#             */
/*   Updated: 2020/04/10 15:55:50 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	mouse_scale(t_setting *setting, int button, int x, int y)
{
	if (button == 4)
	{
		setting->model.scale -= SPEED_S1;
		if (setting->model.scale < 0)
			setting->model.scale = 0;
		re_render(setting);
		return (1);
	}
	if (button == 5)
	{
		setting->model.scale += SPEED_S1;
		re_render(setting);
		return (1);
	}
	if (button == 3)
	{
		setting->system.control ^= 4;
		setting->system.mouse_pos[0] = x;
		setting->system.mouse_pos[1] = y;
		return (1);
	}
	return (0);
}

char	mouse_uipanels(t_setting *setting, int button, int x, int y)
{
	if (x >= 0 && x < UIBUTTON_W &&
		y >= HEIGHT - UIBUTTON_H && y < HEIGHT)
	{
		setting->system.render ^= 16;
		re_render(setting);
		return (1);
	}
	if (x >= WIDTH - UIBUTTON_W && x < WIDTH &&
		y >= HEIGHT - UIBUTTON_H && y < HEIGHT)
	{
		setting->system.render ^= 32;
		re_render(setting);
		return (1);
	}
	return (0);
}

char	mouse_mrotation(t_setting *setting, int x, int y, char inv_y)
{
	if (!(setting->system.control & 1))
		return (0);
	inv_y = ((setting->model.rot[1] < -90 && setting->model.rot[1] > -270) ||
		(setting->model.rot[1] > 90 && setting->model.rot[1] < 270)) ? -1 : 1;
	if (x < setting->system.mouse_pos[0])
		setting->model.rot[1] -= SPEED_R;
	if (x > setting->system.mouse_pos[0])
		setting->model.rot[1] += SPEED_R;
	if (y < setting->system.mouse_pos[1])
		setting->model.rot[0] -= SPEED_R * inv_y;
	if (y > setting->system.mouse_pos[1])
		setting->model.rot[0] += SPEED_R * inv_y;
	if (setting->model.rot[0] >= 360)
		setting->model.rot[0] -= 360;
	if (setting->model.rot[0] <= -360)
		setting->model.rot[0] += 360;
	if (setting->model.rot[1] >= 360)
		setting->model.rot[1] -= 360;
	if (setting->model.rot[1] <= -360)
		setting->model.rot[1] += 360;
	setting->system.mouse_pos[0] = x;
	setting->system.mouse_pos[1] = y;
	re_render(setting);
	return (1);
}

char	mouse_mmove(t_setting *setting, int x, int y)
{
	if (!(setting->system.control & 2))
		return (0);
	if (x < setting->system.mouse_pos[0])
		setting->model.pos[0] -= SPEED_M;
	if (x > setting->system.mouse_pos[0])
		setting->model.pos[0] += SPEED_M;
	if (y < setting->system.mouse_pos[1])
		setting->model.pos[1] -= SPEED_M;
	if (y > setting->system.mouse_pos[1])
		setting->model.pos[1] += SPEED_M;
	setting->system.mouse_pos[0] = x;
	setting->system.mouse_pos[1] = y;
	re_render(setting);
	return (1);
}

char	mouse_mscale(t_setting *setting, int x, int y)
{
	if (!(setting->system.control & 4))
		return (0);
	if (y > setting->system.mouse_pos[1])
		setting->model.scale += SPEED_S2;
	if (y < setting->system.mouse_pos[1])
	{
		setting->model.scale -= SPEED_S2;
		if (setting->model.scale < 0)
			setting->model.scale = 0;
	}
	setting->system.mouse_pos[0] = x;
	setting->system.mouse_pos[1] = y;
	re_render(setting);
	return (1);
}
