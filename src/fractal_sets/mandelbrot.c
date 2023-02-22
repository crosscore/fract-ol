/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:47 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/21 20:29:24 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* mandelbrot:
複素数がマンデルブロ集合の一部であるかどうかをチェックします。
以前にピクセルの座標から変換された、ポイントの実座標と虚座標をパラメーターとして受け取ります。
数値がマンデルブロ集合を脱出するまでの反復回数を返します。
これは、カラーリングの決定に使用できます。 */
int	mandelbrot(double cr, double ci)
{
	int		i;
	double	re;
	double	im;
	double	temp;

	re = 0;
	im = 0;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		if ((re * re + im * im) > 4.0)
			break ;
		temp = 2 * re * im + ci;
		re = re * re - im * im + cr;
		im = temp;
		i++;
	}
	return (i);
}
/*
    How it works:

マンデルブロの公式は複素数を反復します。
	反復ごとに、Z は 2 乗されます。
		Z = Z * Z + c
	結果が無限大になる傾向がある場合、それはセットの一部ではないことを意味します。
	数回繰り返しても結果が小さいままである場合、その数はセットの一部です。

	Examples with regular numbers:
        ex.1: c = 1
            Z =  0
            Z =  0 *  0 + 1 = 1
            Z =  1 *  1 + 1 = 2
            Z =  2 *  2 + 1 = 5
            Z =  5 *  5 + 1 = 26
            Z = 26 * 26 + 1 = 677
            ... Grows to infinity.
            So 1 is NOT part of the Mandelbrot set.

        ex.2: c = -1
            Z =    0
            Z =    0 *    0 + (-1) = -1
            Z = (-1) * (-1) + (-1) =  0
            Z =    0 *    0 + (-1) = -1
            ... Result oscillates between -1 and 0
            So -1 is part of the Mandelbrot set.

	ここで無限大まで計算することはできませんが、
	Zの絶対値が2を超えると、無限大に近づく傾向があり、
	数値はマンデルブロ集合の一部ではありません。

    Since we are working with complex numbers, we need to calculate the
    real number re and the imaginary number im and evaluate both together.
    Multiplication of 2 complex numbers is complicated:
    (a + bi)2   = (a + bi) * (a + bi)
                = (a * a) + (a * bi) + (a * bi) + (bi * bi)
                = (a * a) - (bi * bi) + 2 * (a * bi)
    So the multiplication formula for the imaginary part is:
                    (a * a) - (bi * bi)
    And the multiplication formula for the real part is:
                    2 * a * bi

    See:    http://warp.povusers.org/Mandelbrot/
            https://www.mathsisfun.com/algebra/complex-number-multiply.html
*/
