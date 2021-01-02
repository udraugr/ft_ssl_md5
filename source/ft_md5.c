/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:35:14 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/02 13:11:19 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

char				*ft_itoa_base(uint32_t num, uint8_t base)
{
	char			digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	char			result[100];
	uint32_t		i;
	char			*ascii;

	if (base == 1 || base > 16)
		return (NULL);
	i = 0;
	while (num / base)
	{
		result[i] = digits[num % base];
		num /= base;
		++i;
	}
	// ft_putendl_fd("I'm here!", STDERR_FILENO);
	result[i] = digits[num];
	result[i + 1] = '\0';	
	// ft_printf("ascii= %p\n", ascii);
	ascii = ft_strnew(ft_strlen(result));
	i = 0;
	while (result[i])
	{
		ascii[ft_strlen(result) - 1 - i] = result[i];
		++i;
	}
	return (ascii);
}

static void			init_hash_md5(t_hash *hash)
{
	hash->hash64 = NULL;
	hash->hash32 = ft_memalloc(sizeof(uint32_t) * 4);
	hash->hash32[0] = 0x67452301;
	hash->hash32[1] = 0xEFCDAB89;
	hash->hash32[2] = 0x98BADCFE;
	hash->hash32[3] = 0x10325476;
	// проверка на endian на машина с BIGe нужно свапнуть порядок байт
	hash->size = 4;
}

uint64_t	swap_uint64(uint64_t x)
{
	x = ((x << 8) & 0xFF00FF00FF00FF00ULL) |
		((x >> 8) & 0x00FF00FF00FF00FFULL);
	x = ((x << 16) & 0xFFFF0000FFFF0000ULL) |
		((x >> 16) & 0x0000FFFF0000FFFFULL);
	return (x << 32) | (x >> 32);
}

#include <stdio.h>
static void			init_word_md5(t_input *input, t_word32 *word)
{
	static uint32_t		k[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
		0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
		0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
		0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
		0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
	static uint32_t		s[] = {
		7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	size_t				l;
	size_t				nl;
	size_t				mod64;

	word->k = k;
	word->s = s;
	l = ft_strlen(input->input_str);
	// for (size_t i = 0; i < l; ++i)
	// {
	// 	if (i % 4 == 0)
	// 		printf("\n");
	// 	printf("%s", ft_itoa_base(input->input_str, 16));
	// }
	// printf("\n");
	mod64 = (l + 1) % 64;
	nl = (mod64 > 56) ? l + 1 + 64 - (mod64 - 56) : l + 1 + 56 - mod64;
	word->buf = ft_strnew(nl + 8);
	ft_memcpy(word->buf, input->input_str, l);
	word->buf[l] = 0x80;
	// проверка на endian на машина с BIGe нужно свапнуть порядок байт
	l *= 8;
	ft_memcpy(&word->buf[nl], &l, 8);
	word->size = nl + 8;
	// for (size_t i = 0; i < word->size; ++i)
	// {
	// 	if (i % 4 == 0)
	// 		printf("\n");
	// 	printf("%s", ft_itoa_base(word->buf[i], 16));
	// }
	// printf("\n");
}

/*
**	th - temporiary hash
*/
void				compute_chunk(uint32_t *buf, t_hash *hash, t_word32 *word)
{
	uint32_t		th[4];
	uint32_t		func;
	uint32_t		g;
	uint32_t		i;
	
	th[0] = hash->hash32[0];
	th[1] = hash->hash32[1];
	th[2] = hash->hash32[2];
	th[3] = hash->hash32[3];
	i = 0;
	while (i < 64)
	{
		if (i / 16 == 0)
		{
			func = F(th[1], th[2], th[3]);
			g = i;
		}
		else if (i / 16 == 1)
		{
			func = G(th[1], th[2], th[3]);
			g = (5 * i + 1) % 16;
		}
		else if (i / 16 == 2)
		{
			func = H(th[1], th[2], th[3]);
			g = (3 * i + 5) % 16;
		}
		else
		{
			func = I(th[1], th[2], th[3]);
			g = (7 * i) % 16;
		}
		func += th[0] + word->k[i] + buf[g];
		th[0] = th[3];
		th[3] = th[2];
		th[2] = th[1];
		th[1] += ROTATE_LEFT(func, word->s[i]);
		printf("%x%x%x%x\n", th[0], th[1], th[2], th[3]);
		++i;
	}
	hash->hash32[0] += th[0];
	hash->hash32[1] += th[1];
	hash->hash32[2] += th[2];
	hash->hash32[3] += th[3];
}

uint32_t			swap_uint32(uint32_t x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);

}

char				*ft_md5(t_input *input)
{
	char			*hash_str;
	size_t			size;
	t_hash			hash;
	t_word32		word;


	init_hash_md5(&hash);
	init_word_md5(input, &word);
	size = 0;
	while (size < word.size)
	{
		compute_chunk((uint32_t *)&word.buf[size], &hash, &word);
		size += 64;
		// printf("%x%x%x%x\n", hash.hash32[0], hash.hash32[1], hash.hash32[2], hash.hash32[3]);
	}
	// проверка на endian на машина с BIGe нужно свапнуть порядок байт
	hash.hash32[0] = swap_uint32(hash.hash32[0]);
	hash.hash32[1] = swap_uint32(hash.hash32[1]);
	hash.hash32[2] = swap_uint32(hash.hash32[2]);
	hash.hash32[3] = swap_uint32(hash.hash32[3]);
	size = 0;
	hash_str = NULL;
	// ft_printf("word.buf = %p\n", word.buf);
	while (size < 4)
	{
		hash_str = ft_strjoin_pro(hash_str,
					ft_itoa_base(hash.hash32[size], 16), BOTH);
		++size;
	}
	free(word.buf);
	word.buf = 0;
	//ft_putendl_fd("I'm here!", STDERR_FILENO);
	return (hash_str);
}
