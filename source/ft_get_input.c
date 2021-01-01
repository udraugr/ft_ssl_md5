/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:45:52 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/01 22:36:13 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

char				*read_from_fd(int fd)
{
	char			*str;
	char			buff[501];
	uint32_t		len;

	str = NULL;
	while ((len = read(fd, buff, 500)) > 0)
	{
		buff[len] = '\0';
		str = ft_strjoin_pro(str, buff, ONLY_FIRST);
	}
	if (len == -1)
	{
		ft_putendl_fd("read: cat't read from fd file!", STDERR_FILENO);
		return (NULL);
	}
	return (str);
}

void 				get_std_input(t_input *input)
{
	char			*hash;

	if (!(input->input_str = read_from_fd(STDIN_FILENO)))
		return ;
	input->from = "stdin";
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
		input->from = ft_strdup(argv[i]);
		++i;
		if (fd == -1 || !(input->input_str = read_from_fd(fd)))
			continue ;
		hash = input->hash_func(input);
		ft_print_hash(hash, input);
		ft_strdel(&hash);
		ft_strdel(&input->input_str);
		ft_strdel(&input->from);
	}
}