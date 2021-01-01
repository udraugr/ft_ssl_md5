/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pro.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 14:10:49 by udraugr-          #+#    #+#             */
/*   Updated: 2019/06/22 17:06:25 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_pro(char *begin, char *end, int mod)
{
	char		*ans;

	if (!begin && !end)
		ans = ft_strdup("");
	else if (!begin)
		ans = ft_strdup(end);
	else if (!end)
		ans = ft_strdup(begin);
	else
		ans = ft_strjoin(begin, end);
	if (mod == ONLY_FIRST)
		ft_strdel(&begin);
	else if (mod == ONLY_SECOND)
		ft_strdel(&end);
	else if (mod == BOTH)
	{
		ft_strdel(&begin);
		ft_strdel(&end);
	}
	return (ans);
}
