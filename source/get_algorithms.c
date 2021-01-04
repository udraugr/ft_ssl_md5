/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_algorithms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:26:07 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 22:26:17 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

t_algorithm					*get_algorithms(void)
{
	static t_algorithm		algorithms[] = {
							{ft_md5, "md5", "MD5"},
							{ft_sha224, "sha224", "SHA224"},
							{ft_sha256, "sha256", "SHA256"},
							{ft_sha384, "sha384", "SHA384"},
							{ft_sha512, "sha512", "SHA512"},
							{ft_sha512_224, "sha512/224", "SHA512/224"},
							{ft_sha512_256, "sha512/256", "SHA512/256"},
							{0, {0}, {0}}
											};

	return (algorithms);
}
