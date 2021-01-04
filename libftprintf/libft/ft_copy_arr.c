/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 15:54:29 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 17:11:46 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_copy_arr(int number_of_str, char **str_arr)
{
	char				**ans;
	unsigned short int	i;

	i = 0;
	ans = (char **)malloc(sizeof(char *) * number_of_str + 1);
	if (!ans || !str_arr)
		return (NULL);
	while (str_arr[i])
	{
		if (!(ans[i] = ft_strdup(str_arr[i])))
		{
			while (--i > 0)
				ft_strdel(&ans[i]);
			ft_strdel(&ans[i]);
			free(ans);
			ans = 0;
			return (NULL);
		}
		++i;
	}
	ans[i] = 0;
	return (ans);
}
