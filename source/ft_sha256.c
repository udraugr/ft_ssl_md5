/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:17:13 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 15:31:06 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

static uint32_t		g_k[] = {0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
	0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01,
	0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
	0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA,
	0x5CB0A9DC, 0x76F988DA, 0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
	0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138,
	0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
	0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624,
	0xF40E3585, 0x106AA070, 0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
	0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F,
	0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

static void			init_hash_sha256(uint8_t endian, t_hash *hash)
{
	hash->hash64 = NULL;
	if (!(hash->hash32 = ft_memalloc(sizeof(uint32_t) * 8)))
		ft_exit_malloc_crash();
	hash->hash32[0] = 0x6A09E667;
	hash->hash32[1] = 0xBB67AE85;
	hash->hash32[2] = 0x3C6EF372;
	hash->hash32[3] = 0xA54FF53A;
	hash->hash32[4] = 0x510E527F;
	hash->hash32[5] = 0x9B05688C;
	hash->hash32[6] = 0x1F83D9AB;
	hash->hash32[7] = 0x5BE0CD19;
	if (endian == BIG)
		ft_hash_swap_byte(hash);
	hash->size = 8;
}

static void			init_word_sha256(char *input_str, uint8_t endian,
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
	if (endian == LITTLE)
		l = swap_uint64(l);
	ft_memcpy(&word->buf[nl], &l, 8);
	word->size = nl + 8;
}

static void			compute_round(uint32_t buf64[64], uint32_t i,
									uint32_t th[8])
{
	uint32_t		t1;
	uint32_t		t2;

	t1 = th[7] + Q0(th[4]) +
		((th[4] & th[5]) ^ ((~th[4]) & th[6])) + g_k[i] + buf64[i];
	t2 = Q1(th[0]) +
		((th[0] & th[1]) ^ (th[0] & th[2]) ^ (th[1] & th[2]));
	i = 8;
	while (--i > 0)
		th[i] = th[i - 1];
	th[4] += t1;
	th[0] = t1 + t2;
}

/*
**	th - temporiary hash
*/

static void			compute_chunk(uint32_t *buf, t_hash *hash)
{
	uint32_t		th[8];
	uint32_t		buf64[64];
	uint32_t		i;

	i = 0;
	while (++i <= 8)
		th[i - 1] = hash->hash32[i - 1];
	i = 0;
	while (i < 64)
	{
		if (i < 16)
			buf64[i] = swap_uint32(buf[i]);
		else
			buf64[i] = buf64[i - 16] + S0(buf64[i - 15])
						+ buf64[i - 7] + S1(buf64[i - 2]);
		++i;
	}
	i = 0;
	while (i < 64)
	{
		compute_round(buf64, i, th);
		++i;
	}
	ft_add_to_hash(hash, th, NULL);
}

char				*ft_sha256(t_input *input)
{
	char			*input_str;
	char			*hash_str;
	size_t			size;
	t_hash			hash;
	t_word32		word;

	if (!(input_str = ft_strnew(input->length)))
		ft_exit_malloc_crash();
	ft_memcpy(input_str, input->input_str, input->length);
	init_hash_sha256(input->endian, &hash);
	init_word_sha256(input_str, input->endian, &word, input);
	ft_strdel(&input_str);
	size = 0;
	while (size < word.size)
	{
		compute_chunk((uint32_t *)&word.buf[size], &hash);
		size += 64;
	}
	hash_str = ft_hash_to_ascii(&hash);
	ft_memdel((void **)&hash.hash32);
	ft_memdel((void **)&word.buf);
	return (hash_str);
}
