/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 12:36:23 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/23 19:26:41 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argv, char **argc)
{
	t_setting	setting;

	if (argv != 2)
	{
		write(1, "Needed only one input file.\n", 28);
		exit(0);
	}
	set_model(argc[1], &setting.model, &setting.coords);
	set_system(&setting.system, &setting.model);
	clean_frame(&setting.system, &setting.model);
	transform_model(&setting.system, &setting.model, &setting.coords);
	ui_buttons(&setting.system);
	mlx_put_image_to_window(setting.system.mlx, setting.system.win,
							setting.system.img, 0, 0);
	mlx_hook(setting.system.win, 2, 0, key_press, &setting);
	mlx_hook(setting.system.win, 3, 0, key_release, &setting);
	mlx_hook(setting.system.win, 4, 0, mouse_press, &setting);
	mlx_hook(setting.system.win, 5, 0, mouse_release, &setting);
	mlx_hook(setting.system.win, 6, 0, mouse_move, &setting);
	mlx_hook(setting.system.win, 17, 0, close_fdf, &setting);
	mlx_loop(setting.system.mlx);
	return (0);
}

void	set_model(char *filename, t_model *model, t_coords *coords)
{
	parse(filename, model);
	model->area = model->width * model->height;
	set_diagonal(model);
	pre_transform(model);
	model->rot[0] = ROT_X;
	model->rot[1] = ROT_Y;
	model->rot[2] = ROT_Z;
	set_overall(model);
	set_scalepos(model, coords);
}

void	set_system(t_system *system, t_model *model)
{
	system->mlx = mlx_init();
	system->win = mlx_new_window(system->mlx, WIDTH, HEIGHT, "FdF");
	system->img = mlx_new_image(system->mlx, WIDTH, HEIGHT);
	system->output = (int *)mlx_get_data_addr(system->img,
		&system->img_s[0], &system->img_s[1], &system->img_s[2]);
	system->field = WIDTH * HEIGHT;
	set_buffers(system);
	set_backbuf(system->back_buf);
	system->render = model->color_f ? 66 : 2;
	system->control = 0;
}

void	clean_frame(t_system *system, t_model *model)
{
	int		i;

	i = 0;
	if (system->render & 8 || (model->color_f && system->render & 64))
	{
		while (i < system->field)
		{
			system->output[i] = system->back_buf[i];
			system->z_buf[i] = 1 << 31;
			i += 1;
		}
		return ;
	}
	while (i < system->field)
	{
		system->output[i] = system->back_buf[i];
		i += 1;
	}
}

int		close_fdf(void *param)
{
	(void)param;
	exit(0);
}
