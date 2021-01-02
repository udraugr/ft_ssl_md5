/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 19:24:04 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/02 19:31:50 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

char				*ft_i32toa_base(uint32_t num, uint8_t base)
{
	char			*ascii;
	uint32_t		i;

	if (base == 1 || base > 16)
		return (NULL);
	i = 0;
	if (!(ascii = ft_strnew(CEIL(256.f / (float)base * 4.f))))
	{
		ft_putendl_fd("malloc can't allocate memory!", STDERR_FILENO);
		exit(FAIL);
	}
	ft_memset(ascii, '0', 8);
	i = 7;
	while (num)
	{
		ascii[i] = num % base > 9 ?
				'a' + num % base - 10 : '0' + num % base;
		num /= base;
		--i;
	}
	return (ascii);
}

char				*ft_i64toa_base(uint64_t num, uint8_t base)
{
	char			*ascii;
	uint32_t		i;

	if (base == 1 || base > 16)
		return (NULL);
	i = 0;
	if (!(ascii = ft_strnew(CEIL(256.f / (double)base * 4.f))))
	{
		ft_putendl_fd("malloc can't allocate memory!", STDERR_FILENO);
		exit(FAIL);
	}
	ft_memset(ascii, '0', 16);
	i = 15;
	while (num)
	{
		ascii[i] = num % base > 9 ?
				'a' + num % base - 10 : '0' + num % base;
		num /= base;
		--i;
	}
	return (ascii);
}