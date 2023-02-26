/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:33 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 15:13:12 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* zoom:
複素数のエッジ値をズーム乗数(zoom_level)で調整することにより、
フラクタルのビューをズームインまたはズームアウトします。
その後、フラクタルを別の解像度で再度生成して、
ズームインまたはズームアウトしたように見せることができます。
ズーム乗数(zoom_level)が0.5のように小さい場合、ビューはズームインし、
2.0のように大きい場合はズームアウトします。*/
static void	zoom(t_fractol *f, double zoom_level)
{
	double	width;
	double	height;

	width = f->re_min - f->re_max;
	height = f->im_max - f->im_min;
	f->re_max = f->re_max + (width - zoom_level * width) / 2;
	f->re_min = f->re_max + zoom_level * width;
	f->im_min = f->im_min + (height - zoom_level * height) / 2;
	f->im_max = f->im_min + zoom_level * height;
}

/* move:
複素数のエッジ値を特定の方向に特定の距離だけ調整することで、
フラクタルのビューを移動します。*/
static void	move(t_fractol *f, double move_pixels, char direction)
{
	double	width;
	double	height;

	width = f->re_max - f->re_min;
	height = f->im_max - f->im_min;
	if (direction == 'R')
	{
		f->re_min += width * move_pixels;
		f->re_max += width * move_pixels;
	}
	else if (direction == 'L')
	{
		f->re_min -= width * move_pixels;
		f->re_max -= width * move_pixels;
	}
	else if (direction == 'D')
	{
		f->im_min -= height * move_pixels;
		f->im_max -= height * move_pixels;
	}
	else if (direction == 'U')
	{
		f->im_min += height * move_pixels;
		f->im_max += height * move_pixels;
	}
}

/* key_event_helper:
キーボードキーからのイベントを処理します。
- 1、2、3、4、5: フラクタルの切り替え
この関数は MLX フックに登録されており、
ユーザーが内部で何かを行うと、自動的に呼び出されます
キーボードを使用したプログラムウィンドウ。
有効なイベントが検出されると設定が調整され、フラクタル再描画されます。*/
static int	key_event_helper(int keycode, t_fractol *f)
{
	if (keycode == KEY_ONE && f->fractal_type != MANDELBROT)
		f->fractal_type = MANDELBROT;
	else if (keycode == KEY_TWO && f->fractal_type != JULIA)
		f->fractal_type = JULIA;
	else if (keycode == KEY_THREE && f->fractal_type != BURNING_SHIP)
		f->fractal_type = BURNING_SHIP;
	else if (keycode == KEY_FOUR && f->fractal_type != TRICORN)
		f->fractal_type = TRICORN;
	else if (keycode == KEY_FIVE && f->fractal_type != MANDELBOX)
		f->fractal_type = MANDELBOX;
	else if (keycode == KEY_SIX && f->fractal_type != MULTIBROT)
		f->fractal_type = MULTIBROT;
	else
		return (1);
	set_fractal_viewport(f);
	render_fractal(f);
	return (0);
}

/* key_event:
キーボードキーからのイベントを処理します。
	E or R : zoom
	- 矢印キー or WASD: 移動
	- スペース: カラーシフト
この関数は MLXフックに登録されており、
ユーザーが内部で何かを行うと、自動的に呼び出されます
キーボードを使用したプログラムウィンドウ。
有効なイベントが検出されると設定が調整され、フラクタルが再描画されます。*/
int	key_event(int keycode, t_fractol *f)
{
	if (keycode == KEY_ESC)
	{
		end_fractol(f);
		return (0);
	}
	else if (keycode == KEY_E)
		zoom(f, 0.5);
	else if (keycode == KEY_R)
		zoom(f, 2);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move(f, 0.2, 'U');
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move(f, 0.2, 'D');
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move(f, 0.2, 'L');
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(f, 0.2, 'R');
	else if (keycode == KEY_SPACE)
		change_color(f);
	else if (!key_event_helper(keycode, f))
		return (1);
	else
		return (1);
	render_fractal(f);
	return (0);
}

/* mouse_event:
マウスからのイベントを処理します。
	マウスホイール: zoom
	左クリック: Julia_shift
この関数はMLXフックに登録されており、
ユーザーがマウスを使用してプログラムウィンドウ内で何かを実行すると、自動的に呼び出されます。
有効なイベントが検出されると、設定が調整され、フラクタルが再描画されます。*/
int	mouse_event(int keycode, int mouse_x, int mouse_y, t_fractol *f)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(f, 0.5);
		mouse_x -= WIDTH / 2;
		mouse_y -= HEIGHT / 2;
		if (mouse_x < 0)
			move(f, (double)mouse_x * -1 / WIDTH, 'L');
		else if (mouse_x > 0)
			move(f, (double)mouse_x / WIDTH, 'R');
		if (mouse_y < 0)
			move(f, (double)mouse_y * -1 / HEIGHT, 'U');
		else if (mouse_y > 0)
			move (f, (double)mouse_y / HEIGHT, 'D');
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(f, 2);
	else if (keycode == MOUSE_BTN)
	{
		if (f->fractal_type == JULIA)
			julia_shift(mouse_x, mouse_y, f);
	}
	else
		return (0);
	render_fractal(f);
	return (0);
}
