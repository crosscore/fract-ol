/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:55 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/21 20:23:09 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* skip_space_sign_0x:
スペース、「+」記号文字、および「0x」または「0X」をスキップして、
16進数のカラーコード文字列を解析します。*/
static int	skip_space_sign_0x(char *color)
{
	int	i;

	i = 0;
	while (ft_isspace(color[i]))
		i++;
	if (color[i] == '+')
		i++;
	if (color[i] == '0' && (color[i + 1]
			&& (color[i + 1] == 'x' || color[i] == 'X')))
		i = i + 2;
	return (i);
}

/* ft_atox_color:
16進数のカラーコード文字列を整数に変換します。
有効: "RRGGBB"、"0XRRGGBB"、"rrggbb"、" +rrggbb"
無効: 「-RRGGBB」「RRGGBB-」「RR GG BB」
文字列が有効な16進カラーコードでない場合は、エラーが表示されます。
変換されたintを返します。エラーが発生した場合は-1。*/
static int	ft_atox_color(t_fractol *f, char *color)
{
	int	i;
	int	x;
	int	n;

	n = 0;
	i = 0;
	i = skip_space_sign_0x(color);
	x = 0;
	while (color[i] && ft_ishexdigit(color[i]))
	{
		if (ft_isdigit(color[i]))
			n = (n * 16) + (color[i] - '0');
		else
			n = (n * 16) + (ft_toupper(color[i]) - 'A' + 10);
		i++;
		x++;
	}
	if (x == 6 && !color[i])
		return (n);
	else
		help_msg(f);
	return (-1);
}

/* get_color:
プログラムの起動時に引数として指定された色のオプションを取得します。
色が指定されていない場合は、使用するデフォルト値を設定します。*/
void	get_color(t_fractol *f, int ac, char **av)
{
	if (f->set_type == JULIA && ac == 5)
		f->color = ft_atox_color(f, av[4]);
	else if (f->set_type != JULIA && ac == 3)
		f->color = ft_atox_color(f, av[2]);
	if (ac == 2 || (f->set_type == JULIA && ac == 4))
		f->color = 0x9966FF;
}

/* skip_space_sign:
スペース、「+」および「-」記号文字をスキップし、
「-」記号が検出された場合は is_neg 変数を設定します。
Juliaのfloat値を表す文字列を解析するために使用されます。*/
static int	skip_space_sign(char *str, int *is_neg)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*is_neg *= -1;
		i++;
	}
	return (i);
}

/* ft_atof:
文字列をfloat(10 進数)に変換します。
プログラムの引数として与えられたJuliaの開始値を解析するために使用されます。
変換されたdouble、またはエラーの場合は-42を返します
(Juliaは2.0から-2.0の間の値のみを受け入れます) */
double	ft_atof(char *str)
{
	int		i;
	double	nb;
	int		is_neg;
	double	div;

	nb = 0;
	div = 0.1;
	is_neg = 1;
	i = skip_space_sign(str, &is_neg);
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		nb = (nb * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = nb + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
	return (nb * is_neg);
}
