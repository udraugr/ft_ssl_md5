/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:26:41 by udraugr-          #+#    #+#             */
/*   Updated: 2019/06/09 12:58:34 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*area;

	area = (void *)malloc(size);
	if (!area)
		return (NULL);
	while (size)
		((unsigned char *)area)[size--] = 0;
	((unsigned char *)area)[0] = 0;
	return (area);
}
