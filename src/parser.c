/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:56:08 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/16 16:49:38 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "fdf.h"

 /*
** Count words in the string divided by 'c'
*/
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

int check_point(char *str)
{
	int i;

	i = 0;
	while(str[i] != 0)
	{
		if (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+')
			i++;
		else if (str[i] == ',' && i > 0)
		{
			i++;
			while(ft_isalnum(str[i]))
				i++;
		}
		else
			return(0);
	}
	return(1);
}

/*
**Writes a line from the file in the array of ints
*/
int	fill_matrix(t_model *model, char **line_of_z, int i_starts_from, int y)
{
	int k = i_starts_from;
	while(k < (i_starts_from + model->width))
	{
		if (!(model->vertex[k] = (int *)malloc(sizeof(int) * AMOUNT_OF_PARAMETERS_PER_DOT)))
			{
				write(1, "malloc error\n", 13);
				return(0);
			}
		else if (check_point(line_of_z[k - i_starts_from]))
			{
				model->vertex[k][0] = (k - i_starts_from);
				model->vertex[k][1] = y;
				model->vertex[k][2] = ft_atoi(line_of_z[k - i_starts_from]);
				model->vertex[k][3] = parse_color(line_of_z[k - i_starts_from], model, COLOR_DEF);
				//if (model->vertex[k][3] >= 0)
					//model->color_f = 1;
				//free(line_of_z[k - i_starts_from]);
				k++;
			}
		else
			return(0);
	}
	return(1);
}

int		allocate_mem(char *filename, t_model *model)
{
	// int height;
	// int width;
	// int **n = 0;

	int fd;
	fd = 0;
	char *line = 0;

	if ((fd = open(filename, O_RDONLY, 0)) <= 0)
	{
		write(1, "file not exists", 15);
		return(0);
	}
	get_next_line(fd, &line);
	if (line && ft_strlen(line))
		model->height++;
	model->width = ft_wordscounter(line, ' ');
	free(line);
	while(get_next_line(fd, &line))
	{
		model->height++;
		free(line);
	}
	free(line);
	close(fd);
	model->vertex = (int **)malloc(sizeof(int *) * (model->height * model->width));
	model->vertex[model->height * model-> width] = 0;
	return(1);
}

int parse_color(char *word, t_model *model, int default_color)
{
	char **splitted_word;
	int output;

	output = default_color;
	splitted_word = 0;
	splitted_word = ft_strsplit(word, ',');
	if(splitted_word[1])
	{
		output = ft_atoi_base(splitted_word[1], 16);
		model->color_f = 1;
	}
	ft_arrayfree(splitted_word);
	return(output);
}

int		parse(char *filename, t_model *model)
{
	int fd = 0;
	int cnt = 0;
	int y_cnt;
	y_cnt = 0;
	char *next_line = 0;
	char **splitted_line = 0;
	if (!allocate_mem(filename, model))
		return(0);
	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
	{
		write(1, "Error opening file\n", 19);
		return(0);
	}
	while(get_next_line(fd, &next_line))
	{
		splitted_line = ft_strsplit(next_line, DIVIDE_SYMBOL);
		fill_matrix(model, splitted_line, cnt, y_cnt);
		free(next_line);
		if (splitted_line)
			ft_arrayfree(splitted_line);
		cnt += model->width;
		y_cnt++;
	}
	if(next_line)
		free(next_line);
	close(fd);
	return(1);
}
