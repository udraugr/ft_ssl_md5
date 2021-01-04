/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:09:08 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 00:47:16 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

void				ft_hash_swap_byte(t_hash *hash)
{
	size_t			size;

	if (!hash || (!hash->hash32 && !hash->hash64))
		return ;
	size = 0;
	while (hash->hash32 && size < hash->size)
	{
		hash->hash32[size] = swap_uint32(hash->hash32[size]);
		++size;
	}
	while (hash->hash64 && size < hash->size)
	{
		hash->hash64[size] = swap_uint64(hash->hash64[size]);
		++size;
	}
}

char				*ft_hash_to_ascii(t_hash *hash)
{
	size_t			size;
	char			*hash_str;

	if (!hash || (!hash->hash32 && !hash->hash64))
		return (NULL);
	size = 0;
	hash_str = NULL;
	while (hash->hash32 && size < hash->size)
	{
		if (!(hash_str = ft_strjoin_pro(hash_str,
					ft_i32toa_base(hash->hash32[size], 16), BOTH)))
			break ;
		++size;
	}
	while (hash->hash64 && size < hash->size)
	{
		if (!(hash_str = ft_strjoin_pro(hash_str,
					ft_i64toa_base(hash->hash64[size], 16), BOTH)))
			break ;
		++size;
	}
	if (!hash_str)
		ft_exit_malloc_crash();
	return (hash_str);
}

void				ft_hash_assign(t_hash *hash, uint32_t *h32, uint64_t *h64)
{
	size_t			size;

	if (!hash || (!hash->hash32 && !hash->hash64) || (!h32 && !h64))
		return ;
	size = 0;
	while (hash->hash32 && h32 && size < hash->size)
	{
		hash->hash32[size] = h32[size];
		++size;
	}
	while (hash->hash64 && h64 && size < hash->size)
	{
		hash->hash64[size] = h64[size];
		++size;
	}
}

void				ft_add_to_hash(t_hash *hash, uint32_t *h32, uint64_t *h64)
{
	size_t			size;

	if (!hash || (!hash->hash32 && !hash->hash64) || (!h32 && !h64))
		return ;
	size = 0;
	while (hash->hash32 && h32 && size < hash->size)
	{
		hash->hash32[size] += h32[size];
		++size;
	}
	while (hash->hash64 && h64 && size < hash->size)
	{
		hash->hash64[size] += h64[size];
		++size;
	}
}
