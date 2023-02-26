/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:09 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 15:29:31 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* fill_color:
特定のストライプ間隔の色を設定します。
stripe = 2 の場合、カラーリングはパレットの反復をスキップします。
stripe = 3 の場合、カラーリングは 2 つのパレット反復をスキップします。*/
static void	set_color_stripes(t_fractol *f, int stripe_col, int stripe_interval)
{
	int	i;

	i = 0;
	while (i < MAX_ITERATIONS)
	{
		f->color_array[i] = stripe_col;
		i += stripe_interval;
	}
}

/* calculate_percent_color:
指定された色から一定の割合だけ離れた色を計算します。
各カラーチャネルは個別に計算する必要があります。
やや補完的な色を見つけることを目的としています。
(カラーホイールから選択された真の補色の場合、RGBではなく
HSLカラーを使用するようにこの関数を大幅に変更する必要があります)
0xFF << 24 : alpha (255 = 完全に不透明)
rgb[0] = red, rgb[1] = green, rgb[2] = blue */
int	calculate_percent_color(int base_color, double percent)
{
	int		rgb[3];
	int		new_rgb[3];
	double	percent_of_max_color;

	rgb[0] = (base_color >> 16) & 0xFF;
	rgb[1] = (base_color >> 8) & 0xFF;
	rgb[2] = (base_color >> 0) & 0xFF;
	percent_of_max_color = (percent / 100) * 256;
	new_rgb[0] = (rgb[0] + percent_of_max_color) - 256;
	new_rgb[1] = (rgb[1] + percent_of_max_color) - 256;
	new_rgb[2] = (rgb[2] + percent_of_max_color) - 256;
	return (0xFF << 24 | new_rgb[0] << 16 | new_rgb[1] << 8 | new_rgb[2]);
}

/* set_color_alternating_stripes:
ゼブラストライプの配色を設定します。
色は指定された色と最初の色から50%離れた補色の間で交互に表示されます。*/
void	set_color_alternating_stripes(t_fractol *f, int base_color)
{
	int	complementary_color;

	complementary_color = calculate_percent_color(base_color, 50);
	set_color_stripes(f, base_color, 1);
	set_color_stripes(f, complementary_color, 2);
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

/* set_color_three_stripes:
1つの色とその2つの三角色を使用して3本のストライプを設定する
指定された色、最初の色から33%離れた色、最初の色から66%離れた色
の3つの色の間で交互に表示されます。*/
void	set_color_three_stripes(t_fractol *f, int base_color)
{
	int		triad_colors[2];

	triad_colors[0] = calculate_percent_color(base_color, 33);
	triad_colors[1] = calculate_percent_color(base_color, 66);
	set_color_stripes(f, base_color, 1);
	set_color_stripes(f, triad_colors[0], 2);
	set_color_stripes(f, triad_colors[1], 3);
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

/* set_color_four_stripes:
1つの色とその3つの四分色を使用して4本のストライプを設定する
指定色、指定色から25%離れた色、50%離れた色、75%離れた色
の4つの色の間で交互に表示されます。*/
void	set_color_four_stripes(t_fractol *f, int base_color)
{
	int	tetrad_colors[3];

	tetrad_colors[0] = calculate_percent_color(base_color, 25);
	tetrad_colors[1] = calculate_percent_color(base_color, 50);
	tetrad_colors[2] = calculate_percent_color(base_color, 75);
	set_color_stripes(f, base_color, 1);
	set_color_stripes(f, tetrad_colors[0], 2);
	set_color_stripes(f, tetrad_colors[1], 3);
	set_color_stripes(f, tetrad_colors[2], 4);
	f->color_array[MAX_ITERATIONS - 1] = 0;
}
