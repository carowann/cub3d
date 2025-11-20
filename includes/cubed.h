#ifndef CUBED_H
# define CUBED_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"


# define INPUT_ERR "Give me proper Input >:"
# define INPUT_OK "I appreciate the Input"

// # define WIDTH 500
// # define HEIGHT 500

/*** KEYS ***/

# define XK_w 0x0077  /* Move up */
# define XK_a 0x0061  /* Move Left */
# define XK_s 0x0073  /* Move down */
# define XK_d 0x0064  /* Move Right */
# define XK_Left 0xff51  /* Camera move left */
# define XK_Right 0xff53  /* Camera move right */
# define XK_Escape 0xff1b

/////////////////////
/***** STRUCTS *****/
/////////////////////

typedef struct s_image//struct as required by mlx doc
{
	// void	*img_ptr; //points to image struct
	// char	*pix_ptr; //points to actual pixels
	// int		bitxpix; //bits per pixel - says it should be 32
	// int		endian; //unused?
	// int		line_len; //impo
} t_image;

typedef struct s_env // environment
{
	char	*no;
	char    *so;
	char    *we;
	char    *ea;
	int     floor_color;
	int     ceiling_color;
	char    **map;
}	t_env;

typedef struct	s_cubed
{
	char	*name;//link to av[1] in main to pass mand o julia check if ess
	char	*addr;
	int		iter_def; //for image quality and speed

	//image struct
	t_image	img;
	//mlx actions
	void	*start_mlx; //connect to mlx init
	void	*mlx_win; //connect to new window
} t_cubed;

#endif