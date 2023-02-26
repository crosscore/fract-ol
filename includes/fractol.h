/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:24:02 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 18:29:15 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>

/*  Dimensions	*/
# define WIDTH 900
# define HEIGHT 900
# define MAX_ITERATIONS 100

/*  Fractal sets	*/
# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3
# define TRICORN 4
# define MANDELBOX 5
# define MULTIBROT 6

/* Keys */
# define EVENT_CLOSE_BTN 17
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_E 101
# define KEY_R 114
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPACE 32
# define KEY_ONE 49
# define KEY_TWO 50
# define KEY_THREE 51
# define KEY_FOUR 52
# define KEY_FIVE 53
# define KEY_SIX 54
# define MULTI 4
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_WHEEL_BTN 3
# define MOUSE_BTN 1
# define MOUSE_BTN_2 3
# define KEY_K 107

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_buf;
	int		fractal_type;
	double	re_min;
	double	re_max;
	double	im_min;
	double	im_max;
	double	jr;
	double	ji;
	double	xs;
	double	xr;
	double	xf;
	int		*color_array;
	int		color_mode;
	int		base_color;
}	t_fractol;

/*  Fractal Sets   */
int		mandelbrot(double cr, double ci);
int		julia(t_fractol *f, double cr, double ci);
int		burning_ship(double cr, double ci);
int		tricorn(double cr, double ci);
int		mandelbox(t_fractol *f, double cr, double ci);
int		multibrot(double cr, double ci);

/*  Render Fractal	*/
void	render_fractal(t_fractol *f);
int		julia_shift(int x, int y, t_fractol *f);

/* Colors	*/
void	change_color(t_fractol *f);
void	set_color_monochrome(t_fractol *f, int base_color);
void	set_color_gradient(t_fractol *f, int base_colors[4], int n);
void	set_color_alternating_stripes(t_fractol *f, int base_color);
void	set_color_three_stripes(t_fractol *f, int base_color);
void	set_color_four_stripes(t_fractol *f, int base_color);
void	set_color_opposites(t_fractol *f, int base_color);
void	set_color_contrasted(t_fractol *f, int base_color);
void	set_color_graphical(t_fractol *f, int base_color);
int		calculate_percent_color(int base_color, double percent);

/*  Events   */
int		key_event(int keycode, t_fractol *f);
int		mouse_event(int keycode, int mouse_x, int mouse_y, t_fractol *f);

/* Initialization */
void	initialize_t_fractol(t_fractol *f);
int		err_msg(char *str1, char *str2, int errno);
void	initialize_fractal(t_fractol *f);
void	setup_fractol(t_fractol *f);
void	set_fractal_viewport(t_fractol *f);
void	get_color(t_fractol *f, int argc, char **argv);
double	ft_atof(char *str);

/*  Clean   */
int		end_fractol(t_fractol *f);
void	clean_exit(int error_code, t_fractol *f);

/*  Help  */
void	display_help(t_fractol *f);
void	display_controls(void);

#endif
