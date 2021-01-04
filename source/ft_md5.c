/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:35:14 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 01:00:19 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

static uint32_t		g_k[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
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

static uint32_t		g_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static void			init_hash_md5(uint8_t endian, t_hash *hash)
{
	hash->hash64 = NULL;
	if (!(hash->hash32 = ft_memalloc(sizeof(uint32_t) * 4)))
		ft_exit_malloc_crash();
	hash->hash32[0] = 0x67452301;
	hash->hash32[1] = 0xEFCDAB89;
	hash->hash32[2] = 0x98BADCFE;
	hash->hash32[3] = 0x10325476;
	if (endian == BIG)
		ft_hash_swap_byte(hash);
	hash->size = 4;
}

static void			init_word_md5(char *input_str, uint8_t endian,
									t_word32 *word, t_input *input)
{
	size_t				l;
	size_t				nl;
	size_t				mod64;

	l = input->length;
	mod64 = (l + 1) % 64;
	nl = (mod64 > 56) ? l + 1 + 64 - (mod64 - 56) : l + 1 + 56 - mod64;
	if (!(word->buf = (unsigned char *)ft_strnew(nl + 8)))
		ft_exit_malloc_crash();
	ft_memcpy(word->buf, input_str, l);
	word->buf[l] = 0x80;
	l *= 8;
	if (endian == BIG)
		l = swap_uint64(l);
	ft_memcpy(&word->buf[nl], &l, 8);
	word->size = nl + 8;
}

static void			compute_round(uint32_t *buf, uint32_t i, uint32_t th[4])
{
	uint32_t		func;
	uint32_t		g;

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
	func += th[0] + g_k[i] + buf[g];
	th[0] = th[3];
	th[3] = th[2];
	th[2] = th[1];
	th[1] += ROTL(func, g_s[i]);
}

/*
**	th - temporiary hash
*/

static void			compute_chunk(uint32_t *buf, t_hash *hash)
{
	uint32_t		th[4];
	uint32_t		i;

	i = 0;
	while (++i <= 4)
		th[i - 1] = hash->hash32[i - 1];
	i = 0;
	while (i < 64)
	{
		compute_round(buf, i, th);
		++i;
	}
	ft_add_to_hash(hash, th, NULL);
}

char				*ft_md5(t_input *input)
{
	char			*input_str;
	char			*hash_str;
	size_t			size;
	t_hash			hash;
	t_word32		word;

	if (!(input_str = ft_strnew(input->length)))
		ft_exit_malloc_crash();
	ft_memcpy(input_str, input->input_str, input->length);
	init_hash_md5(input->endian, &hash);
	init_word_md5(input->input_str, input->endian, &word, input);
	ft_strdel(&input_str);
	size = 0;
	while (size < word.size)
	{
		compute_chunk((uint32_t *)&word.buf[size], &hash);
		size += 64;
	}
	if (input->endian == LITTLE)
		ft_hash_swap_byte(&hash);
	hash_str = ft_hash_to_ascii(&hash);
	ft_memdel((void **)&hash.hash32);
	ft_memdel((void **)&word.buf);
	return (hash_str);
}
