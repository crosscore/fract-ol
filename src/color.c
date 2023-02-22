/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:27 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/22 14:57:00 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* color_shift_special:
color_shift関数の拡張。カラーパターンを変更します。
その後、フラクタルを別の色効果で再度レンダリングできます。*/
static void	color_shift_special(t_fractol *f)
{
	int	alt_color;

	if (f->color == 0xFFFFFF)
		alt_color = 0xCCCCCC;
	else
		alt_color = f->color;
	if (f->color_mode == 5)
		set_color_contrasted(f, alt_color);
	else if (f->color_mode == 6)
		set_color_opposites(f, f->color);
	else if (f->color_mode == 7)
		set_color_graphic(f, f->color);
	else if (f->color_mode == 8)
		set_color_multiple(f, (int [8]){0xFF0000, 0xFF7F00, 0xFFFF00,
			0x00FF00, 0x0000FF, 0x4B0082, 0x9400D3, 0xFFFFFF}, 8);
}

/* color_shift_striped:
color_shift 関数の拡張。カラーパターンを変更します。
その後、フラクタルを別の色効果で再度レンダリングできます。*/
static void	color_shift_striped(t_fractol *f)
{
	if (f->color_mode == 2)
		set_color_zebra(f, f->color);
	else if (f->color_mode == 3)
		set_color_triad(f, f->color);
	else if (f->color_mode == 4)
		set_color_tetra(f, f->color);
	else
		color_shift_special(f);
}

/* color_shift:
MLXイメージを再初期化し、カラーパターンを変更します。
その後、フラクタルを別の色効果で再度レンダリングできます。*/
void	color_shift(t_fractol *f)
{
	int	alt_color;

	f->color_mode = (f->color_mode + 1) % 9;
	reinit_img(f);
	if (f->color == 0x000000)
		alt_color = 0x333333;
	else
		alt_color = f->color;
	if (f->color_mode == 0)
		set_color_mono(f, alt_color);
	else if (f->color_mode == 1)
		set_color_multiple(f, (int [4]){0x000000, alt_color,
			get_percent_color(f->color, 50), 0xFFFFFF}, 4);
	else
		color_shift_striped(f);
}
