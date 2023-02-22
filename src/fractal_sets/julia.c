/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:34 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/21 18:24:54 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* julia_shift:
Julia計算の kr 値と ki 値を変更して、別のJuliaフラクタル形状を取得します。
この関数は、ユーザーがシーン上のポイントをクリックしたときに呼び出される必要があります。*/
int	julia_shift(int x, int y, t_fractol *f)
{
	f->kr = f->re_min + (double)x * (f->re_max - f->re_min) / WIDTH;
	f->ki = f->im_max + (double)y * (f->im_min - f->im_max) / HEIGHT;
	render(f);
	return (0);
}

/* julia:
複素数がジュリア集合の一部であるかどうかを確認します。
以前にピクセルの座標から変換された、ポイントの実座標と虚座標をパラメーターとして受け取ります。
数値がJuliaセットをエスケープするまでの反復回数を返します。
これは、カラーリングの決定に使用できます。*/
int	julia(t_fractol *f, double zr, double zi)
{
	int		n;
	double	tmp;

	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zi * zi + zr * zr) > 4.0)
			break ;
		tmp = 2 * zr * zi + f->ki;
		zr = zr * zr - zi * zi + f->kr;
		zi = tmp;
		n++;
	}
	return (n);
}
/*
	How it works:

ジュリア集合は、マンデルブロー集合と密接に関連しています。
その式は同じです。 異なるのはそれにプラグインする複素数です。

Mandelbrot は、zr と zi の開始値として 0 を使用し、
反復するたびにピクセル座標 (cr と ci) を追加します。

一方、Julia はピクセル座標を zr および zi として開始し、
反復するたびに別の複素数 (kr および ki) を追加します。

kr と ki の値によって、Julia の形状が決まります。
kr + ki がマンデルブロ集合の一部である場合、Julia は連続した立体になります。
kr + ki がマンデルブロー集合の一部でない場合、ジュリア フラクタルは分離した島の分離した集合になります。
kr + ki がマンデルブロ フラクタル境界に近いポイントである場合、
マンデルブロ フラクタルのそのポイントで見られるのと同じパターンがジュリア フラクタルに現れます。*/
