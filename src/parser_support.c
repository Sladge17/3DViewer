/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 21:51:32 by admin             #+#    #+#             */
/*   Updated: 2020/04/15 21:53:08 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_wordscounter(char const *str, char c)
{
	int i;
	int words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

void	calc_z_max(t_model *model, int val)
{
	if (val < model->z_min)
		model->z_min = val;
	else if (val > model->z_max)
		model->z_max = val;
	model->z_result = model->z_max - model->z_min;
}

int		allocate_mem(char *filename, t_model *model)
{
	int		fd;
	char	*line;

	fd = 0;
	line = 0;
	if ((fd = open(filename, O_RDONLY, 0)) <= 0)
		return (0);
	get_next_line(fd, &line);
	if (line && ft_strlen(line))
		model->height++;
	model->width = ft_wordscounter(line, ' ');
	free(line);
	while (get_next_line(fd, &line))
	{
		model->height++;
		free(line);
	}
	free(line);
	close(fd);
	model->vertex = (int **)malloc(sizeof(int *) *
				(model->height * model->width));
	model->vertex[model->height * model->width] = 0;
	return (1);
}

void	model_init(t_model *model)
{
	model->color_f = 0;
	model->z_max = 0;
	model->z_min = 0;
	model->z_result = 0;
}

int		check_point(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+')
			i++;
		else if (str[i] == ',' && i > 0)
		{
			i++;
			while (ft_isalnum(str[i]))
				i++;
		}
		else
			return (0);
	}
	return (1);
}
