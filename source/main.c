/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:48:43 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/01 22:35:33 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

static t_algorithm			*get_algorithms(void)
{
	static t_algorithm		algorithms[] = {ft_md5, "md5", "MD5(%s)= %s\n",
											ft_sha256, "sha256", "SHA256(%s)",
											0, 0, 0};

	return (algorithms);
}

static uint8_t				get_info_algorithm(char *name_algorithm,
												t_input *input)
{
	t_algorithm				*algorithms;
	uint8_t					i;
	uint16_t				endian;

	i = 0;
	algorithms = get_algorithms();
	ft_strtolower(name_algorithm);
	while (algorithms && algorithms[i].hash_func)
	{
		if (!ft_strcmp(algorithms[i].name, name_algorithm))
		{
			input->hash_func = algorithms[i].hash_func;
			ft_strcpy(input->promt, algorithms[i].promt);
			endian = 0x0001;
			endian = *((uint8_t *)&endian) ? LITTLE : BIG;
			input->endian = endian;
			input->flags = 0;
			return (SUCCESS);
		}
		++i;
	}
	ft_putstr_fd(name_algorithm, STDERR_FILENO);
	ft_putendl_fd(": Unknown hash function\n", STDERR_FILENO);
	return (FAIL);
}

static uint8_t				get_info_flags(char *flags,
											t_input *input)
{
	if (!ft_strcmp(flags, "-q"))
		input->flags |= FLAG_Q;
	else if (!ft_strcmp(flags, "-r"))
		input->flags |= FLAG_R;
	else if (!ft_strcmp(flags, "-s"))
		input->flags |= FLAG_S;
	else if (!ft_strcmp(flags, "-p"))
		input->flags |= FLAG_P;
	else
	{
		ft_putstr_fd(flags, STDERR_FILENO);
		ft_putendl_fd(": Unknown options\n", STDERR_FILENO);
		return (FAIL);
	}
	return (SUCCESS);
}

static void					ft_usage(void)
{
	t_algorithm				*algorithms;
	uint8_t					i;

	ft_putendl_fd("Usage: ./ft_ssl command [options] [arguments]",
		STDERR_FILENO);
	ft_putendl_fd("Where command is:", STDERR_FILENO);
	algorithms = get_algorithms();
	i = 0;
	while (algorithms && algorithms[i].hash_func)
	{
		ft_putendl_fd(algorithms[i].name, STDERR_FILENO);
		++i;
	}
	ft_putendl_fd("\nAnd availiable options is:", STDERR_FILENO);
	ft_putendl_fd("-q\tquiet mode", STDERR_FILENO);
	ft_putendl_fd("-r\treverse the format of the output.", STDERR_FILENO);
	ft_putendl_fd("-s\tprint the sum of the given string", STDERR_FILENO);
	ft_putendl_fd("-p\techo STDIN to STDOUT and append the checksum to STDOUT",
		STDERR_FILENO);
	exit(FAIL);
}

int							main(int argc, char **argv)
{
	size_t					i;
	t_input					input;
	char					hash;

	if (argc < 2 || get_info_algorithm(argv[1], &input) == FAIL)
		ft_usage();
	i = 2;
	while (argv[i] && argv[i][0] == '-')
	{
		if (get_info_flags(argv[i], &input) == FAIL)
			ft_usage();
		++i;
	}
	if (!argv[i])
		get_std_input(&input);
	else
		get_file_input(argv, i, &input);
	return (0);
}
