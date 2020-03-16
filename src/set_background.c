/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 15:08:31 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/16 15:20:33 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	back->color_rgb[0][0] = ((COLOR_UP & (255 << 16)) >> 16);
	back->color_rgb[0][2] = (COLOR_UP & 255);
	back->color_rgb[0][1] = ((COLOR_UP & (255 << 8)) >> 8);
	back->color_rgb[1][0] = ((COLOR_DOWN & (255 << 16)) >> 16);
	back->color_rgb[1][1] = ((COLOR_DOWN & (255 << 8)) >> 8);
	back->color_rgb[1][2] = (COLOR_DOWN & 255);
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
