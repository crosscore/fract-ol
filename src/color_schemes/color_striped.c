/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_striped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:09 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/21 18:24:38 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* fill_color:
特定のストライプ間隔の色を設定します。
stripe = 2 の場合、カラーリングはパレットの反復をスキップします。
stripe = 3 の場合、カラーリングは 2 つのパレット反復をスキップします。*/
static void	fill_color_stripe(t_fractol *f, int color, int stripe)
{
	int	i;

	i = 0;
	while (i < MAX_ITERATIONS)
	{
		f->color_array[i] = color;
		i += stripe;
	}
}

/* get_percent_color:
指定された色から一定の割合だけ離れた色を計算します。
各カラーチャネルは個別に計算する必要があります。
やや補完的な色を見つけることを目的としています。
(カラーホイールから選択された真の補色の場合、RGBではなく
HSLカラーを使用するようにこの関数を大幅に変更する必要があります)
Note: rgb[3] : rgb[0] = red, rgb[1] = green, rgb[2] = blue */
int	get_percent_color(int color, double percent)
{
	int		rgb[3];
	int		trgb[3];
	double	percentage;

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	percentage = (percent / 100) * 256;
	trgb[0] = (rgb[0] + percentage) - 256;
	trgb[1] = (rgb[1] + percentage) - 256;
	trgb[2] = (rgb[2] + percentage) - 256;
	return (0xFF << 24 | trgb[0] << 16 | trgb[1] << 8 | trgb[2]);
}

/* set_color_zebra:
ゼブラ ストライプの配色を設定します。
色は指定された色と最初の色から50%離れた補色の間で交互に表示されます。*/
void	set_color_zebra(t_fractol *f, int color)
{
	int	color2;

	color2 = get_percent_color(color, 50);
	fill_color_stripe(f, color, 1);
	fill_color_stripe(f, color2, 2);
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

/* set_color_triad:
縞模様の配色を設定します。
色は、指定された色、最初の色から33%離れた色、
最初の色から66%離れた色の3つの色の間で交互に表示されます。*/
void	set_color_triad(t_fractol *f, int color)
{
	int		triad[2];

	triad[0] = get_percent_color(color, 33);
	triad[1] = get_percent_color(color, 66);
	fill_color_stripe(f, color, 1);
	fill_color_stripe(f, triad[0], 2);
	fill_color_stripe(f, triad[1], 3);
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

/* set_color_tetra:
縞模様の配色を設定します。
指定色、指定色から25%離れた色、50%離れた色、75%離れた色
の4つの色の間で交互に表示されます。*/
void	set_color_tetra(t_fractol *f, int color)
{
	int	tetra[3];

	tetra[0] = get_percent_color(color, 25);
	tetra[1] = get_percent_color(color, 50);
	tetra[2] = get_percent_color(color, 75);
	fill_color_stripe(f, color, 1);
	fill_color_stripe(f, tetra[0], 2);
	fill_color_stripe(f, tetra[1], 3);
	fill_color_stripe(f, tetra[2], 4);
	f->color_array[MAX_ITERATIONS - 1] = 0;
}
