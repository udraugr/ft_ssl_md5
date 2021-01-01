/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:35:14 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/01 19:51:14 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

char				*ft_md5(t_input *input)
{
    uint32_t		A;
    uint32_t		B;
    uint32_t		C;
    uint32_t		D;
	uint32_t		T[64];

	A = 0x67452301;
	B = 0xEFCDAB89;
	C = 0x98BADCFE;
	D = 0x10325476;

	// for (int i = 0; i < 64; i++)
	// {
	// 	T[i] = (uint32_t)(pow(2.f, 32.f) * fabs(sin((double)(i + 1))));
	// 	printf("%u \n", T[i]);
	// }
    // uint16_t x = 0x0001;
    // ft_printf("%s-endian\n", *((uint8_t *) &x) ? "little" : "big");
	return (NULL);
}