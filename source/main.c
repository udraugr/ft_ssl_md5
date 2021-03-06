/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:48:43 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 22:26:21 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

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

static uint8_t				get_info_flags(char **flags,
											size_t *i,
											t_input *input,
											t_read_from_stdin *stdin_read)
{
	if (!flags || !flags[*i])
		return (FAIL);
	if (!ft_strcmp(flags[*i], "-q"))
		input->flags |= FLAG_Q;
	else if (!ft_strcmp(flags[*i], "-r"))
		input->flags |= FLAG_R;
	else if (!ft_strcmp(flags[*i], "-s"))
		return (get_str_input(flags, i, input, stdin_read));
	else if (!ft_strcmp(flags[*i], "-p"))
	{
		input->flags |= FLAG_P;
		get_std_input(input, stdin_read);
		input->flags &= ~FLAG_P;
	}
	else
	{
		ft_putstr_fd(flags[*i], STDERR_FILENO);
		ft_putendl_fd(": Unknown options\n", STDERR_FILENO);
		return (FAIL);
	}
	return (SUCCESS);
}

static int					ft_usage(void)
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
	return (FAIL);
}

static void					input_loop(char ***argv)
{
	char					**args;
	size_t					i;
	t_input					input;
	t_read_from_stdin		stdin_read;
	uint8_t					res;

	args = *argv;
	if ((res = get_info_algorithm(args[0], &input)) == FAIL)
		ft_usage();
	i = 1;
	stdin_read.read_from_stdin = FALSE;
	stdin_read.need_read = TRUE;
	while (res == SUCCESS && args[i] && args[i][0] == '-')
	{
		if ((res = get_info_flags(args, &i, &input, &stdin_read)) == FAIL)
			ft_usage();
		++i;
	}
	if (res == SUCCESS && !args[i] &&
		stdin_read.need_read == TRUE && stdin_read.read_from_stdin == FALSE)
		get_std_input(&input, &stdin_read);
	else if (res == SUCCESS && args[i])
		get_file_input(args, i, &input);
	ft_del_arr(argv);
}

int							main(int argc, char **argv)
{
	char					**args;

	while (get_argv_from_stdin(&args, argc, argv) != STOP)
		input_loop(&args);
	return (0);
}
