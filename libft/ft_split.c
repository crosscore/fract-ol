/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:38:10 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/16 16:38:10 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

void	ft_free_all(char **arr)
{
	size_t	i;
	char	**tmp;

	i = 0;
	tmp = arr;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(tmp);
}

void	ft_split_loop(char const *s, char c, char **array, int *j)
{
	int		k;
	char	*temp;

	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			k = 0;
			temp = malloc(ft_word_len(&(*s), c) + 1);
			if (!temp)
			{
				array[k] = NULL;
				ft_free_all(array);
				return ;
			}
			while (*s && *s != c)
				temp[k++] = *s++;
			temp[k] = '\0';
			array[*j] = temp;
			(*j)++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		j;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!(array))
		return (NULL);
	j = 0;
	ft_split_loop(s, c, array, &j);
	array[j] = NULL;
	return (array);
}
