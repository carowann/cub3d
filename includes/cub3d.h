/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/01/12 18:23:15 by giomastr         ###   ########.fr       */
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

/* ========================= */
/*         DEFINES           */
/* ========================= */

# define WINDOW_WIDTH	800
# define WINDOW_HEIGHT	800

# define TEXTURE_WIDTH	64
# define TEXTURE_HEIGHT	64

# define FRAME_TIME_SEC	0.01666667 // Approx 60 FPS

# define MOVEMENT_SPEED_MULTIPLIER	3.0
# define ROTATION_SPEED_MULTIPLIER	2.0

# define WALL	1
# define EMPTY	0

# define UP		1
# define DOWN	-1
# define LEFT	-1
# define RIGHT	1

# define WALL_MARGIN	0.2

# define DELTA_DIST_INFINITY	1e30

# define STEP_X_LEFT	-1
# define STEP_X_RIGHT	1
# define STEP_Y_UP		-1
# define STEP_Y_DOWN	1

# define MSG_N_ARGS			"Error\nInvalid number of arguments.\n"
# define MSG_CUB_EXT		"Error\nInvalid file extension. Expected .cub\n"
# define MSG_INIT_MLX		"Error\nFailed to initialize MLX.\n"
# define MSG_N_ARGS			"Error\nInvalid number of arguments.\n"
# define MSG_CUB_EXT		"Error\nInvalid file extension. Expected .cub\n"
# define MSG_INIT_MLX		"Error\nFailed to initialize MLX.\n"
# define MSG_WINDOW_FAIL	"Error\nFailed to create window.\n"
# define MSG_IMG_FAIL			"Error\nFailed to create image.\n"
# define MSG_ADDR_FAIL			"Error\nFailed to get image address.\n"
# define MSG_TIME_FAIL			"Error\nFailed to get current time.\n"
# define MSG_OPEN_FAIL		"Error\nFailed to open file.\n"
# define MSG_IS_DIR			"Error\nFile isn't filing. Is directoring.\n"
# define MSG_MAP_FAIL		"Error\nIssues with map.\n"
# define MSG_CUB_FAIL		"Error\nIssues with CUB file.\n"
# define MSG_MALL_FAIL		"Error\nFailed to allocate memory.\n"
# define MSG_COL_FAIL		"Error\nWrong color format.\n"
# define MSG_PLAYER			"Error\nCheck player count\n"
# define MSG_ELEM_FAIL		"Error\nCheck elements in map\n"

# define MSG_FAIL_LOAD_TEX	"Error\nFailed to load textures.\n"

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
    ID_NO,  // North
    ID_SO,  // South
    ID_WE,  // West
    ID_EA,  // East
    ID_FL,
	ID_CE
}   t_id;

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
} t_player;

typedef struct s_map
{
	t_list		*lines;
	char		**grid;
	int			width; // strlen
	int			height; // node count
	int			floor_color;
	int			ceiling_color;

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
}	t_tex;

typedef struct s_mlx
{
	void	*mlx; //The MLX connection/instance (required for all MLX operations)
	void	*win; //The window where graphics are displayed
	void	*img; //The image buffer where we draw each frame
	char	*addr; //Pointer to the raw pixel data of the image
	int		bits_per_pixel; //Number of bits used to represent each pixel
	int		line_length; //Bytes per row in the image (used to calculate pixel positions)
	int		endian; //Byte order (big/little endian) for color encoding
	int		screen_width;
	int		screen_height;
	t_tex	tex[4]; //Array of 4 tex for walls
} t_mlx;

typedef struct s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
	char		*tex_path[4];
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
void	read_cub(t_data *data, int fd);
void	init_data(t_data *data);
void	init_mlx(t_mlx *mlx, t_data *data);
void	test_map(t_data *data); // mappa hardcoded
void	game_loop(t_data *data);
int		cleanup_and_exit(t_data *data, int exit_code, char *msg);
int		handle_close_window(t_data *data);
void	print_err_mess(char *msg);

void	raycasting(t_data *data);
void	free_matrix(void **matrix);
double	get_current_time(t_data *data);
void	set_delta_distances(t_ray *ray);
void	set_step_and_initial_side_distances(t_ray *ray, t_player *player);
void	set_perpendicular_wall_distance(t_ray *ray, t_player *player);
void	move_forward_or_backward(t_map *map, t_player *player, int direction);
void	rotate_left_or_right(t_player *player, int direction);
void	free_list(t_list *list);


// wip
int	validate_colours(t_data *data, char *colour);// return completely analysed value
t_id	get_id_line(char *str);
void	add_line(char *line, t_data *data);
void	allocate_map(t_data *data, t_list *lines);
void	print_map_debug(t_data *data, t_list *lines);
void	check_map_elements(t_data *data);
void	validate_map(t_data *data);
char	**copy_matrix(char **grid, int height);
int		maze_fill(char **map, int x, int y, int max_x, int max_y);

void	set_movement_and_rotation_speed(t_data *data, t_player *player);
void	handle_keyboard_input(t_data *data);
void	set_tex_path(t_data *data);
void	load_all_tex(t_data *data, t_mlx *mlx);
void	set_pixel_buffer(t_mlx *mlx, t_ray *ray, t_map *map, t_player *player, int x);


#endif