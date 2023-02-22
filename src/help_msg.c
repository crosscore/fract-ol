/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:39 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/22 14:49:23 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	print_fractal_options(void)
{
	ft_putendl_fd("+===============  Available Fractals  ===============+", 1);
	ft_putendl_fd("|  Selecting fractals to display                     |", 1);
	ft_putendl_fd("|                                                    |", 1);
	ft_putendl_fd("|  M - Mandelbrot                                    |", 1);
	ft_putendl_fd("|  J - Julia                                         |", 1);
	ft_putendl_fd("|  B - Burning Ship                                  |", 1);
	ft_putendl_fd("|  T - Tricorn                                       |", 1);
	ft_putendl_fd("|  X - Mandelbox                                     |", 1);
	ft_putendl_fd("|                                                    |", 1);
	ft_putendl_fd("|  Usage example: ./fractol <type>                   |", 1);
	ft_putendl_fd("|                 ./fractol M                        |", 1);
	ft_putendl_fd("+====================================================+", 1);
	ft_putendl_fd("|  Only Julia allows you to specify starting values  |", 1);
	ft_putendl_fd("|  for the initial fractal shape. Values must be     |", 1);
	ft_putendl_fd("|  -2.0 and 2.0 and must contain a decimal point.    |", 1);
	ft_putendl_fd("|                                                    |", 1);
	ft_putendl_fd("|  Usage example: ./fractol J                        |", 1);
	ft_putendl_fd("|                 ./fractol J 0.285 0.01             |", 1);
	ft_putendl_fd("+====================================================+\n", 1);
}

void	print_color_options(void)
{
	ft_putendl_fd("+=================  Color Display  ==================+", 1);
	ft_putendl_fd("|  Pick a display color by providing a hexadecimal   |", 1);
	ft_putendl_fd("|  code. The hex color code must be formatted as     |", 1);
	ft_putendl_fd("|  RRGGBB.                                           |", 1);
	ft_putendl_fd("|                                                    |", 1);
	ft_putendl_fd("|  White:  FFFFFF    Black:  000000                  |", 1);
	ft_putendl_fd("|  Red:    FF0000    Green:  00FF00                  |", 1);
	ft_putendl_fd("|  Blue:   0000FF    Yellow: FFFF00                  |", 1);
	ft_putendl_fd("|                                                    |", 1);
	ft_putendl_fd("|  Other interesting colors:                         |", 1);
	ft_putendl_fd("|  Purple: 9933FF    Orange: CC6600                  |", 1);
	ft_putendl_fd("|  Pink:   FF3399    Turquoise: 00FF80               |", 1);
	ft_putendl_fd("|                                                    |", 1);
	ft_putendl_fd("|  Usage example: ./fractol <type> <color>           |", 1);
	ft_putendl_fd("|                 ./fractol M 0066FF                 |", 1);
	ft_putendl_fd("+====================================================+\n", 1);
}

void	print_controls(void)
{
	ft_putendl_fd("\n", 1);
	ft_putendl_fd("+====================  Controls  ====================+", 1);
	ft_putendl_fd("|   WASD or arrow keys     |     Move view           |", 1);
	ft_putendl_fd("|   E/R or scroll wheel    |     Zoom in/out         |", 1);
	ft_putendl_fd("|   Space                  |     Change color scheme |", 1);
	ft_putendl_fd("|   Left click             |     Shift Julia set     |", 1);
	ft_putendl_fd("|   1, 2, 3, 4, 5          |     Switch fractals     |", 1);
	ft_putendl_fd("|   ESC or close window    |     Quit fractol        |", 1);
	ft_putendl_fd("+====================================================+\n", 1);
}

void	help_msg(t_fractol *f)
{
	ft_putendl_fd("\n+====================================================+", 1);
	ft_putendl_fd("|                     FRACT-OL                       |", 1);
	ft_putendl_fd("+====================================================+\n", 1);
	print_fractal_options();
	print_color_options();
	clean_exit(EXIT_FAILURE, f);
}
