/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:33 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/22 12:34:33 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* zoom:
複素数のエッジ値をズーム乗数(zoom)で調整することにより、
フラクタルのビューをズームインまたはズームアウトします。
その後、フラクタルを別の解像度で再度生成して、
ズームインまたはズームアウトしたように見せることができます。
ズーム乗数(zoom)が0.5のように小さい場合、ビューはズームインし、
2.0のように大きい場合はズームアウトします。*/
static void	zoom(t_fractol *f, double zoom)
{
	double	center_r;
	double	center_i;

	center_r = f->re_min - f->re_max;
	center_i = f->im_max - f->im_min;
	f->re_max = f->re_max + (center_r - zoom * center_r) / 2;
	f->re_min = f->re_max + zoom * center_r;
	f->im_min = f->im_min + (center_i - zoom * center_i) / 2;
	f->im_max = f->im_min + zoom * center_i;
}

/* move:
複素数のエッジ値を特定の方向に特定の距離だけ調整することで、
フラクタルのビューを移動します。*/
static void	move(t_fractol *f, double distance, char direction)
{
	double	center_r;
	double	center_i;

	center_r = f->re_max - f->re_min;
	center_i = f->im_max - f->im_min;
	if (direction == 'R')
	{
		f->re_min += center_r * distance;
		f->re_max += center_r * distance;
	}
	else if (direction == 'L')
	{
		f->re_min -= center_r * distance;
		f->re_max -= center_r * distance;
	}
	else if (direction == 'D')
	{
		f->im_min -= center_i * distance;
		f->im_max -= center_i * distance;
	}
	else if (direction == 'U')
	{
		f->im_min += center_i * distance;
		f->im_max += center_i * distance;
	}
}

/* key_event_extend:
キーボード キーからのイベントを処理します。
- 1、2、3、4、5: フラクタルの切り替え
この関数は MLX フックに登録されており、
ユーザーが内部で何かを行うと、自動的に呼び出されます
キーボードを使用したプログラム ウィンドウ。
有効なイベントが検出されると設定が調整され、フラクタル再描画されます。*/
static int	key_event_extend(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ONE && mlx->set_type != MANDELBROT)
		mlx->set_type = MANDELBROT;
	else if (keycode == KEY_TWO && mlx->set_type != JULIA)
		mlx->set_type = JULIA;
	else if (keycode == KEY_THREE && mlx->set_type != BURNING_SHIP)
		mlx->set_type = BURNING_SHIP;
	else if (keycode == KEY_FOUR && mlx->set_type != TRICORN)
		mlx->set_type = TRICORN;
	else if (keycode == KEY_FIVE && mlx->set_type != MANDELBOX)
		mlx->set_type = MANDELBOX;
	else
		return (1);
	get_complex_layout(mlx);
	render(mlx);
	return (0);
}

/* key_event:
キーボード キーからのイベントを処理します。
	+ or - : zoom
	- 矢印キー or WASD: 移動
	- スペース: カラーシフト
この関数は MLX フックに登録されており、
ユーザーが内部で何かを行うと、自動的に呼び出されます
キーボードを使用したプログラム ウィンドウ。
有効なイベントが検出されると設定が調整され、フラクタルが再描画されます。*/
int	key_event(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ESC)
	{
		end_fractol(mlx);
		return (0);
	}
	else if (keycode == KEY_PLUS_E)
		zoom(mlx, 0.5);
	else if (keycode == KEY_MINUS_R)
		zoom(mlx, 2);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move(mlx, 0.2, 'U');
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move(mlx, 0.2, 'D');
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move(mlx, 0.2, 'L');
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(mlx, 0.2, 'R');
	else if (keycode == KEY_SPACE)
		color_shift(mlx);
	else if (!key_event_extend(keycode, mlx))
		return (1);
	else
		return (1);
	render(mlx);
	return (0);
}

/* mouse_event:
マウスからのイベントを処理します。
	マウスホイール: zoom
	左クリック: Julia_shift
この関数は MLX フックに登録されており、
ユーザーがマウスを使用してプログラムウィンドウ内で何かを実行すると、自動的に呼び出されます。
有効なイベントが検出されると、設定が調整され、フラクタルが再描画されます。*/
int	mouse_event(int keycode, int x, int y, t_fractol *mlx)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(mlx, 0.5);
		x -= WIDTH / 2;
		y -= HEIGHT / 2;
		if (x < 0)
			move(mlx, (double)x * -1 / WIDTH, 'L');
		else if (x > 0)
			move(mlx, (double)x / WIDTH, 'R');
		if (y < 0)
			move(mlx, (double)y * -1 / HEIGHT, 'U');
		else if (y > 0)
			move (mlx, (double)y / HEIGHT, 'D');
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(mlx, 2);
	else if (keycode == MOUSE_BTN)
	{
		if (mlx->set_type == JULIA)
			julia_shift(x, y, mlx);
	}
	else
		return (0);
	render(mlx);
	return (0);
}
