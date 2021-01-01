/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:08:49 by udraugr-          #+#    #+#             */
/*   Updated: 2019/08/19 16:58:33 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_strsplit(char const *s, char c)
{
	char		**ans;
	char		*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * 2)))
		return (0);
	tmp[0] = c;
	tmp[1] = '\0';
	ans = ft_strsplit_str(s, tmp);
	ft_strdel(&tmp);
	return (ans);
}
