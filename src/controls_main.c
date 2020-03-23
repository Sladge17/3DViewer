/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 15:24:46 by student           #+#    #+#             */
/*   Updated: 2020/03/23 16:16:03 by student          ###   ########.fr       */
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
	
	// if (keycode == 15)
	// {
		
	// 	if (setting->system.render & 128)
	// 		setting->system.render ^= 128;
	// 	setting->model.rot[0] = ROT_X;
	// 	setting->model.rot[1] = ROT_Y;
	// 	setting->model.rot[2] = ROT_Z;
	// 	setting->model.scale = setting->model.first_scale;
	// 	setting->model.pos[0] = setting->model.first_pos[0];
	// 	setting->model.pos[1] = setting->model.first_pos[1];
	// 	// setting->model.overall = 0;
	// }
		// set_params(&setting->model);

	// if (keycode == 3 && !(setting->system.render & 128))
	// {
	// 	setting->model.overall = 0;
	// }

		
	// if (keycode == 35)
	// 	setting->system.render ^= 128;
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
	
	
	return (0);
}