/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:09:11 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/29 16:59:12 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Includes

# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

// Defines

# define ARGS_ERR "Error\nInvalid number of arguments\n"
# define FILE_EXTENSION_ERR "Error\nScene extension should be .cub\n"
# define SCENE_FILE_ERR "Error\nScene file cannot be opened\n"
# define EMPTY_SCENE_ERR "Error\nScene file is empty\n"
# define SCENE_ID_ERR "Error\nScene identifiers are corrupted\n"
# define COLOR_ERR "Error\nScene colors are corrupted\n"
# define MAP_CLOSED_ERR "Error\nMap is not closed\n"
# define MAP_EMPTY_LINE_ERR "Error\nMap should not contain empty lines\n"
# define MAP_CHARS_ERR "Error\nMap contains invalid chars\n"
# define MAP_START_ERR "Error\nMap must contain strictly one starting \
						position\n"
# define IMG_ERR "Error\nImage(s) could not be opened\n"

# define SCREEN_WIDTH 854
# define SCREEN_HEIGHT 480
# define MINIMAP_SIZE 200
# define MINIMAP_MARGIN 20
# define MINIMAP_TILE_SIZE 16
# define MINIMAP_PLAYER_SIZE 6
# define COL_WIDTH 2
# define SPEED 0.02
# define ROTATION_SPEED 0.02
# define MOUSE_THRESHOLD 50
# define SENS 0.3
# define FOV 90

# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define D_KEY 2
# define S_KEY 1
# define E_KEY 14
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define KEYPRESS 2
# define KEYPRESSMASK 3
# define KEYRELEASE 3
# define KEYRELEASEMASK 0
# define DESTROYNOTIFY 17
# define STRUCTURENOTIFYMASK 0

// THIS PART ISN'T NORMED ACCORDING TO THE 42 NORMINETTE
// BUT IS NECESSARY TO MAKE IT CROSS-COMPATIBLE
# define DESTROY_DISPLAY(mlx_ptr)
# define GET_MOUSE_POS(mlx_ptr, win_ptr, pos_x, pos_y) mlx_mouse_get_pos(win_ptr, &pos_x, &pos_y)

// Structures

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_ray
{
	t_coord	dir;
	t_coord	wall_pos;
	char	side;
	int		touched_tile_x;
	int		touched_tile_y;
	double	screen_x;
	double	dist;
	double	height;
}	t_ray;

typedef struct s_image
{
	void	*img_ptr;
	char	*data_addr;
	int		width;
	int		height;
	int		size_line;
	int		bits_per_pixel;
	int		endian;
	char	*path;
}	t_image;

typedef struct s_player
{
	t_coord	*dir;
	t_coord	*pos;
	t_coord	*mouse_pos;
	int		key_a;
	int		key_w;
	int		key_d;
	int		key_s;
	int		key_right;
	int		key_left;
}	t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	*player;
	t_image		*no;
	t_image		*so;
	t_image		*we;
	t_image		*ea;
	t_image		*door;
	t_image		*hand;
	t_image		*background;
	t_image		*render;
	int			floor_color;
	int			ceil_color;
	char		**scene;
	char		**map;
	int			map_width;
	int			map_height;
	int			map_start_line;
	int			hand_frame;
}	t_data;

// Prototypes

// Main
void	quit(t_data *data, int err_code);

// Rendering
void	render_column(t_data *data, t_ray *ray);
void	create_background(t_data *data);
void	set_color_at_pixel(t_data *data, int x, int y, int color);
void	render_minimap(t_data *data);

// Images
void	init_images(t_data *data);
void	*create_images(t_data *data);
void	get_images_data(t_data *data);

// Hand
void	render_hand(t_data *data);

// Raycasting
void	raycast(t_data *data);
void	get_dist_to_wall(t_data *data, t_ray *ray);

// Movement
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		game_loop(t_data *data);
void	handle_movement(t_data *data);
void	deal_with_collisions(t_data *data, t_coord *old_pos,
			t_coord *new_pos);
void	handle_movement(t_data *data);
void	rotate_player(t_data *data, double rotation_speed);
void	door_interract(t_data *data);

// Player
void	init_player(t_data *data);
void	*get_player_starting_attributes(t_data *data);

// Parsing
void	*read_scene(t_data *data, char *file);
void	check_valid_scene(t_data *data);
void	*read_map(t_data *data);

// Window management
void	init_window(t_data *data);

// Utils
int		ft_atoi(const char *nptr);
double	ft_distance_to(double x1, double y1, double x2, double y2);
void	ft_free_tab(void **tab, int n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putstr_fd(char *str, int fd);
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size);
int		ft_rgb_to_int(int r, int g, int b);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	ft_strdel(char **str);
int		ft_strlen(char *str);
char	*ft_strldup(const char *s, int len, char c);
int		ft_tablen(char **tab);
char	*get_next_line(int fd);
void	ft_print_tab(char **tab);

#endif
