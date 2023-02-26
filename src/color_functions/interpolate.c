/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:17:49 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 15:30:08 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* interpolate（補間する）
この関数は、2つの16進カラーコードの間を「補間する」もので、
RGB値に分解された各カラーチャンネルの値を計算するために使用されます。
具体的には、開始値と終了値の差分を、
指定されたステップ数と総ステップ数の比率(fraction＝分数、補間の段階数)に乗算し、
開始値に加算することで、補間値を計算します。
fraction = 現在のステップ数 / 総ステップ数
(end_rgb - start_rgb) * fraction + start_rgb
endValueは補間したい終了カラーの値、startValueは補間したい開始カラーの値、
なお、小数点以下の桁数を指定するfractionパラメータが提供され、
その値に基づいて補間されたカラーコードが返されます。
Note: rgb[3] : [0] = red, [1] = green, [2] = blue
Alpha: 0(透明) ~ 255(不透明)
Alpha		R		 G		  B
11111111 00000010 11111111 00000001
00000000 00000000 00000000 11111111 (000000FF = MASK)
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
	start_rgb[0] += (end_rgb[0] - start_rgb[0]) * fraction;
	start_rgb[1] += (end_rgb[1] - start_rgb[1]) * fraction;
	start_rgb[2] += (end_rgb[2] - start_rgb[2]) * fraction;
	return (0xFF << 24 | start_rgb[0] << 16 | start_rgb[1] << 8 | start_rgb[2]);
}

/* set_color_gradient:
複数の色を受け取り、それらの色を滑らかにグラデーションさせながら配列に設定する
色は、それぞれの間のスムーズな移行のために補間されます。
より大きな配列をキャストし、含まれる色の数を指定することで4つ以上の色を提供することが可能。
MAX_ITERATIONSが100, n=4の場合、最初にiは0で初期化され、内側のwhileループは100/7=14回実行される。
この時点で、i + jは50になり、MAX_ITERATIONSと等しくなるため、
外側のwhileループは実行されず、関数は終了する。つまり、外側のwhileループは1回だけ実行される。
*/
void	set_color_gradient(t_fractol *f, int base_colors[4], int n)
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
			f->color_array[i + j] = \
				interpolate(base_colors[x], base_colors[x + 1], fraction);
			j++;
		}
		x++;
		i += j;
	}
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

/* set_color_monochrome:
単色を受け取り、黒から指定された色までと指定された色から白までの2つのグラデーションを設定する
外側のwhile文の実行が2回目になるとbase_colorとcolorは両方白になる。
f->color_array[MAX_ITERATIONS - 1] = 0 は、
f->color_array配列の最後の要素に0を代入することで終端を示している。*/
void	set_color_monochrome(t_fractol *f, int base_color)
{
	int		i;
	int		j;
	double	fraction;
	int		color;

	color = 0x000000;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while (j < MAX_ITERATIONS / 2)
		{
			fraction = (double)j / (MAX_ITERATIONS / 2);
			f->color_array[i + j] = interpolate(color, base_color, fraction);
			j++;
		}
		color = base_color;
		base_color = 0xFFFFFF;
		i += j;
	}
	f->color_array[MAX_ITERATIONS -1] = 0;
}
