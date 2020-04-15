/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 16:24:10 by student           #+#    #+#             */
/*   Updated: 2020/04/15 21:46:33 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ui_boxcontrols(t_setting *setting)
{
	int		i;
	int		j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < UIBOX_W)
		{
			get_rgba(&setting->sys.output[j + i * WIDTH]);
			j += 1;
		}
		i += 1;
	}
}

void	ui_boxinfo(t_setting *setting)
{
	int		i;
	int		j;

	i = 0;
	while (i < HEIGHT)
	{
		j = WIDTH - UIBOX_W;
		while (j < WIDTH)
		{
			get_rgba(&setting->sys.output[j + i * WIDTH]);
			j += 1;
		}
		i += 1;
	}
}

void	ui_buttons(t_setting *setting)
{
	int		i;
	int		j;

	i = HEIGHT - UIBUTTON_H;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < UIBUTTON_W)
		{
			setting->sys.output[j + i * WIDTH] = UI_BUTTON;
			j += 1;
		}
		j = WIDTH - UIBUTTON_W;
		while (j < WIDTH)
		{
			setting->sys.output[j + i * WIDTH] = UI_BUTTON;
			j += 1;
		}
		i += 1;
	}
}

void	get_rgba(int *color)
{
	unsigned int	a_color;
	unsigned char	*rgb[2];
	float			opacity;
	char			d_rgb[3];
	unsigned char	len[3];

	a_color = UI_BOX;
	rgb[0] = (unsigned char *)color;
	rgb[1] = (unsigned char *)&a_color;
	opacity = rgb[1][3] / (float)255;
	d_rgb[0] = rgb[1][0] > rgb[0][0] ? 1 : -1;
	d_rgb[1] = rgb[1][1] > rgb[0][1] ? 1 : -1;
	d_rgb[2] = rgb[1][2] > rgb[0][2] ? 1 : -1;
	len[0] = abs(rgb[1][0] - rgb[0][0]);
	len[1] = abs(rgb[1][1] - rgb[0][1]);
	len[2] = abs(rgb[1][2] - rgb[0][2]);
	a_color = (lround(rgb[0][0] + len[0] * opacity * d_rgb[0])) +
		(lround(rgb[0][1] + len[1] * opacity * d_rgb[1]) << 8) +
		(lround(rgb[0][2] + len[2] * opacity * d_rgb[2]) << 16);
	*color = a_color;
}
