#include "fdf.h"



void print_left_manual_text(t_sys *system, int *st, int c)
{
	void *mlx_ptr;
	void *win_ptr;
	int x = st[0];
	int y = st[1];

	mlx_ptr = system->mlx;
	win_ptr = system->win;
    mlx_string_put(mlx_ptr, win_ptr, x, y+=30, c, "Rotation");
    mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "LMB & drag - main");
    mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "Z, X - addition");
    mlx_string_put(mlx_ptr, win_ptr, x, y+=50, c, "Movement");
    mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "RMB & drag");
    mlx_string_put(mlx_ptr, win_ptr, x, y+=50, c, "Scale");
    mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "MScroll - fast");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "MMB & y_drag - precision");
	mlx_string_put(mlx_ptr, win_ptr, x, y+=90, c, "Render mode");
    mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "1 - vertex render");
    mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "2 - wireframe render");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "3 - silhouette render");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "4 - mesh render");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "~ - ON / OFF vertex color");
	mlx_string_put(mlx_ptr, win_ptr, x + 80, y+=30, c, "(if exists)");
	mlx_string_put(mlx_ptr, win_ptr, x, y+=90, c, "Projection");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "P - perspective/orthographic");
    mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=70, c, "R - Reset transform");
    mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "F - Focus in center");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, "(orthographic projection only)");
    mlx_string_put(mlx_ptr, win_ptr, x, y+=100, c, "ESC - Exit fdf");
}

void print_right_manual_text(t_setting *s, int *st, int c)
{
	void *mlx_ptr;
	void *win_ptr;
	int x = st[0] + 1570;
	int y = st[1];
	int number_of_triangles = (s->model.width - 1) * (s->model.height - 1) * 2;

	char *vertexes = ft_strjoin("number of vertices: ", ft_itoa(s->model.area));
	char *trianges = ft_strjoin("number of triangles: ", ft_itoa(number_of_triangles));
	char *modelname = ft_strjoin("name: ", s->model.modelname);
	char *max_x = ft_strjoin("X ", ft_itoa(s->model.width));
	char *max_y = ft_strjoin("Y ", ft_itoa(s->model.height));
	char *max_z = ft_strjoin("Z ", ft_itoa(s->model.z_result));
	char *pivot_x = ft_strjoin("X ", ft_itoa((int)s->model.pos[0]));
	char *pivot_y = ft_strjoin("Y ", ft_itoa((int)s->model.pos[1]));


	char *rot_x;
	if ((s->model.rot[0]) < 0)
		rot_x = ft_strjoin("X ", ft_itoa(360 + (int)s->model.rot[0]));
	else
		rot_x = ft_strjoin("X ", ft_itoa((int)s->model.rot[0]));

	char *rot_y;
	if ((s->model.rot[1]) < 0)
		rot_y = ft_strjoin("Y ", ft_itoa(360 + (int)s->model.rot[1]));
	else
		rot_y = ft_strjoin("Y ", ft_itoa((int)s->model.rot[1]));

	char *rot_z;
	if ((s->model.rot[2]) < 0)
		rot_z = ft_strjoin("Z ", ft_itoa(360 + (int)s->model.rot[2]));
	else
		rot_z = ft_strjoin("Z ", ft_itoa((int)s->model.rot[2]));
	char *u_s;
	if (s->model.scale < 0.999999)
		u_s = ft_strjoin("uniform scale: 0", ft_ftoa_an(s->model.scale, 3));
	else
		u_s = ft_strjoin("uniform scale: ", ft_ftoa_an(s->model.scale, 3));


	char *rend_mode;
	if ((s->sys.render & 0b0000001))
		rend_mode = ft_strdup("render mode: vertex render");
	else if (s->sys.render & 0b00000010)
		rend_mode = ft_strdup("render mode: wireframe render");
	else if (s->sys.render & 0b00000100)
		rend_mode = ft_strdup("render mode: silhouette render");
	else if (s->sys.render & 0b00001000)
		rend_mode = ft_strdup("render mode: mesh render");
	else
		rend_mode = ft_strdup("render mode unknown");

	char *color_en;
	if (s->sys.render & 0b01000000)
		color_en = ft_strdup("vertex color: ON");
	else
		color_en = ft_strdup("vertex color: OFF");

	char *projection;
	if (s->sys.render & 0b10000000)
		projection = ft_strdup("projection: perspective");
	else
		projection = ft_strdup("projection: orthographic");
	//char *max_z = ft_strjoin("Zmax:   ", ft_itoa(setting->model.width));

	mlx_ptr = s->sys.mlx;
	win_ptr = s->sys.win;
    mlx_string_put(mlx_ptr, win_ptr, x, y+=30, c, "Model");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, modelname);
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "overal dimensions:");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, max_x);
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, max_y);
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, max_z);
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, vertexes);
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, trianges);
	if(s->model.color_f)
		mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "vertex color: YES");
	else
		mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "vertex color: NO");

	mlx_string_put(mlx_ptr, win_ptr, x, y+=70, c, "Pivot");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, "position:");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, pivot_x);
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, pivot_y);

	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=40, c, "rotation");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, rot_x);
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, rot_y);
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, rot_z);
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y+=30, c, u_s);

	mlx_string_put(mlx_ptr, win_ptr, x, y+=70, c, "Scene");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, rend_mode);
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, color_en);
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y+=30, c, projection);
}

void print_left_text(t_setting *setting, int c)
{
	int start[2];

	start[0] = 20;
	start[1] = 20;
	print_left_manual_text(&setting->sys, start, c);
}

void print_right_text(t_setting *setting, int c)
{
	int start[2];

	start[0] = 15;
	start[1] = 20;
	print_right_manual_text(setting, start, c);
}

void print_two_small_buttons_text(t_setting *setting, int c)
{
	mlx_string_put(setting->sys.mlx, setting->sys.win, 1745, 1042, c, "I - Information");
	mlx_string_put(setting->sys.mlx, setting->sys.win, 35, 1045, c, "C - Controls");
}
