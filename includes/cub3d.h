/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:05:18 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/25 12:21:19 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

# define WINDOW_WIDTH 500
# define WINDOW_HEIGHT 500

/* ========================= */
/*           KEYS           */
/* ========================= */

# define XK_w 0x0077  /* Move up */
# define XK_a 0x0061  /* Move Left */
# define XK_s 0x0073  /* Move down */
# define XK_d 0x0064  /* Move Right */
# define XK_Left 0xff51  /* Camera move left */
# define XK_Right 0xff53  /* Camera move right */
# define XK_Escape 0xff1b

/* ========================= */
/*        STRUCTURES         */
/* ========================= */

typedef enum e_config
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEIL,
}	t_config;


typedef enum e_config
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEIL,
}	t_config;


enum e_msg_codes
{
	MSG_NONE,
	MSG_N_ARGS,
	MSG_CUB_EXT,
	MSG_INIT_MLX,
	MSG_WINDOW_FAIL,
	MSG_IMG_FAIL,
	MSG_ADDR_FAIL
};

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_player;

typedef struct s_map
{
	int	grid[10][10]; // Example fixed size, adjust as needed
	int	width;
	int	height;
	//textures
	//floor and ceiling colors
} t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_mlx;

typedef struct s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
} t_data;


/* ========================= */
/*       FUNCTIONS           */
/* ========================= */

int		check_input(int argc, char **argv);
void	read_map(char *path);
void	init_data(t_data *data);
void	init_mlx(t_mlx *mlx, t_data *data);
void	init_test_map(t_data *data);
void	game_loop(t_data *data);
int		cleanup_and_exit(t_data *data, int exit_code, int msg_code);
int		handle_close_window(t_data *data);

#endif