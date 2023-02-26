/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:44 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 19:20:54 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* initialize_t_fractol:
後で置き換えるデフォルト値でfractolデータ構造を初期化します。
エラー検出に使用されます。*/
void	initialize_t_fractol(t_fractol *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->img = NULL;
	f->img_buf = NULL;
	f->fractal_type = -1;
	f->re_min = 0;
	f->re_max = 0;
	f->im_min = 0;
	f->im_max = 0;
	f->jr = 0;
	f->ji = 0;
	f->xs = 0;
	f->xr = 0;
	f->xf = 0;
	f->color_array = NULL;
	f->color_mode = -1;
	f->base_color = 0;
}

/* set_fractal_viewport:
複素数の軸をウィンドウの幅と高さにマップして、特定のピクセルと複素数の間の同等性を作成します。
	- Mandelbox setの実軸と虚軸の範囲は4 ~ -4であるため、
	フラクタルが中央に表示されるようにエッジがこれらの数値にマッピングされます。
	- Julia は、Mandelbrot や Burning Ship よりも右側に少しスペースが必要なので、
	マッピングも少しシフトする必要があります。
また、ウィンドウの比率が変化しても、フラクタルが歪まないように比率を保つには？
以下の状態が比率が保たれていえるので以下の式を変形した結果が、f->im_maxの式となる。
(f->im_max - f->im_min) / (f->remax - f->re_min) = HEIGHT / WIDTH;
f->im_max = f->im_min + (f->re_max - f->re_min) * HEIGHT / WIDTH;　*/
void	set_fractal_viewport(t_fractol *f)
{
	if (f->fractal_type == JULIA)
	{
		f->re_min = -2.0;
		f->re_max = 2.0;
		f->im_min = -2.0;
		f->im_max = f->im_min + (f->re_max - f->re_min) * HEIGHT / WIDTH;
	}
	else if (f->fractal_type == MANDELBOX)
	{
		f->re_min = -4.0;
		f->re_max = 4.0;
		f->im_min = -4.0;
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

/* err_msg:
エラーメッセージを標準エラーに表示します。
指定されたerrnoを返します。*/
int	err_msg(char *str1, char *str2, int errno)
{
	ft_putstr_fd("Fractol: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	return (errno);
}

/* setup_fractol:
新しいMLXインスタンス、new_windowを作成し、
フラクタルデータ構造にデフォルト値を設定します。*/
void	setup_fractol(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		clean_exit(err_msg("Failed to initialize MLX library.", "", 1), f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "FRACT-OL");
	if (!f->win)
		clean_exit(err_msg("Failed to create window.", "", 1), f);
	f->xs = 2.0;
	f->xr = 0.5;
	f->xf = 1.0;
	set_fractal_viewport(f);
	change_color(f);
}

/* reinit_image:
実行時にカラーパレットまたはフラクタルタイプが変更された場合、
MLXイメージをきれいに再初期化します。*/
void	initialize_fractal(t_fractol *f)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;

	if (f->mlx && f->img)
		mlx_destroy_image(f->mlx, f->img);
	if (f->color_array)
		free(f->color_array);
	if (f->img_buf)
		f->img_buf = NULL;
	f->color_array = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	if (!(f->color_array))
		clean_exit(err_msg("Error initializing color scheme. \
			Failed to allocate memory.", "", 1), f);
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!(f->img))
		clean_exit(err_msg("Error creating image. \
			Failed to allocate memory.", "", 1), f);
	f->img_buf = mlx_get_data_addr(f->img, &pixel_bits, &line_bytes, &endian);
}
