/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:00 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 19:16:07 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* set_pixel_color:
MLXイメージマップの1つのピクセルに色を追加します。
MLX画像は、1ピクセルあたり32bit(4byte)で構成されています。
そのためx_pixel * + 4 y_pixel * 4 * 900をすることでxバイト目に保存されているかがわかる。
つまりimg_buf[]配列は、1pixel=4byteとして横一列に順番にデータを格納していることとなる。
よって、img_buf[x_pixel * 4 + y_pixel * 4 * 900]で、img_bufの何番目に保存されているかを
確認することが可能。
色の整数は、ここでは右から左に格納され、0xAARRGGBBの形式になっています。
8ビットは、アルファ(透明度)、赤、緑、青の各色成分をエンコードします。
ビットシフト:
	- BB >>  0 (0x000000BB)
	- GG >>  8 (0x0000GG00)
	- RR >> 16 (0x00RR0000)
	- AA >> 24 (0xAA000000) */
static void	set_pixel_color(t_fractol *f, int x_pixel, int y_pixel, int color)
{
	f->img_buf[x_pixel * 4 + y_pixel * WIDTH * 4] = color;
	f->img_buf[x_pixel * 4 + y_pixel * WIDTH * 4 + 1] = color >> 8;
	f->img_buf[x_pixel * 4 + y_pixel * WIDTH * 4 + 2] = color >> 16;
	f->img_buf[x_pixel * 4 + y_pixel * WIDTH * 4 + 3] = color >> 24;
}

/* calculate_fractal:
現在のフラクタルセットに応じて、正しいフラクタル計算関数を選択します。*/
static int	calculate_fractal(t_fractol *f, double re, double im)
{
	int	iterations;

	iterations = 0;
	if (f->fractal_type == MANDELBROT)
		iterations = mandelbrot(re, im);
	else if (f->fractal_type == JULIA)
		iterations = julia(f, re, im);
	else if (f->fractal_type == BURNING_SHIP)
		iterations = burning_ship(re, im);
	else if (f->fractal_type == TRICORN)
		iterations = tricorn(re, im);
	else if (f->fractal_type == MANDELBOX)
		iterations = mandelbox(f, re, im);
	else if (f->fractal_type == MULTIBROT)
		iterations = multibrot(re, im);
	return (iterations);
}

/* render_fractal:
ウィンドウの各ピクセルを反復処理し、ピクセルの座標を複素数に変換し、
その数がフラクタルセットの一部であるかどうかを計算できるようにします。
複素数がフラクタルセットを超えるまでの反復回数により、ピクセルに適用される色が決まります。
全ピクセルが評価され、MLX画像に追加されるとこの関数はMLX画像をウィンドウ表示します。*/
void	render_fractal(t_fractol *f)
{
	int		x_pixel;
	int		y_pixel;
	int		iterations;
	double	re;
	double	im;

	mlx_clear_window(f->mlx, f->win);
	y_pixel = 0;
	while (y_pixel < HEIGHT)
	{
		x_pixel = 0;
		while (x_pixel < WIDTH)
		{
			re = f->re_min + (double)x_pixel * (f->re_max - f->re_min) / WIDTH;
			im = f->im_max + (double)y_pixel * (f->im_min - f->im_max) / HEIGHT;
			iterations = calculate_fractal(f, re, im);
			set_pixel_color(f, x_pixel, y_pixel, f->color_array[iterations]);
			x_pixel++;
		}
		y_pixel++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

/*
「f->img」変数は、フラクタルの描画に使用されます。
以前に、initialize_fractal関数でmlx_new_image関数を使用し、
f->img変数には新しいイメージオブジェクトが格納された状態でした。
フラクタルの描画処理中に、各ピクセルのRGBA値がf->img_buf配列に設定され、
f->img変数はこのイメージデータを表示します。

mlx_put_image_to_window関数は、
f->img変数に格納されたイメージデータをf->winウィンドウ上の指定された座標に描画します。
引数として、f->mlxはMLXコネクションオブジェクト、f->winは対象のウィンドウオブジェクト、
f->imgは描画するイメージオブジェクトを指定します。
4番目の引数には、x座標とy座標が指定されます。
この例では、(0, 0) と指定されているため、イメージがウィンドウの左上隅から描画されます。

f->img変数には、initialize_fractal関数でmlx_new_image関数が呼び出されたときに、
空のイメージオブジェクトが格納されていました。
render_fractal関数内で、各ピクセルのRGBA値がf->img_buf配列に設定された後、
mlx_put_image_to_window関数が呼び出され、
f->img変数に格納されたイメージデータがf->winウィンドウに描画されます。
*/