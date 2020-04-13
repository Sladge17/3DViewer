/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 12:36:23 by jthuy             #+#    #+#             */
/*   Updated: 2020/04/10 16:52:49 by student          ###   ########.fr       */
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
	set_system(&setting.sys, &setting.model);
	clean_frame(&setting.sys, &setting.model);
	transform_model(&setting.sys, &setting.model, &setting.coords);
	ui_buttons(&setting.sys);
	mlx_put_image_to_window(setting.sys.mlx, setting.sys.win,
							setting.sys.img, 0, 0);
	mlx_hook(setting.sys.win, 2, 0, key_press, &setting);
	mlx_hook(setting.sys.win, 3, 0, key_release, &setting);
	mlx_hook(setting.sys.win, 4, 0, mouse_press, &setting);
	mlx_hook(setting.sys.win, 5, 0, mouse_release, &setting);
	mlx_hook(setting.sys.win, 6, 0, mouse_move, &setting);
	mlx_hook(setting.sys.win, 17, 0, close_fdf, &setting);
	mlx_loop(setting.sys.mlx);
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

void	set_system(t_sys *sys, t_model *model)
{
	sys->mlx = mlx_init();
	sys->win = mlx_new_window(sys->mlx, WIDTH, HEIGHT, "fdf");
	sys->img = mlx_new_image(sys->mlx, WIDTH, HEIGHT);
	sys->output = (int *)mlx_get_data_addr(sys->img,
		&sys->img_s[0], &sys->img_s[1], &sys->img_s[2]);
	sys->field = WIDTH * HEIGHT;
	set_buffers(sys);
	set_backbuf(sys->back_buf);
	sys->render = model->color_f ? 66 : 2;
	sys->control = 0;
}

void	clean_frame(t_sys *sys, t_model *model)
{
	int		i;

	i = 0;
	if (sys->render & 8 || (model->color_f && sys->render & 64))
	{
		while (i < sys->field)
		{
			sys->output[i] = sys->back_buf[i];
			sys->z_buf[i] = 1 << 31;
			i += 1;
		}
		return ;
	}
	while (i < sys->field)
	{
		sys->output[i] = sys->back_buf[i];
		i += 1;
	}
}

int		close_fdf(void *param)
{
	(void)param;
	exit(0);
}
