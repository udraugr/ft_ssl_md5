/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:45:52 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 17:34:54 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

char				*read_from_fd(int fd, t_input *input)
{
	char			*str;
	char			*tmp;
	char			buff[64];
	int				len;

	if (!(str = ft_strnew(0)))
		ft_exit_malloc_crash();
	while ((len = read(fd, buff, 63)) > 0)
	{
		buff[len] = '\0';
		tmp = str;
		if (!(str = ft_strnew(input->length + len)))
			ft_exit_malloc_crash();
		ft_memcpy(str, tmp, input->length);
		ft_memcpy(str + input->length, buff, len);
		input->length += len;
		ft_strdel(&tmp);
	}
	if (len == -1)
	{
		ft_putendl_fd("read: cat't read from fd file!", STDERR_FILENO);
		return (NULL);
	}
	return (str);
}

uint8_t				get_str_input(char **flags,
									size_t *i,
									t_input *input,
									t_read_from_stdin *stdin_read)
{
	char			*hash;

	if (!flags[*i + 1])
	{
		ft_putendl_fd("-s\toption requires an argument\n", STDERR_FILENO);
		return (FAIL);
	}
	input->length = ft_strlen(flags[*i + 1]);
	input->from = flags[*i + 1];
	input->input_str = flags[*i + 1];
	input->flags |= FLAG_S;
	hash = input->hash_func(input);
	ft_print_hash(hash, input);
	ft_strdel(&hash);
	input->flags &= ~FLAG_S;
	*i += 1;
	stdin_read->need_read = FALSE;
	return (SUCCESS);
}

void				get_std_input(t_input *input, t_read_from_stdin *stdin_read)
{
	char			*hash;

	input->length = 0;
	if (stdin_read->read_from_stdin == FALSE)
	{
		if (!(input->input_str = read_from_fd(STDIN_FILENO, input)))
			return ;
		stdin_read->read_from_stdin = TRUE;
	}
	else
	{
		if (!(input->input_str = ft_strnew(0)))
			ft_exit_malloc_crash();
	}
	input->from = NULL;
	hash = input->hash_func(input);
	ft_print_hash(hash, input);
	ft_strdel(&hash);
	ft_strdel(&input->input_str);
}

void				get_file_input(char **argv, size_t i, t_input *input)
{
	int				fd;
	char			*hash;

	while (argv && argv[i])
	{
		input->length = 0;
		if ((fd = open(argv[i], O_RDONLY)) == -1)
			ft_putendl_fd("open: cat't take fd for file!", STDERR_FILENO);
		++i;
		if (fd == -1 || !(input->input_str = read_from_fd(fd, input)))
			continue ;
		close(fd);
		input->from = argv[i - 1];
		hash = input->hash_func(input);
		ft_print_hash(hash, input);
		ft_strdel(&hash);
		ft_strdel(&input->input_str);
	}
}
