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
		exit (0);
	}
	set_model(argc[1], &setting.model, &setting.coords);

	set_system(&setting.system);

	clean_frame(&setting.system, &setting.model);

	transform_model(&setting.system, &setting.model, &setting.coords);



	// int	i = 0;
	// while (i < setting.model.area)
	// {
	// 	setting.system.output[(setting.model.vertex[i][0] + setting.model.vertex[setting.model.area - 1][0]) * 100 + 
	// 	(setting.model.vertex[i][1] + setting.model.vertex[setting.model.area - 1][1]) * WIDTH * 100] = 
	// 	setting.model.vertex[i][3];
	// 	i += 1;
	// }

	
	mlx_put_image_to_window(setting.system.mlx, setting.system.win,
							setting.system.img, 0, 0);

	mlx_hook(setting.system.win, 2, 0, key_press, &setting);
	mlx_hook(setting.system.win, 4, 0, mouse_press, &setting);
	mlx_hook(setting.system.win, 5, 0, mouse_release, &setting);
	mlx_hook(setting.system.win, 6, 0, mouse_move, &setting);
	mlx_hook(setting.system.win, 17, 0, close_fdf, &setting);

	mlx_loop (setting.system.mlx);
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

void	set_diagonal(t_model *model)
{
	float	diag03;
	float	diag12;
	int		i;
	int		j;
	
	model->diagonal = (char *)malloc(sizeof(char) *
					((model->width - 1) * (model->height - 1)));
	if (!model->diagonal)
		exit (0);		
	j = 0;
	while (j < model->height - 1)
	{
		i = 0;
		while (i < model->width - 1)
		{
			diag03 = len_diag(model->vertex[i + j * model->width],
					model->vertex[i + model->width + 1 + j * model->width]);
			diag12 = len_diag(model->vertex[i + 1 + j * model->width],
					model->vertex[i + model->width + j * model->width]);
			model->diagonal[i + j * (model->width - 1)] = diag12 > diag03 ? 0 : 1;
			i += 1;
		}
		j += 1;
	}
}

float	len_diag(int *vertex_0, int *vertex_1)
{
	float	lenght;
	int		len[3];

	len[0] = abs(vertex_1[0] - vertex_0[0]);
	len[1] = abs(vertex_1[1] - vertex_0[1]);
	len[2] = abs(vertex_1[2] - vertex_0[2]);
	lenght = sqrt(len[0] * len[0] + len[1] * len[1] + len[2] * len[2]);
	return (lenght);
}


void	set_overall(t_model *model)
{
	int		i;

	if (!(model->o_vertex = (float **)malloc(sizeof(float *) * model->area)))
		exit(0);
	i = 0;
	while (i < model->area)
	{
		if (!(model->o_vertex[i] = (float *)malloc(sizeof(float) * 2)))
			exit(0);
		i += 1;
	}
}


void	pre_transform(t_model *model)
{
	int		i;
	int		shift[2];

	shift[0] = model->vertex[model->area - 1][0];
	shift[1] = model->vertex[model->area - 1][1];
	i = 0;
	while (i < model->area)
	{
		model->vertex[i][0] *= 2;
		model->vertex[i][0] -= shift[0];
		model->vertex[i][1] *= 2;
		model->vertex[i][1] -= shift[1];
		model->vertex[i][2] *= 2;
		i += 1;
	}
}


void	set_system(t_system *system)
{
	system->mlx = mlx_init();
	system->win = mlx_new_window(system->mlx, WIDTH, HEIGHT, "FdF");
	system->img = mlx_new_image(system->mlx, WIDTH, HEIGHT);
	system->output = (int *)mlx_get_data_addr(system->img, &system->img_s[0], &system->img_s[1], &system->img_s[2]);
	system->field = WIDTH * HEIGHT;
	set_buffers(system);
	set_backbuf(system->back_buf);
	system->render = 65;
	system->control = 0;
}

void	set_buffers(t_system *system)
{
	if (!(system->back_buf = (int *)malloc(sizeof(int) * system->field)))
		exit (0);
	if (!(system->z_buf = (int *)malloc(sizeof(int) * system->field)))
		exit (0);
	
	// system->z_buf = (int *)malloc(sizeof(int) * system->field);
	// if (!(system->z_buf))
	// 	exit (0);
	// system->light_buf = (int *)malloc(sizeof(int) * area);
	// if (!(system->light_buf))
	// 	exit (0);
}

int		close_fdf(void *param)
{
	(void)param;
	exit(0);
}

void	clean_frame(t_system *system, t_model *model)
{
	int		i;

	// mlx_clear_window(system->mlx, system->win);

	i = 0;
	if (model->color_f && system->render & 64)
	{
		while (i < system->field)
		{
			system->output[i] = system->back_buf[i];
			system->z_buf[i] = 1 << 31;
			// system->light_buf[i] = 0;
			i += 1;
		}
	}
	else
	{
		while (i < system->field)
		{
			system->output[i] = system->back_buf[i];
			// system->z_buf[i] = 1 << 31;
			// system->light_buf[i] = 0;
			i += 1;
		}
	}
}



