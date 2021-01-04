/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_argv_from_stdin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:19:48 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 21:36:02 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

static void			read_stdin(char **str)
{
	int				len;
	char			c[2];
	char			*tmp;

	ft_putstr_fd("ft_ssl> ", STDOUT_FILENO);
	ft_strdel(str);
	while ((len = read(STDIN_FILENO, &c, 1)) > 0)
	{
		c[len] = '\0';
		if (c[0] == '\n')
			break ;
		else if (!(*str = ft_strjoin_pro(*str, ft_strdup(c), BOTH)))
			ft_exit_malloc_crash();
	}
	if (len == -1)
	{
		ft_putendl_fd("read: cat't read from STDIN_FILENO!", STDERR_FILENO);
		exit(STOP);
	}
	tmp = NULL;
	if (*str && !(tmp = ft_strtrim(*str)))
		ft_exit_malloc_crash();
	ft_strdel(str);
	*str = tmp;
}

int					get_argv_from_stdin(char ***args, int argc, char **argv)
{
	char			*str;
	static uint8_t	stadia = NEXT;

	if (stadia == NEXT_LAST)
		return (STOP);
	if (argc < 2)
	{
		str = NULL;
		while (!str || !ft_strcmp(str, ""))
			read_stdin(&str);
		if (!ft_strcmp(str, "exit"))
			stadia = STOP;
		if (stadia != STOP && !(*args = parse_argv_from_stdin(str)))
			ft_exit_malloc_crash();
		ft_strdel(&str);
	}
	else
	{
		if (!(*args = ft_copy_arr(argc - 1, &argv[1])))
			ft_exit_malloc_crash();
		stadia = NEXT_LAST;
	}
	return (stadia);
}
