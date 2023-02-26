/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:52 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 07:19:07 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* tricorn:
複素数が Tricorn セットの一部であるかどうかを確認します。
以前にピクセルの座標から変換された、ポイントの実座標と虚座標をパラメーターとして受け取ります。
Tricornフラクタル(マンデルバー)は、Mandelbrotフラクタルの歪みです。
乗算が異なることを除いて、同じ基本式を使用します。
mandelbrot: im =  2 * re * im + ci
Tricorn:    im = -2 * re * im + ci */
int	tricorn(double cr, double ci)
{
	int		n;
	double	re;
	double	im;
	double	tmp;

	re = cr;
	im = ci;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((re * re + im * im) > 4.0)
			break ;
		tmp = -2 * re * im + ci;
		re = re * re - im * im + cr;
		im = tmp;
		n++;
	}
	return (n);
}
