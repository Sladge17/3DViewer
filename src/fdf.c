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

	// drawing_background(&setting.system);
	clean_frame(&setting.system, &setting.model);

	transform_model(&setting.system, &setting.model, &setting.coords);

	// printf("%d %d\n", setting.model.vertex[0][0], setting.model.vertex[0][1]);

	// printf("%d %d\n", setting.model.vertex[setting.model.area - 1][0], setting.model.vertex[setting.model.area - 1][1]);


	// int	i = 0;

	// while (i < setting.model.area)
	// {
	// 	setting.system.output[(setting.model.vertex[i][0] + setting.model.vertex[setting.model.area - 1][0]) * 100 + 
	// 	(setting.model.vertex[i][1] + setting.model.vertex[setting.model.area - 1][1]) * WIDTH * 100] = 
	// 	setting.model.vertex[i][3];
	// 	i += 1;
	// }

	
	mlx_put_image_to_window(setting.system.mlx, setting.system.win, setting.system.img, 0, 0);
	// mlx_string_put(setting.system.mlx, setting.system.win, 30, 30, 0xff, "ROTATION:");

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

	// func prescale -> shift to origin
	// int		i = 0;
	// while (i < model->area)
	// {
	// 	model->vertex[i][0] *= 2;
	// 	model->vertex[i][1] *= 2;
	// 	i += 1;
	// }

	pre_transform(model);
	// shift_to_origin(model);
	model->rot[0] = ROT_X;
	model->rot[1] = ROT_Y;
	model->rot[2] = ROT_Z;
	set_overall(model);
	set_scalepos(model, coords);
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


// void	shift_to_origin(t_model *model)
// {
// 	int		i;

// 	i = 0;
// 	while (i < model->area)
// 	{
// 		model->vertex[i][0] -= model->vertex[model->area - 1][0] / 2;
// 		model->vertex[i][1] -= model->vertex[model->area - 1][1] / 2;
// 		i += 1;
// 	}
// }

void	set_system(t_system *system)
{
	system->mlx = mlx_init();
	system->win = mlx_new_window(system->mlx, WIDTH, HEIGHT, "FdF");
	system->img = mlx_new_image(system->mlx, WIDTH, HEIGHT);
	system->output = (int *)mlx_get_data_addr(system->img, &system->img_s[0], &system->img_s[1], &system->img_s[2]);
	system->field = WIDTH * HEIGHT;
	set_buffers(system);
	set_backbuf(system->back_buf);

	// int	i = 0;
	// while (i < system->field)
	// {
	// 	system->z_buf[i] = 1 << 31;
	// 	i += 1;
	// }

	system->render = 2;
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


// void	drawing_background(t_system *system)
// {
// 	int		i;

// 	i = 0;
// 	while (i < system->field)
// 	{
// 		system->output[i] = system->back_buf[i];
// 		i += 1;
// 	}
// 	// i = 0;
// 	// while (i < model->area)
// 	// {
// 	// 	system->output[model->vertex[i][0] + model->vertex[i][1] * WIDTH] = model->vertex[i][2];
// 	// 	i += 1;
// 	// }
	
// }

void	draw_qvertex(t_system *system, t_model *model, t_coords *coords)
{
	int		i;
	int		j;
	
	if (model->color_f)
	{

		i = 0;
		while (i < 4)
		{
			if (((0 > coords->d_quad[i][0]) || (coords->d_quad[i][0] > WIDTH - 1))
				|| ((0 > coords->d_quad[i][1]) || (coords->d_quad[i][1] > HEIGHT - 2)))
			{
				i += 1;
				continue ;
			}
			j = -1;
			while (j < 2)
			{
				if (coords->d_quad[i][0] && coords->f_quad[i][2] > system->z_buf[(coords->d_quad[i][0] - 1) + (coords->d_quad[i][1] - j) * WIDTH])
				{
					system->output[(coords->d_quad[i][0] - 1) + (coords->d_quad[i][1] - j) * WIDTH] = coords->d_quad[i][2];
					system->z_buf[(coords->d_quad[i][0] - 1) + (coords->d_quad[i][1] - j) * WIDTH] = lround(coords->f_quad[i][2]);
				}
				if (coords->f_quad[i][2] > system->z_buf[(coords->d_quad[i][0]) + (coords->d_quad[i][1] - j) * WIDTH])
				{
					system->output[(coords->d_quad[i][0]) + (coords->d_quad[i][1] - j) * WIDTH] = coords->d_quad[i][2];
					system->z_buf[(coords->d_quad[i][0]) + (coords->d_quad[i][1] - j) * WIDTH] = lround(coords->f_quad[i][2]);
				}
				if (coords->d_quad[i][0] != WIDTH - 1 && coords->f_quad[i][2] > system->z_buf[(coords->d_quad[i][0] + 1) + (coords->d_quad[i][1] - j) * WIDTH])
				{
					system->output[(coords->d_quad[i][0] + 1) + (coords->d_quad[i][1] - j) * WIDTH] = coords->d_quad[i][2];
					system->z_buf[(coords->d_quad[i][0] + 1) + (coords->d_quad[i][1] - j) * WIDTH] = lround(coords->f_quad[i][2]);
				}
				j += 1;
			}
			i += 1;
		}
	}
	else
	{
		i = 0;
		while (i < 4)
		{
			if (((0 > coords->d_quad[i][0]) || (coords->d_quad[i][0] > WIDTH - 1))
				|| ((0 > coords->d_quad[i][1]) || (coords->d_quad[i][1] > HEIGHT - 2)))
			{
				i += 1;
				continue ;
			}
			j = -1;
			while (j < 2)
			{
				if (coords->d_quad[i][0])
					system->output[(coords->d_quad[i][0] - 1) + (coords->d_quad[i][1] - j) * WIDTH] = COLOR_V;
				system->output[(coords->d_quad[i][0]) + (coords->d_quad[i][1] - j) * WIDTH] = COLOR_V;
				if (coords->d_quad[i][0] != WIDTH - 1)
					system->output[(coords->d_quad[i][0] + 1) + (coords->d_quad[i][1] - j) * WIDTH] = COLOR_V;
				j += 1;
			}
			i += 1;
		}
	}
}

// void	draw_qvertex(t_system *system, t_model *model, t_coords *coords)
// {
// 	int		i;
// 	int		j;
	
// 	if (model->color_f)
// 	{

// 		i = 0;
// 		while (i < 4)
// 		{
// 			if (((0 > coords->d_quad[i][0]) || (coords->d_quad[i][0] > WIDTH - 1))
// 				|| ((0 > coords->d_quad[i][1]) || (coords->d_quad[i][1] > HEIGHT - 2)))
// 			{
// 				i += 1;
// 				continue ;
// 			}
// 			j = -1;
// 			while (j < 2)
// 			{
// 				if (coords->d_quad[i][0])
// 					system->output[(coords->d_quad[i][0] - 1) + (coords->d_quad[i][1] - j) * WIDTH] = coords->d_quad[i][2];
// 				system->output[(coords->d_quad[i][0]) + (coords->d_quad[i][1] - j) * WIDTH] = coords->d_quad[i][2];
// 				if (coords->d_quad[i][0] != WIDTH - 1)
// 					system->output[(coords->d_quad[i][0] + 1) + (coords->d_quad[i][1] - j) * WIDTH] = coords->d_quad[i][2];
// 				j += 1;
// 			}
// 			i += 1;
// 		}
// 	}
// }

int		close_fdf(void *param)
{
	(void)param;
	exit(0);
}

void	clean_frame(t_system *system, t_model *model)
{
	int		i;

	i = 0;
	if (model->color_f)
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









	// drawing_background(system);
}