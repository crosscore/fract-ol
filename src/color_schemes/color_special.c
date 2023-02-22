/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:04 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/21 18:23:55 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
注意: これらの配色関数はまったくの偶然によって作成されたものであり、
提供されたすべての色で常にうまく機能するとは限りません。
それらは、予測できない結果をもたらす可能性のあるFFFFFF または 000000を超えるプッシュに依存しています。

彼らが仕事をするとき、彼らは非常に興味深く美しいカラーリングを作成しますが、
それがこのプロジェクトからカットされていない理由です.

通常、中間の色、特に次のような色でうまく機能します。
9966FF 33FF33 FF6666 CCCC00 CC6600

ただし、次のようなエッジの色ではうまく機能しません。
000000 FFFFFF 00FF00 FF0000 0000FF FFFF00 */
#include "../includes/fractol.h"


void	set_color_opposites(t_fractol *f, int color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		f->color_array[i] = 0;
		r += i % 0xFF;
		g += i % 0xFF;
		b += i % 0xFF;
		f->color_array[i] = 0xFF << 24 | r << 16 | g << 8 | b;
	}
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

void	set_color_contrasted(t_fractol *f, int color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		f->color_array[i] = 0;
		if (r != 0xFF)
			r += i % 0xFF;
		if (g != 0xFF)
			g += i % 0xFF;
		if (b != 0xFF)
			b += i % 0xFF;
		f->color_array[i] = 0xFF << 24 | r << 16 | g << 8 | b;
	}
	f->color_array[MAX_ITERATIONS - 1] = 0;
}

void	set_color_graphic(t_fractol *f, int color)
{
	int	i;
	int	rgb[3];

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
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
