/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:48:37 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/01 22:41:15 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "../libftprintf/ft_printf/printf.h"
# include <fcntl.h>

# define FLAG_Q 0x1000
# define FLAG_R 0x100
# define FLAG_S 0x10
# define FLAG_P 0x1

# define F(X, Y, Z) (uint32_t)((X & Y) | (~X & Z))
# define G(X, Y, Z) (uint32_t)((X & Z) | (Y & ~Z))
# define H(X, Y, Z) (uint32_t)(X ^ Y ^ Z)
# define I(X, Y, Z) (uint32_t)(Y ^ (X | ~Z))

# define ROTATE_LEFT(X, N) (uint32_t)((x << n) | (x >> (32 - n)))

enum
{
	SUCCESS,
	FAIL
};

enum
{
	LITTLE,
	BIG
};

typedef struct			s_input
{
	char				*input_str;
	char				*from;
	char				promt[60];
	char				*(*hash_func)(struct s_input*);
	uint32_t			flags;
	uint8_t				endian;
}						t_input;

typedef struct			s_algorithm
{
	char				*(*hash_func)(struct s_input*);
	char				name[60];
	char				promt[60];
}						t_algorithm;

typedef struct			s_word32
{
	size_t				size;
	unsigned char		*buf;
	uint32_t			*k;
	uint32_t			*s;
}						t_word32;

typedef struct			s_hash
{
	uint64_t			*hash64;
	uint32_t			*hash32;
	size_t				size;
}						t_hash;

void 					get_std_input(t_input *input);
void					get_file_input(char **argv, size_t i, t_input *input);

void					ft_print_hash(char *hash, t_input *input);

char					*ft_md5(t_input *input);
char					*ft_sha256(t_input *input);

#endif