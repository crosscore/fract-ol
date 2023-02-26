/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:28 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 10:40:07 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* burning_ship:
複素数がBurning Shipセットの一部であるかどうかを確認します。
以前にピクセルの座標から変換された、ポイントの実座標と虚座標をパラメーターとして受け取ります。
数値がBurning Shipセットから抜けるまでの反復回数を返します。
Burning Ship フラクタルは、Mandelbrot フラクタルの歪みです。
同じ方程式を使用してセットを計算しますが、各反復でzrとziの絶対値を使用します。*/
int	burning_ship(double cr, double ci)
{
	int		i;
	double	re;
	double	im;
	double	tmp;

	re = 0;
	im = 0;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		if ((re * re + im * im) > 4.0)
			break ;
		re = fabs(re);
		im = fabs(im);
		tmp = 2 * re * im + ci;
		re = re * re - im * im + cr;
		im = tmp;
		i++;
	}
	return (i);
}
