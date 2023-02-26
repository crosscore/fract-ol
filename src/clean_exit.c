/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:19:06 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 07:29:16 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* clean_exit:
MLXループを終了してディスプレイを破棄する前に、
ウィンドウ、MLXイメージ、MLXインスタンスを破棄し、カラーパレットを解放します。
指定された終了コードでプロセスを終了します。*/
void	clean_exit(int exit_code, t_fractol *f)
{
	if (!f)
		exit(exit_code);
	if (f->color_array)
		free(f->color_array);
	if (f->img)
		mlx_destroy_image(f->mlx, f->img);
	if (f->win && f->mlx)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx)
	{
		mlx_loop_end(f->mlx);
		mlx_destroy_display(f->mlx);
		free(f->mlx);
	}
	exit(exit_code);
}

/* end_fractol:
プログラムを正常に終了します。
この関数は MLXフックに登録されています。
ユーザーが右ボタンを押すたびに、この関数が自動的に呼び出されます。*/
int	end_fractol(t_fractol *f)
{
	clean_exit(0, f);
	return (0);
}
