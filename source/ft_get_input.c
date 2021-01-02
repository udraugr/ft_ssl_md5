/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:45:52 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/02 16:55:40 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

char				*read_from_fd(int fd)
{
	char			*str;
	char			buff[501];
	uint32_t		len;

	if (!(str = ft_strnew(0)))
	{
		ft_putendl_fd("malloc can't allocate memory!", STDERR_FILENO);
		exit(FAIL);
	}
	while ((len = read(fd, buff, 500)) > 0)
	{
		buff[len] = '\0';
		if (!(str = ft_strjoin_pro(str, buff, ONLY_FIRST)))
		{
			ft_putendl_fd("malloc can't allocate memory!", STDERR_FILENO);
			exit(FAIL);
		}
	}
	if (len == -1)
	{
		ft_putendl_fd("read: cat't read from fd file!", STDERR_FILENO);
		return (NULL);
	}
	return (str);
}

void				get_std_input(t_input *input, t_read_from_stdin *stdin_read)
{
	char			*hash;

	if (stdin_read->read_from_stdin == FALSE)
	{
		if (!(input->input_str = read_from_fd(STDIN_FILENO)))
			return ;
		stdin_read->read_from_stdin = TRUE;
	}
	else
	{
		if (!(input->input_str = ft_strnew(0)))
			exit(FAIL);
	}
	input->from = NULL;
	hash = input->hash_func(input);
	ft_print_hash(hash, input);
	ft_strdel(&hash);
	ft_strdel(&input->input_str);
}

void				get_file_input(char **argv, size_t i, t_input *input)
{
	uint32_t		fd;
	char			*hash;

	while (argv && argv[i])
	{
		if ((fd = open(argv[i], O_RDONLY)) == -1)
			ft_putendl_fd("open: cat't take fd for file!", STDERR_FILENO);
		++i;
		if (fd == -1 || !(input->input_str = read_from_fd(fd)))
			continue ;
		input->from = ft_strdup(argv[i - 1]);
		hash = input->hash_func(input);
		ft_print_hash(hash, input);
		ft_strdel(&hash);
		ft_strdel(&input->input_str);
		ft_strdel(&input->from);
	}
}
