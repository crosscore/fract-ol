/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:52 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/22 14:58:02 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* tricorn:
複素数が Tricorn セットの一部であるかどうかを確認します。
以前にピクセルの座標から変換された、ポイントの実座標と虚座標をパラメーターとして受け取ります。
数値が Tricorn セットをエスケープするまでの反復回数を返します。
これを使用してカラーリングを決定できます。*/
int	tricorn(double cr, double ci)
{
	int		n;
	double	zr;
	double	zi;
	double	tmp;

	zr = cr;
	zi = ci;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		tmp = -2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		n++;
	}
	return (n);
}
/*
使い方：
Tricornフラクタル(マンデルバー)は、Mandelbrotフラクタルの歪みです。
乗算が異なることを除いて、同じ基本式を使用します。
mandelbrot: zi =  2 * zr * zi + ci
Tricorn:    zi = -2 * zr * zi + ci*/
