/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:04 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 17:35:02 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
通常、中間の色、特に次のような色でうまく機能します。
9966FF 33FF33 FF6666 CCCC00 CC6600
ただし、次のようなエッジの色ではうまく機能しません。
000000 FFFFFF 00FF00 FF0000 0000FF FFFF00 */

#include "../includes/fractol.h"

/*「グラフィカルな色を設定する」
色相環を均等に回転させ、視覚的に鮮明であることを目指している
たとえオーバーフローが起きてもRGB値は00~FFの範囲をとるだけで
プログラム上の問題は起きない*/
void	set_color_graphical(t_fractol *f, int base_color)
{
	int	i;
	int	rgb[3];

	rgb[0] = (base_color >> 16) & 0xFF;
	rgb[1] = (base_color >> 8) & 0xFF;
	rgb[2] = (base_color >> 0) & 0xFF;
	i = -1;
	while (rgb[0] < 0x33 || rgb[1] < 0x33 || rgb[2] < 0x33)
	{
		if (rgb[0] != 0xFF)
			rgb[0]++;
		if (rgb[1] != 0xFF)
			rgb[1]++;
		if (rgb[2] != 0xFF)
			rgb[2]++;
	}
	while (++i < MAX_ITERATIONS)
	{
		f->color_array[i] = 0;
		rgb[0] -= i % 0xFF;
		rgb[1] -= i % 0xFF;
		rgb[2] -= i % 0xFF;
		f->color_array[i] = 0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	}
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

/*
RGB各色値について1の補数を使って対称的な色を生成する
~演算子は、ビット反転演算子。オペランドのビットを反転させる */
void	set_color_opposites(t_fractol *f, int base_color)
{
	int	i;
	int	rgb[3];

	rgb[0] = (base_color >> 16) & 0xFF;
	rgb[1] = (base_color >> 8) & 0xFF;
	rgb[2] = (base_color >> 0) & 0xFF;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		f->color_array[i] = 0;
		rgb[0] = ~rgb[0];
		rgb[1] = ~rgb[1];
		rgb[2] = ~rgb[2];
		f->color_array[i] = 0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	}
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

/*RGB各色値について色相環を回転させることで、
色のコントラスト(対比)を高めたvividな配色を生成する
rgb[0]=4byte(32bit)
rgb[0] += i % 0xFF; の結果は常に0~255の間となるためオーバーフロー対策である*/
void	set_color_contrasted(t_fractol *f, int base_color)
{
	int	i;
	int	rgb[3];

	rgb[0] = (base_color >> 16) & 0xFF;
	rgb[1] = (base_color >> 8) & 0xFF;
	rgb[2] = (base_color >> 0) & 0xFF;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		f->color_array[i] = 0;
		if (rgb[0] != 0xFF)
			rgb[0] += i % 0xFF;
		if (rgb[1] != 0xFF)
			rgb[1] += i % 0xFF;
		if (rgb[2] != 0xFF)
			rgb[2] += i % 0xFF;
		f->color_array[i] = 0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	}
	f->color_array[MAX_ITERATIONS - 1] = 0;
}
