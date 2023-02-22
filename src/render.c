/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:00 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/22 14:31:51 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* set_pixel_color:
MLXイメージマップの1つのピクセルに色を追加します。
MLX画像は、1ピクセルあたり32ビットで構成されています。
色の整数は、ここでは右から左に格納され、0xAARRGGBBの形式になっています。
8ビットは、アルファ(透明度)、赤、緑、青の各色成分をエンコードします。
ビットシフト:
	- BB >>  0 (0x000000BB)
	- GG >>  8 (0x0000GG00)
	- RR >> 16 (0x00RR0000)
	- AA >> 24 (0xAA000000) */
static void	set_pixel_color(t_fractol *f, int x, int y, int color)
{
	f->buf[x * 4 + y * WIDTH * 4] = color;
	f->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
	f->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
	f->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

/* calculate_fractal:
現在のフラクタルセットに応じて、正しいフラクタル計算関数を選択します。*/
static int	calculate_fractal(t_fractol *f, double pr, double pi)
{
	int	nb_iter;

	nb_iter = 0;
	if (f->set_type == MANDELBROT)
		nb_iter = mandelbrot(pr, pi);
	else if (f->set_type == JULIA)
		nb_iter = julia(f, pr, pi);
	else if (f->set_type == BURNING_SHIP)
		nb_iter = burning_ship(pr, pi);
	else if (f->set_type == TRICORN)
		nb_iter = tricorn(pr, pi);
	else if (f->set_type == MANDELBOX)
		nb_iter = mandelbox(f, pr, pi);
	return (nb_iter);
}

/* render:
ウィンドウの各ピクセルを反復処理し、ピクセルの座標を複素数に変換して、
その数がフラクタルセットの一部であるかどうかを計算できるようにします。
複素数がフラクタルセットから拒否されるまでの反復回数によって、
ピクセルに適用される色が決まります。
すべてのピクセルが評価され、MLX画像に追加されると、
この関数はMLX画像をウィンドウに表示します。 */
void	render(t_fractol *f)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	int		nb_iter;

	mlx_clear_window(f->mlx, f->win);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pr = f->re_min + (double)x * (f->re_max - f->re_min) / WIDTH;
			pi = f->im_max + (double)y * (f->im_min - f->im_max) / HEIGHT;
			nb_iter = calculate_fractal(f, pr, pi);
			set_pixel_color(f, x, y, f->color_array[nb_iter]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
