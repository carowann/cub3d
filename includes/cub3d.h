/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:38:03 by cwannhed          #+#    #+#             */
/*   Updated: 2026/01/29 12:43:31 by cwannhed         ###   ########.fr       */
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
# define MAGENTA	0xFF00FF;

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

# define MSG_N_ARGS			"\033[31mError ❌\nInvalid number of arguments.\033[0m\n"
# define MSG_CUB_EXT		"\033[31mError ❌\nInvalid file extension. Expected .cub\033[0m\n"
# define MSG_INIT_MLX		"\033[31mError ❌\nFailed to initialize MLX.\033[0m\n"
# define MSG_WINDOW_FAIL	"\033[31mError ❌\nFailed to create window.\033[0m\n"
# define MSG_IMG_FAIL		"\033[31mError ❌\nFailed to create image.\033[0m\n"
# define MSG_ADDR_FAIL		"\033[31mError ❌\nFailed to get image address.\033[0m\n"
# define MSG_TIME_FAIL		"\033[31mError ❌\nFailed to get current time. \033[0m\n"
# define MSG_OPEN_FAIL		"\033[31mError ❌\nFailed to open file.\033[0m\n"
# define MSG_IS_DIR			"\033[31mError ❌\nFile isn't filing. Is directoring.\033[0m\n"
# define MSG_MALL_FAIL		"\033[31mError ❌\nFailed to allocate memory.\033[0m\n"
# define MSG_FAIL_LOAD_TEX	"\033[31mError ❌\nFailed to load textures.\033[0m\n"
// cub err mess
# define MSG_CUB_FAIL_00	"\033[31mError ❌\nIssues with CUB file: invalid ids.\033[0m\n"
# define MSG_CUB_FAIL_01	"\033[31mError ❌\nIssues with CUB file: missing textures.\033[0m\n"
# define MSG_CUB_FAIL_02	"\033[31mError ❌\nIssues with CUB file: missing colours.\033[0m\n"
# define MSG_CUB_FAIL_03	"\033[31mError ❌\nIssues with CUB file: too many ids.\033[0m\n"
// map err mess
# define MSG_COL_FAIL		"\033[31mError ❌\nWrong color format.\033[0m\n"
# define MSG_MAP_FAIL_00	"\033[31mError ❌\nIssues with map: map too small.\033[0m\n"
# define MSG_MAP_FAIL_01	"\033[31mError ❌\nIssues with map: maze leak.\033[0m\n"
# define MSG_MAP_FAIL_02	"\033[31mError ❌\nIssues with map: wrong rows.\033[0m\n"
# define MSG_MAP_FAIL_03	"\033[31mError ❌\nIssues with map: map could not be validated.\033[0m\n"
# define MSG_MAP_FAIL_04	"\033[31mError ❌\nIssues with map: check elements.\033[0m\n"
# define MSG_MAP_FAIL_05	"\033[31mError ❌\nIssues with map: cannot use tab!\033[0m\n"
# define MSG_MAP_FAIL_06	"\033[31mError ❌\nIssues with map: incorrect player count.\033[0m\n"
// val ok mess
# define MSG_MAP_COPY		"\033[32mMap copied successfully ✅ \033[0m\n"
# define MSG_MAP_GRID		"\033[32mCreated map grid ✅ \033[0m\n"
# define MSG_MLX_INIT		"\033[32mMLX initialised successfully ✅ \033[0m\n"
# define MSG_INPUT_OK		"\033[32mValid input ✅\033[0m\n"
# define MSG_DATA_OK		"\033[32mInitialised data  ✅\033[0m\n"
# define MSG_F_OK			"\033[32mValidated floor color ✅\033[0m\n"
# define MSG_C_OK			"\033[32mValidated ceiling color ✅\033[0m\n"
# define MSG_CUB_OK			"\033[32mRead .cub file ✅\033[0m\n"
// # define MSG_COORD_OK		"\033[32mSaved player coordinates y = %d, x = %d with orientation %c\n", y, x, c  ✅\033[0m\n"
# define MSG_WIN_OK			"\033[32mCreated new window  ✅\033[0m\n"
# define MSG_IMG_OK			"\033[32mCreated new image ✅\033[0m\n"
# define MSG_T0_OK			"\033[32mCreated mlx image for ./text_packs/gem_pack/north.xpm ✅\033[0m\n"
# define MSG_T1_OK			"\033[32mCreated mlx image for ./text_packs/gem_pack/south.xpm ✅\033[0m\n"
# define MSG_T2_OK			"\033[32mCreated mlx image for ./text_packs/gem_pack/west.xpm ✅\033[0m\n"
# define MSG_T3_OK			"\033[32mCreated mlx image for ./text_packs/gem_pack/east.xpm ✅\033[0m\n"
// # define MSG_	"\033[32m ____ \033[0m\n"
// # define MSG_	"\033[32m ____ \033[0m\n"

# define KEY_PRESSED	1
# define KEY_RELEASED	0

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
} t_id;

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
} t_player;

typedef struct s_map
{
	t_list		*lines;
	char		**grid;
	int			width; // strlen
	int			height; // node count
	size_t		floor_color;
	size_t		ceiling_color;
	bool		floor_color_found;
	bool		ceiling_color_found;
} t_map;

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
	void	*mlx; //The MLX connection/instance (required for all MLX operations)
	void	*win; //The window where graphics are displayed
	t_img	*img; //The image buffer where we draw each frame
	char	*addr; //Pointer to the raw pixel data of the image
	int		bits_per_pixel; //Number of bits used to represent each pixel
	int		line_length; //Bytes per row in the image (used to calculate pixel positions)
	int		endian; //Byte order (big/little endian) for color encoding
	int		screen_width;
	int		screen_height;
	t_tex	tex[4]; //Array of 4 tex for walls
	double	aspect_ratio;
} t_mlx;

typedef struct s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
	char		*tex_path[4];
	int			finished_reading;
	int			fd;
} t_data;

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
} t_ray;

/* ========================= */
/*       FUNCTIONS           */
/* ========================= */

int		check_input(int argc, char **argv);
// int		read_map(t_data *data, int fd);
void	read_cub(t_data *data);
void	init_data(t_data *data);
void	init_mlx(t_mlx *mlx, t_data *data);
void	game_loop(t_data *data);
int		cleanup_and_exit(t_data *data, int exit_code, char *msg);
int		handle_close_window(t_data *data);
void	print_mess(char *msg, int code);

void	raycasting(t_data *data);
void	free_matrix(void **matrix);
double	get_current_time(t_data *data);
void	set_delta_distances(t_ray *ray);
void	set_step_and_initial_side_distances(t_ray *ray, t_player *player);
void	set_perpendicular_wall_distance(t_ray *ray, t_player *player);
void	move_forward_or_backward(t_map *map, t_player *player, int direction);
void	rotate_left_or_right(t_player *player, int direction);
void	skip_spaces(char **line);

void	kill_get_next_line(int fd);

// wip
size_t	validate_colours(t_data data, char *colour);// return completely analysed value
t_id	get_id_line(char *str);
void	add_line(char *line, t_data *data);
void	allocate_map(t_data *data, t_list *lines);
void	print_map_debug(t_data *data, t_list *lines);
void	check_map_elements(t_data *data);
void	validate_map(t_data *data);
char	**copy_matrix(char **grid, int height);
int		maze_fill(char **map, int x, int y, t_data d);
void	set_movement_and_rotation_speed(t_data *data, t_player *player);
void	handle_keyboard_input(t_data *data);
// void	set_tex_path(t_data *data);
void	load_all_tex(t_data *data, t_mlx *mlx);
void	set_pixel_buffer(t_data *d, t_ray *ray, int x);
bool	line_is_empty(char *s);
char	*clean_path(t_data *data, char *s);
bool	line_is_ids(char *s);
bool	line_is_map(char *s);

#endif