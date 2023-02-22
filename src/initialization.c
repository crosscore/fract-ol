/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:44 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/22 14:57:19 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* clean_init:
後で置き換えるデフォルト値で fractol データ構造を初期化します。
エラー検出に使用されます。*/
void	initialize_fractol(t_fractol *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->img = NULL;
	f->buf = NULL;
	f->set_type = -1;
	f->re_min = 0;
	f->re_max = 0;
	f->im_min = 0;
	f->im_max = 0;
	f->kr = 0;
	f->ki = 0;
	f->sx = 0;
	f->rx = 0;
	f->fx = 0;
	f->color_array = NULL;
	f->color_mode = -1;
	f->color = 0;
}

/* get_complex_layout:
複素数の軸をウィンドウの幅と高さにマップして、特定のピクセルと複素数の間の同等性を作成します。
	- Mandelbox setの実軸と虚軸の範囲は4 ~ -4であるため、
	フラクタルが中央に表示されるようにエッジがこれらの数値にマッピングされます。
	- Julia は、Mandelbrot や Burning Ship よりも右側に少しスペースが必要なので、
	マッピングも少しシフトする必要があります。
また、ウィンドウの比率が変化した場合にフラクタルの歪みを避けるために、
エッジの1つが常に他のエッジに従って計算されます。*/
void	get_complex_layout(t_fractol *f)
{
	if (f->set_type == MANDELBOX)
	{
		f->re_min = -4.0;
		f->re_max = 4.0;
		f->im_min = -4.0;
		f->im_max = f->im_min + (f->re_max - f->re_min) * HEIGHT / WIDTH;
	}
	else if (f->set_type == JULIA)
	{
		f->re_min = -2.0;
		f->re_max = 2.0;
		f->im_min = -2.0;
		f->im_max = f->im_min + (f->re_max - f->re_min) * HEIGHT / WIDTH;
	}
	else
	{
		f->re_min = -2.0;
		f->re_max = 1.0;
		f->im_max = -1.5;
		f->im_min = f->im_max + (f->re_max - f->re_min) * HEIGHT / WIDTH;
	}
}

/* init_img:
MLXイメージとカラーパレットを初期化します。
カラー パレットは、反復回数ごとにすべての色合いを格納するために使用され、
各ピクセルの色がイメージに格納され、プログラム ウィンドウに表示されます。*/
static void	init_img(t_fractol *f)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buf;

	f->color_array = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	if (!(f->color_array))
		clean_exit(msg("error initializing color scheme.", "", 1), f);
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!(f->img))
		clean_exit(msg("image creation error.", "", 1), f);
	buf = mlx_get_data_addr(f->img, &pixel_bits, &line_bytes, &endian);
	f->buf = buf;
}

/* reinit_image:
実行時にカラー パレットまたはフラクタル タイプが変更された場合、
MLXイメージをきれいに再初期化します。*/
void	reinit_img(t_fractol *f)
{
	if (f->mlx && f->img)
		mlx_destroy_image(f->mlx, f->img);
	if (f->color_array)
		free(f->color_array);
	if (f->buf)
		f->buf = NULL;
	init_img(f);
}

/* init:
新しい MLXインスタンス、new_windowを作成し、
フラクタルデータ構造にデフォルト値を設定します。*/
void	init(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		clean_exit(msg("MLX: error connecting to mlx.", "", 1), f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "--- Fract-ol ---");
	if (!f->win)
		clean_exit(msg("MLX: error creating window.", "", 1), f);
	f->sx = 2.0;
	f->rx = 0.5;
	f->fx = 1.0;
	get_complex_layout(f);
	color_shift(f);
}
