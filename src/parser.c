/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:56:08 by jthuy             #+#    #+#             */
/*   Updated: 2020/04/14 12:30:52 by admin            ###   ########.fr       */
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


char *parse_name(char *str)
{
	int i;
	int size;

	i = ft_strlen(str);
	size = ft_strlen(str);

	if (str)
	{
		while(str[i] != '/' && i != 0)
		{
			i--;
		}
		i++;
		if (ft_strstr(str, ".fdf"))
			size -= 4;
	}
	return(ft_strsub(str, i, size - i));
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



void calc_z_max(t_model *model, int val)
{
	if (val < model->z_min)
		model->z_min = val;
	else if (val > model->z_max)
		model->z_max = val;
	model->z_result = model->z_max - model->z_min;
}


/*
**Writes a line from the file in the array of ints
*/
int	fill_matrix(t_model *model, char **line_of_z, int i_starts_from, int y)
{
	int k;

	k = i_starts_from;
	if (ft_arraylen(line_of_z) < model->width)
		return(0);
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
				calc_z_max(model, model->vertex[k][2]);
				k++;
			}
		else
			return(0);
	}
	return(1);
}

int		allocate_mem(char *filename, t_model *model)
{
	int fd;
	char *line;

	fd = 0;
	line = 0;
	if ((fd = open(filename, O_RDONLY, 0)) <= 0)
		return(0);
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

void model_init(t_model *model)
{
	model->color_f = 0;
	model->z_max = 0;
	model->z_min = 0;
	model->z_result = 0;
}

int		read_file(int fd, char **splitted_line, t_model *model)
{
	char *next_line;
	int cnt;
	int y_cnt;

	cnt = 0;
	y_cnt = 0;
	next_line = 0;
	while(get_next_line(fd, &next_line))
	{
		splitted_line = ft_strsplit(next_line, DIVIDE_SYMBOL);
		if (!fill_matrix(model, splitted_line, cnt, y_cnt))
			return(PARSER_WRONGCONTENT_ERR);
		free(next_line);
		if (splitted_line)
			ft_arrayfree(splitted_line);
		cnt += model->width;
		y_cnt++;
	}
	if(next_line)
		free(next_line);
	return(0);
}

int		parse(char *filename, t_model *model)
{
	int fd;
	int read_status;
	char **splitted_line;

	fd = 0;
	splitted_line = 0;
	model_init(model);
	if (!allocate_mem(filename, model))
		return(PARSER_OPENFILE_ERR);
	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
		return(PARSER_OPENFILE_ERR);
	read_status = read_file(fd, splitted_line, model);
	close(fd);
	return(read_status);
}
