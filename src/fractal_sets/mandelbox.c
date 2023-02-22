/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:42 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/22 01:09:29 by ysakahar         ###   ########.fr       */
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

/* mandelbox:
複素数がマンデルボックス集合の一部であるかどうかをチェックします。
以前にピクセルの座標から変換された、ポイントの実座標と虚座標をパラメーターとして受け取ります。
数値がマンデルボックス セットをエスケープするまでの反復回数を返します。
これは、カラーリングの決定に使用できます。 */
int	mandelbox(t_fractol *f, double cr, double ci)
{
	int		n;
	double	vr;
	double	vi;
	double	mag;

	vr = cr;
	vi = ci;
	mag = 0;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		vr = f->fx * box_fold(vr);
		vi = f->fx * box_fold(vi);
		mag = sqrt(vr * vr + vi * vi);
		vr = vr * f->sx * ball_fold(f->rx, mag) + cr;
		vi = vi * f->sx * ball_fold(f->rx, mag) + ci;
		if (sqrt(mag) > 2)
			break ;
		n++;
	}
	return (n);
}
/*
使い方：
マンデルボックス セットは通常3Dで表されますが、2Dでレンダリングすることもできます。
マンデルブロ フラクタルの一種です。
マンデルブロ集合と同様に、空間内のすべての点に式を繰り返し適用して計算されます。

マンデルブロ方程式は次のとおりです。 z = z2 + c
マンデルボックスの方程式は次のとおりです。 v = s * ballFold(r, f*boxFold(v)) + c
どこ：
- v は開始複素数 (変換されたピクセル座標) です。
- c は不変の複素数 (ピクセル座標)
- s はスケール乗数です
- r は最小半径
- f は固定半径です

boxFold(v) は、各軸 a について次のことを意味します。

		if v[a] > 1
    		v[a] =  2 - v[a]
		else if v[a] < -1
    		v[a] = -2 - v[a]

	ballFold(r, v) means for v's magnitude m:

		if m < r
    		m = m/r^2
		else if m < 1
			m = 1/m^2

	The standard Mandelbox uses this formula with s=2, r=0.5 and f=1.
	See:	https://sites.google.com/site/mandelbox/what-is-a-mandelbox
			https://en.wikipedia.org/wiki/Mandelbox
*/
