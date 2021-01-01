/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:25:59 by udraugr-          #+#    #+#             */
/*   Updated: 2019/08/19 16:54:11 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char now, char *sep)
{
	while (*sep)
	{
		if (*sep == now)
			return (1);
		++sep;
	}
	return (0);
}

static int	ft_fill(char ***ans, char const *str, char *sep)
{
	char	*tmp;
	int		n;
	int		word;

	word = 0;
	while (*str)
	{
		while (*str && ft_check(*str, sep) == 1)
			++str;
		if (!(*str))
			break ;
		tmp = (char *)str;
		while (*str && ft_check(*str, sep) == 0)
			++str;
		n = str - tmp;
		if (!((*ans)[word] = ft_strndup(tmp, n)))
		{
			ft_del_arr(ans);
			return (1);
		}
		++word;
	}
	return (0);
}

char		**ft_strsplit_str(char const *str, char *sep)
{
	char	**ans;
	int		word;
	int		i;

	if (!sep || !str)
		return (0);
	word = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_check(str[i], sep) == 1)
			++i;
		if (!str[i])
			break ;
		++word;
		while (str[i] && ft_check(str[i], sep) == 0)
			++i;
	}
	if (!(ans = (char **)malloc(sizeof(char *) * (word + 1))))
		return (0);
	ft_bzero((void *)ans, sizeof(char *) * (word + 1));
	if (ft_fill(&ans, str, sep) != 0)
		return (0);
	return (ans);
}
