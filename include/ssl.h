/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:48:37 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/03 00:03:05 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "../libftprintf/ft_printf/printf.h"
# include <fcntl.h>

typedef u_int64_t	uint64_t;
typedef u_int32_t	uint32_t;
typedef u_int16_t	uint16_t;
typedef u_int8_t	uint8_t;

# define ROTL(X, N) (uint32_t)((X << N) | (X >> (32 - N)))
# define ROTR(X, N) (uint32_t)((X >> N) | (X << (32 - N)))

# define CEIL(X) (size_t)(X > (size_t)(X)) ? (size_t)(X + 1.f): (size_t)(X)

/*
** Functions for md5
*/

# define F(X, Y, Z) (uint32_t)((X & Y) | (~X & Z))
# define G(X, Y, Z) (uint32_t)((X & Z) | (Y & ~Z))
# define H(X, Y, Z) (uint32_t)(X ^ Y ^ Z)
# define I(X, Y, Z) (uint32_t)(Y ^ (X | ~Z))

/*
** Functions for sha256
*/

# define S0(X) ROTR(X, 7) ^ ROTR(X, 18) ^ (X >>  3)
# define S1(X) ROTR(X, 17) ^ ROTR(X, 19) ^ (X >> 10)
# define Q0(X) ROTR(X, 6) ^ ROTR(X, 11) ^ ROTR(X, 25)
# define Q1(X) ROTR(X, 2) ^ ROTR(X, 13) ^ ROTR(X, 22)

enum
{
	FLAG_Q = 0x1000,
	FLAG_R = 0x100,
	FLAG_S = 0x10,
	FLAG_P = 0x1
};

enum
{
	FALSE,
	TRUE
};

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

typedef struct			s_read_from_stdin
{
	uint8_t				read_from_stdin;
	uint8_t				need_read;
}						t_read_from_stdin;

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
}						t_word32;

typedef struct			s_hash
{
	uint64_t			*hash64;
	uint32_t			*hash32;
	size_t				size;
}						t_hash;

uint8_t					get_str_input(char **flags,
										size_t *i,
										t_input *input,
										t_read_from_stdin *stdin_read);
void					get_std_input(t_input *input,
										t_read_from_stdin *stdin_read);
void					get_file_input(char **argv, size_t i, t_input *input);

void					ft_print_hash(char *hash, t_input *input);

char					*ft_i32toa_base(uint32_t num, uint8_t base);
char					*ft_i64toa_base(uint64_t num, uint8_t base);
uint64_t				swap_uint64(uint64_t x);
uint32_t				swap_uint32(uint32_t x);

void					ft_hash_swap_byte(t_hash *hash);
char					*ft_hash_to_ascii(t_hash *hash);
void					ft_hash_assigne(t_hash *hash,
										uint32_t *h32, uint64_t *h64);
void					ft_add_to_hash(t_hash *hash,
										uint32_t *h32, uint64_t *h64);

char					*ft_md5(t_input *input);
char					*ft_sha256(t_input *input);

#endif
