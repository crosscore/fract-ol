/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_interpolated.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:17:49 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/21 18:23:45 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* interpolate:
この関数は、2つの16進カラーコードの間を補間するもので、
RGB値に分解された各カラーチャンネルの値を計算するために使用されます。具体的には、開始値と終了値の差分を、
指定されたステップ数と総ステップ数の比率に乗算し、開始値に加算することで、補間値を計算します。
式は以下の通りです。
(endValue - startValue) * stepNumber / lastStepNumber + startValue
endValue は補間したい終了カラーの値、startValueは補間したい開始カラーの値、
stepNumberは現在のステップ数、lastStepNumberは総ステップ数、つまり補間の段階数を表します。
なお、小数点以下の桁数を指定するfractionパラメータが提供され、
その値に基づいて補間されたカラーコードが返されます。
Note: rgb[3] : [0] = red, [1] = green, [2] = blue
Alpha: 0(透明) ~ 255(不透明)
Alpha		R		 G		  B
11111111 00000010 11111111 00000001
00000000 00000000 00000000 11111111 (000000FF = MASK)

static int interpolate(int start_color, int end_color, double fraction)
{
	union u_color
	{
		int color;
		unsigned char channel[4];
	} start, end;

	start.color = start_color;
	end.color = end_color;
	for (int i = 0; i < 3; i++)
		start.channel[i] = (end.channel[i] - start.channel[i]) * fraction + start.channel[i];
	return (start.color);
}
*/
static int	interpolate(int start_color, int end_color, double fraction)
{
	int	start_rgb[3];
	int	end_rgb[3];

	start_rgb[0] = ((start_color >> 16) & 0xFF);
	start_rgb[1] = ((start_color >> 8) & 0xFF);
	start_rgb[2] = ((start_color >> 0) & 0xFF);
	end_rgb[0] = ((end_color >> 16) & 0xFF);
	end_rgb[1] = ((end_color >> 8) & 0xFF);
	end_rgb[2] = ((end_color >> 0) & 0xFF);
	start_rgb[0] = (end_rgb[0] - start_rgb[0]) * fraction + start_rgb[0];
	start_rgb[1] = (end_rgb[1] - start_rgb[1]) * fraction + start_rgb[1];
	start_rgb[2] = (end_rgb[2] - start_rgb[2]) * fraction + start_rgb[2];
	return (0xFF << 24 | start_rgb[0] << 16 | start_rgb[1] << 8 | start_rgb[2]);
}

/* set_color_mono:
単色配色を設定します。
色の範囲は、黒から指定された色、フラクタル境界付近の白までです。*/
void	set_color_mono(t_fractol *f, int color)
{
	int		i;
	int		j;
	double	fraction;
	int		color1;
	int		color2;

	color1 = 0x000000;
	color2 = color;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while (j < MAX_ITERATIONS / 2)
		{
			fraction = (double)j / (MAX_ITERATIONS / 2);
			f->color_array[i + j] = interpolate(color1, color2, fraction);
			j++;
		}
		color1 = color2;
		color2 = 0xFFFFFF;
		i += j;
	}
	f->color_array[MAX_ITERATIONS -1] = 0;
}

/* set_color_multiple:
マルチカラー配色を設定します。
色の範囲は、配列で提供される最初の色から最後の色までです。
色は、それぞれの間のスムーズな移行のために補間されます。
より大きな配列をキャストし、含まれる色の数を指定することで4つ以上の色を提供することができます。*/
void	set_color_multiple(t_fractol *f, int colors[4], int n)
{
	int		i;
	int		j;
	int		x;
	double	fraction;

	i = 0;
	x = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while ((i + j) < MAX_ITERATIONS && j < (MAX_ITERATIONS / (n - 1)))
		{
			fraction = (double)j / (MAX_ITERATIONS / (n - 1));
			f->color_array[i + j] = interpolate(colors[x], colors[x + 1], fraction);
			j++;
		}
		x++;
		i += j;
	}
	f->color_array[MAX_ITERATIONS - 1] = 0;
}
