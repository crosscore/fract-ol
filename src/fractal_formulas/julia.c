/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:34 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 07:21:22 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* julia_shift:
Julia計算の jr 値と ji 値を変更して、別のJuliaフラクタル形状を取得します。
この関数は、ユーザーがシーン上のポイントをクリックしたときに呼び出される必要があります。*/
int	julia_shift(int mouse_x, int mouse_y, t_fractol *f)
{
	f->jr = f->re_min + (double)mouse_x * (f->re_max - f->re_min) / WIDTH;
	f->ji = f->im_max + (double)mouse_y * (f->im_min - f->im_max) / HEIGHT;
	render_fractal(f);
	return (0);
}

/* julia:
複素数がジュリア集合の一部であるかどうかを確認します。
以前にピクセルの座標から変換された、ポイントの実座標と虚座標をパラメーターとして受け取ります。
数値がJuliaセットをエスケープするまでの反復回数を返します。
これは、カラーリングの決定に使用できます。*/
int	julia(t_fractol *f, double cr, double ci)
{
	int		i;
	double	tmp;

	i = 0;
	while (i < MAX_ITERATIONS)
	{
		if ((ci * ci + cr * cr) > 4.0)
			break ;
		tmp = 2 * cr * ci + f->ji;
		cr = cr * cr - ci * ci + f->jr;
		ci = tmp;
		i++;
	}
	return (i);
}

/*
ジュリア集合は、マンデルブロー集合と密接に関連しています。
その式は同じです。異なるのはそれにプラグインする複素数です。

Mandelbrotは、crとciの開始値として0を使用し、
反復するたびにピクセル座標 (crとci) を追加します。

一方、Juliaはピクセル座標を cr および ci として開始し、
反復するたびに別の複素数 (jr および ji) を追加します。

jr と ji の値によって、Juliaの形状が決まります。
jr + ji がマンデルブロ集合の一部である場合、Juliaは連続した立体になります。
jr + ji がマンデルブロー集合の一部でない場合、ジュリアフラクタルは分離した島の分離した集合になります。
jr + ji がマンデルブロフラクタル境界に近いポイントである場合、
マンデルブロ集合のそのポイントで見られるのと同じパターンがジュリアフラクタルに現れます。*/