/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:28 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/21 18:22:54 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* burning_ship:
複素数がBurning Shipセットの一部であるかどうかを確認します。
以前にピクセルの座標から変換された、ポイントの実座標と虚座標をパラメーターとして受け取ります。
数値がBurning Shipセットから抜けるまでの反復回数を返します。
これはカラーリングの決定に使用できます。*/
int	burning_ship(double cr, double ci)
{
	int		n;
	double	zr;
	double	zi;
	double	tmp;

	zr = 0;
	zi = 0;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		zr = fabs(zr);
		zi = fabs(zi);
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		n++;
	}
	return (n);
}
/*
	How it works:
Burning Ship フラクタルは、Mandelbrot フラクタルの歪みです。
同じ方程式を使用してセットを計算しますが、各反復でzrとziの絶対値を使用します。
*/
