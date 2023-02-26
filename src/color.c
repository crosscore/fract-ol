/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:27 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 15:33:22 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* color_shift_special:
color_shift関数の拡張。カラーパターンを変更します。
その後、フラクタルを別の色効果で再度レンダリングできます。
0xFF0000,0xFF7F00,0xFFFF00,0x00FF00,0x0000FF,0x4B0082,0x9400D3,0xFFFFFF
0xFFFFFF,0x9400D3,0x4B0082,0x0000FF,0x00FF00,0xFFFF00,0xFF7F00,0xFF0000
0x333333, 0x9400D3, 0xFFFFFF, 0x0000FF, 0x00FF00, 0xFFFF00, 0xFF7F00, 0xFF0000
*/
static void	change_color_special(t_fractol *f)
{
	int	base_color;

	if (f->base_color == 0xFFFFFF)
		base_color = 0xCCCCCC;
	else
		base_color = f->base_color;
	if (f->color_mode == 5)
		set_color_contrasted(f, base_color);
	else if (f->color_mode == 6)
		set_color_opposites(f, f->base_color);
	else if (f->color_mode == 7)
		set_color_graphical(f, f->base_color);
	else if (f->color_mode == 8)
		set_color_gradient(f, (int [8]){0x000000, 0x0000FF, 0xFF0000, 0x9400D3,
			0x00FF00, 0xFFFF00, 0xFF7F00, 0xFFFFFF}, 8);
}

/* change_color:
MLXイメージを再初期化し、カラーパターンを変更します。
その後、フラクタルを別の色効果で再度レンダリングできます。*/
void	change_color(t_fractol *f)
{
	int	base_color;

	f->color_mode = (f->color_mode + 1) % 9;
	initialize_fractal(f);
	if (f->base_color == 0x000000)
		base_color = 0x333333;
	else
		base_color = f->base_color;
	if (f->color_mode == 0)
		set_color_monochrome(f, base_color);
	else if (f->color_mode == 1)
		set_color_gradient(f, (int [4]){0x000000, base_color,
			calculate_percent_color(f->base_color, 50), 0xFFFFFF}, 4);
	else if (f->color_mode == 2)
		set_color_alternating_stripes(f, f->base_color);
	else if (f->color_mode == 3)
		set_color_three_stripes(f, f->base_color);
	else if (f->color_mode == 4)
		set_color_four_stripes(f, f->base_color);
	else
		change_color_special(f);
}
