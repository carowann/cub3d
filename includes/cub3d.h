/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:38:03 by cwannhed          #+#    #+#             */
/*   Updated: 2026/01/30 17:48:36 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _GNU_SOURCE
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../minilibx-linux/mlx_int.h"

/* ========================= */
/*         DEFINES           */
/* ========================= */

# define BOLD	"\033[1m"
# define BLUE	"\033[0;34m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define RESET	"\033[0m"

//minimap?
#define MM_TILE_SIZE 10  // Ogni cubo della mappa sarà 10x10 pixel
#define MM_COLOR_WALL 0x00C9C9C9 // Bianco
#define MM_COLOR_FLOOR 0x002A2A2A // Nero
#define MM_COLOR_PLAYER 0x00FFFFFF // Rosso


# define FRAME_TIME_SEC	0.01666667 // Approx 60 FPS
# define MOVEMENT_SPEED_MULTIPLIER	3.0
# define ROTATION_SPEED_MULTIPLIER	2.0
# define WALL	'1'
# define EMPTY	'0'
# define UP		1
# define DOWN	-1
# define LEFT	-1
# define RIGHT	1
# define DELTA_DIST_INFINITY	1e30
# define STEP_X_LEFT	-1
# define STEP_X_RIGHT	1
# define STEP_Y_UP		-1
# define STEP_Y_DOWN	1
# define KEY_PRESSED	1
# define KEY_RELEASED	0

# define MSG_N_ARGS			"Invalid number of arguments.\n"
# define MSG_CUB_EXT		"Invalid file extension. Expected .cub\n"
# define MSG_INIT_MLX		"Failed to initialize MLX.\n"
# define MSG_WINDOW_FAIL	"Failed to create window.\n"
# define MSG_IMG_FAIL		"Failed to create image.\n"
# define MSG_ADDR_FAIL		"Failed to get image address.\n"
# define MSG_TIME_FAIL		"Failed to get current time.\n"
# define MSG_OPEN_FAIL		"Failed to open file.\n"
# define MSG_IS_DIR			"File isn't filing. Is directoring.\n"
# define MSG_MALL_FAIL		"Failed to allocate memory.\n"
# define MSG_FAIL_LOAD_TEX	"Failed to load textures.\n"
// cub err mess
# define MSG_CUB_FAIL_00	"Issues with CUB file: invalid ids.\n"
# define MSG_CUB_FAIL_01	"Issues with CUB file: missing textures.\n"
# define MSG_CUB_FAIL_02	"Issues with CUB file: missing colours.\n"
# define MSG_CUB_FAIL_03	"Issues with CUB file: too many ids.\n"
# define MSG_CUB_FAIL_04	"Issues with CUB file: wrong configuration.\n"
// map err mess
# define MSG_COL_FAIL		"Wrong color format.\n"
# define MSG_MAP_FAIL_00	"Issues with map: map too small.\n"
# define MSG_MAP_FAIL_01	"Issues with map: maze leak.\n"
# define MSG_MAP_FAIL_02	"Issues with map: wrong rows.\n"
# define MSG_MAP_FAIL_03	"Issues with map: map could not be validated.\n"
# define MSG_MAP_FAIL_04	"Issues with map: check elements.\n"
# define MSG_MAP_FAIL_05	"Issues with map: cannot use tab!\n"
# define MSG_MAP_FAIL_06	"Issues with map: incorrect player count.\n"
// val ok mess
# define MSG_MAP_COPY		"✅ Map copied successfully\n"
# define MSG_MAP_GRID		"✅ Created map grid\n"
# define MSG_MLX_INIT		"✅ MLX initialised successfully\n"
# define MSG_INPUT_OK		"✅ Valid input\n"
# define MSG_DATA_OK		"✅ Initialised data\n"
# define MSG_F_OK			"✅ Validated floor color\n"
# define MSG_C_OK			"✅ Validated ceiling color\n"
# define MSG_CUB_OK			"✅ Read .cub file\n"
# define MSG_WIN_OK			"✅ Created new window\n"
# define MSG_IMG_OK			"✅ Created new image\n"

/* ========================= */
/*        STRUCTURES         */
/* ========================= */

enum e_msg_codes
{
	SUCCESS,
	FAILURE
};

enum e_wall_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef enum e_id
{
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_FL,
	ID_CE
}	t_id;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time_curr_frame;
	double	time_last_frame;
	double	move_speed;
	double	rot_speed;
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;
	double	last_render_time;
}	t_player;

typedef struct s_map
{
	t_list		*lines;
	char		**grid;
	int			width;
	int			height;
	size_t		floor_color;
	size_t		ceiling_color;
	bool		floor_color_found;
	bool		ceiling_color_found;
}	t_map;

typedef struct s_tex
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		x;
	int		y;
	double	pos;
	double	step;
}	t_tex;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		screen_width;
	int		screen_height;
	t_tex	tex[4];
	double	aspect_ratio;
}	t_mlx;

typedef struct s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
	char		*tex_path[4];
	int			fd;
}	t_data;

typedef struct s_ray
{
	int		step_x; //step in x direction
	int		step_y; //step in y direction
	int		hit; //was there a wall hit?
	int		wall_side; //was a NS or a EW wall hit?
	int		map_x; //current square of the map in x
	int		map_y; //current square of the map in y
	int		draw_start; //start of the line to draw
	int		draw_end; //end of the line to draw
	int		line_height; //height of the line to draw
	double	camera_x; //x-coordinate in camera space
	double	ray_dir_x; //ray direction x
	double	ray_dir_y; //ray direction y
	double	side_dist_x; //initial side distance in x
	double	side_dist_y; //initial side distance in y
	double	delta_dist_x; //length of ray from one x-side to next x-side
	double	delta_dist_y; //length of ray from one y-side to next y-side
	double	perp_wall_dist; //perpendicular distance to the wall
}	t_ray;

/* ========================= */
/*       FUNCTIONS           */
/* ========================= */

int		check_input(int argc, char **argv);
void	read_cub(t_data *data);
void	init_data(t_data *data);
void	init_mlx(t_mlx *mlx, t_data *data);
void	game_loop(t_data *data);
int		cleanup_and_exit(t_data *data, int exit_code, char *msg);
int		handle_close_window(t_data *data);
void	print_mess(char *msg, int code);
void	start_mlx(t_data d);

void	raycasting(t_data *data);
void	free_matrix(void **matrix);
double	get_current_time(t_data *data);
void	set_delta_distances(t_ray *ray);
void	set_step_and_initial_side_distances(t_ray *ray, t_player *player);
void	set_perpendicular_wall_distance(t_ray *ray, t_player *player);
void	skip_spaces(char **line);

void	kill_get_next_line(int fd);

// wip
size_t	validate_colours(t_data data, char *colour);
t_id	get_id_line(char *str);
void	add_line(char *line, t_data *data);
void	allocate_map(t_data *data, t_list *lines);
void	validate_map(t_data *data);
int		maze_fill(char **map, int x, int y, t_data d);
void	set_movement_and_rotation_speed(t_data *data, t_player *player);
void	handle_keyboard_input(t_data *data);
void	load_all_tex(t_data *data, t_mlx *mlx);
void	set_pixel_buffer(t_data *d, t_ray *ray, int x);
bool	line_is_empty(char *s);
char	*clean_path(t_data *data, char *s);
bool	line_is_ids(char *s);
bool	line_is_map(char *s);
///temp
void	draw_minimap_tile(t_data *data, int x, int y, int color);
void	draw_minimap(t_data *data);
int	render_mm_frame(t_data *data);


#endif