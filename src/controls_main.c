/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 15:24:46 by student           #+#    #+#             */
/*   Updated: 2020/03/23 20:15:31 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press(int keycode, void *param)
{	
	t_setting		*setting;

	setting = (t_setting *)param;
	
	if (keycode == 53)
		exit (0);
	// // if (keycode == 126)
	// // 	setting->model.rot[0] -= 1;
	// // if (keycode == 125)
	// // 	setting->model.rot[0] += 1;
	// // if (setting->model.rot[0] == -360 || setting->model.rot[0] == 360)
	// // 		setting->model.rot[0] = 0;
	// // if (keycode == 123)
	// // 	setting->model.rot[1] -= 1;
	// // if (keycode == 124)
	// // 	setting->model.rot[1] += 1;
	// // if (setting->model.rot[1] == -360 || setting->model.rot[1] == 360)
	// // 		setting->model.rot[1] = 0;
	if (keycode == 6)
		setting->model.rot[2] -= 1;
	if (keycode == 7)
		setting->model.rot[2] += 1;
	if (setting->model.rot[2] == -360 || setting->model.rot[2] == 360)
			setting->model.rot[2] = 0;
	
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
	}
	if (keycode == 3 && !(setting->system.render & 128))
	{
		set_scalepos(&setting->model, &setting->coords);
	}


	if (keycode == 12)
	{
		if (setting->system.render & 128)
			setting->system.render ^= 128;
		setting->model.rot[0] = 0;
		setting->model.rot[1] = 0;
		setting->model.rot[2] = 0;
		setting->model.scale = 100;
		setting->model.pos[0] = setting->model.vertex[setting->model.area - 1][0] * 100;
		setting->model.pos[1] = setting->model.vertex[setting->model.area - 1][1] * 100;
	}

		
	if (keycode == 35)
		setting->system.render ^= 128;
	// if (keycode == 18)
	// {
	// 	setting->system.render &= 128;
	// 	setting->system.render |= 1;
	// }
	// if (keycode == 19)
	// {
	// 	setting->system.render &= 128;
	// 	setting->system.render |= 2;
	// }
	// if (keycode == 20)
	// {
	// 	setting->system.render &= 128;
	// 	setting->system.render |= 4;
	// }
	// if (keycode == 21)
	// {
	// 	setting->system.render &= 128;
	// 	setting->system.render |= 8;
	// }
	// if (keycode == 2)
	// 	setting->system.control ^= 8;

	clean_frame(&setting->system);
	transform_model(&setting->system, &setting->model, &setting->coords);
	mlx_put_image_to_window(setting->system.mlx, setting->system.win, setting->system.img, 0, 0);

	 mlx_string_put(setting->system.mlx, setting->system.win, 30, 30, 0xff, ft_itoa(setting->model.pos[0]));
	 mlx_string_put(setting->system.mlx, setting->system.win, 30, 60, 0xff, ft_itoa(setting->model.pos[1]));

	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_setting		*setting;

	setting = (t_setting *)param;
	if (button == 4)
	{
		setting->model.scale -= SPEED_S1;
		if (setting->model.scale < 0)
			setting->model.scale = 0;
		// mlx_clear_window(setting->system.mlx, setting->system.win);
		// transform_model(&setting->system, &setting->model, &setting->coords);
		clean_frame(&setting->system);	
		transform_model(&setting->system, &setting->model, &setting->coords);
		mlx_put_image_to_window(setting->system.mlx, setting->system.win, setting->system.img, 0, 0);
		return (0);
	}
	if (button == 5)
	{
		setting->model.scale += SPEED_S1;
		// mlx_clear_window(setting->system.mlx, setting->system.win);
		// transform_model(&setting->system, &setting->model, &setting->coords);
		clean_frame(&setting->system);	
		transform_model(&setting->system, &setting->model, &setting->coords);
		mlx_put_image_to_window(setting->system.mlx, setting->system.win, setting->system.img, 0, 0);
		return (0);
	}
	if (button == 1)
		setting->system.control ^= 1;
	if (button == 2)
		setting->system.control ^= 2;
	if (button == 3)
		setting->system.control ^= 4;
	setting->system.mouse_pos[0] = x;
	setting->system.mouse_pos[1] = y;
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_setting		*setting;

	x = 0;
	y = 0;
	setting = (t_setting *)param;
	if (button == 1)
		setting->system.control ^= 1;
	if (button == 2)
		setting->system.control ^= 2;
	if (button == 3)
		setting->system.control ^= 4;
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_setting		*setting;
	char			inv_y;

	setting = (t_setting *)param;
	if (!(setting->system.control))
		return (0);
	if (setting->system.control & 1)
	{
		inv_y = ((setting->model.rot[1] < -90 && setting->model.rot[1] > -270) || (setting->model.rot[1] > 90 && setting->model.rot[1] < 270)) ? -1 : 1;
		
		if (x < setting->system.mouse_pos[0])
			setting->model.rot[1] -= SPEED_R;
		if (x > setting->system.mouse_pos[0])
			setting->model.rot[1] += SPEED_R;
		if (y < setting->system.mouse_pos[1])
			setting->model.rot[0] -= SPEED_R * inv_y;
		if (y > setting->system.mouse_pos[1])
			setting->model.rot[0] += SPEED_R * inv_y;
		
		// if (setting->model.rot[0] == 360 || setting->model.rot[0] == -360)
		// 	setting->model.rot[0] = 0;
		// if (setting->model.rot[1] == 360 || setting->model.rot[1] == -360)
		// 	setting->model.rot[1] = 0;
		if (setting->model.rot[0] >= 360)
			setting->model.rot[0] -= 360;
		if (setting->model.rot[0] <= -360)
			setting->model.rot[0] += 360;
		if (setting->model.rot[1] >= 360)
			setting->model.rot[1] -= 360;
		if (setting->model.rot[1] <= -360)
			setting->model.rot[1] += 360;
		
	}
	if (setting->system.control & 2)
	{
		if (x < setting->system.mouse_pos[0])
			setting->model.pos[0] -= SPEED_M;
		if (x > setting->system.mouse_pos[0])
			setting->model.pos[0] += SPEED_M;
		if (y < setting->system.mouse_pos[1])
			setting->model.pos[1] -= SPEED_M;
		if (y > setting->system.mouse_pos[1])
			setting->model.pos[1] += SPEED_M;
	}
	if (setting->system.control & 4)
	{	
		if (y > setting->system.mouse_pos[1])
			setting->model.scale += SPEED_S2;
		if (y < setting->system.mouse_pos[1])
		{
			setting->model.scale -= SPEED_S2;
			if (setting->model.scale < 0)
				setting->model.scale = 0;
		}
	}
	setting->system.mouse_pos[0] = x;
	setting->system.mouse_pos[1] = y;

	clean_frame(&setting->system);	
	transform_model(&setting->system, &setting->model, &setting->coords);
	mlx_put_image_to_window(setting->system.mlx, setting->system.win, setting->system.img, 0, 0);
	
	return (0);
}