/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_system.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 19:38:21 by student           #+#    #+#             */
/*   Updated: 2020/04/07 19:38:25 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_buffers(t_system *system)
{
	if (!(system->back_buf = (int *)malloc(sizeof(int) * system->field)))
		exit(0);
	if (!(system->z_buf = (int *)malloc(sizeof(int) * system->field)))
		exit(0);
}

void	set_backbuf(int *back_buf)
{
	t_back	*backset;
	int		i;
	int		j;
	float	cursor;

	backset = set_backset();
	j = 0;
	while (j < HEIGHT)
	{
		cursor = (float)j / (float)HEIGHT;
		back_buf[j * WIDTH] = backcolor(cursor, backset);
		i = 1;
		while (i < WIDTH)
		{
			back_buf[j * WIDTH + i] = back_buf[j * WIDTH];
			i += 1;
		}
		j += 1;
	}
	free(backset);
}

t_back	*set_backset(void)
{
	t_back	*back;

	if (!(back = (t_back *)malloc(sizeof(t_back))))
		exit(0);
	back->color_rgb[0][0] = (char)(COLOR_UP >> 16);
	back->color_rgb[0][1] = (char)(COLOR_UP >> 8);
	back->color_rgb[0][2] = (char)COLOR_UP;
	back->color_rgb[1][0] = (char)(COLOR_DOWN >> 16);
	back->color_rgb[1][1] = (char)(COLOR_DOWN >> 8);
	back->color_rgb[1][2] = (char)COLOR_DOWN;
	back->d[0] = back->color_rgb[1][0] > back->color_rgb[0][0] ? 1 : -1;
	back->d[1] = back->color_rgb[1][1] > back->color_rgb[0][1] ? 1 : -1;
	back->d[2] = back->color_rgb[1][2] > back->color_rgb[0][2] ? 1 : -1;
	back->len[0] = abs(back->color_rgb[1][0] - back->color_rgb[0][0]);
	back->len[1] = abs(back->color_rgb[1][1] - back->color_rgb[0][1]);
	back->len[2] = abs(back->color_rgb[1][2] - back->color_rgb[0][2]);
	return (back);
}

int		backcolor(float cursor, t_back *backset)
{
	int		color;
	int		chanal[3];

	chanal[0] = (backset->color_rgb[0][0] +
				lround(backset->len[0] * cursor * backset->d[0])) << 16;
	chanal[1] = (backset->color_rgb[0][1] +
				lround(backset->len[1] * cursor * backset->d[1])) << 8;
	chanal[2] = (backset->color_rgb[0][2] +
				lround(backset->len[2] * cursor * backset->d[2]));
	color = chanal[0] + chanal[1] + chanal[2];
	return (color);
}
