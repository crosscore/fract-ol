/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:42 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 07:20:08 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static double	box_fold(double v)
{
	if (v > 1)
		v = 2 - v;
	else if (v < -1)
		v = -2 - v;
	return (v);
}

static double	ball_fold(double r, double m)
{
	if (m < r)
		m = m / (r * r);
	else if (m < 1)
		m = 1 / (m * m);
	return (m);
}

int	mandelbox(t_fractol *f, double cr, double ci)
{
	int		n;
	double	re;
	double	im;
	double	mag;

	re = cr;
	im = ci;
	mag = 0;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		re = f->xf * box_fold(re);
		im = f->xf * box_fold(im);
		mag = sqrt(re * re + im * im);
		re = re * f->xs * ball_fold(f->xr, mag) + cr;
		im = im * f->xs * ball_fold(f->xr, mag) + ci;
		if (mag > 4)
			break ;
		n++;
	}
	return (n);
}
/*
マンデルボックス セットは通常3Dで表されますが、2Dでレンダリングすることもできます。
マンデルブロフラクタルの一種です。
マンデルブロ集合と同様に、空間内のすべての点に式を繰り返し適用して計算されます。

マンデルブロ方程式     : z = z^2 + c
マンデルボックスの方程式: v = s * ballFold(r, f*boxFold(v)) + c

- v 開始複素数 (変換されたピクセル座標)
- c 不変の複素数 (ピクセル座標)
- xs スケール乗数
- xr は最小半径
- xf は固定半径

box_fold関数は、マンデルボックスフラクタルを描画するための非線形変換の1つです。
この変換では、与えられた2次元座標を「箱」の中に押し込めることができます。
vが1より大きい場合、新しい値は2からvを引いた値になり、vが-1より小さい場合、
新しい値は-2からvを引いた値になります。

ball_fold関数は、マンデルボックスフラクタルの非線形変換のもう1つで、
与えられた2次元座標を球の中に押し込めます。
rは球の半径で、mは座標の「マグニチュード」で、mがrより小さい場合、
新しい値はmをrの2乗で割ったものになり、mが1より小さい場合、
新しい値は1をmの2乗で割ったものになります。
これにより、座標が球の内側にある場合、それらはより小さな範囲に「圧縮」され、
球の外側にある場合はより広い範囲に「引き伸ばされ」ます。

The standard Mandelbox uses this formula with s=2, r=0.5 and f=1.
*/
