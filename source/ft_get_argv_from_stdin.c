/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_argv_from_stdin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:19:48 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 20:51:18 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

static size_t		word_count(char *str)
{
	size_t			word;
	size_t			i;
	uint8_t			whitespaces;
	char			quote;

	i = 0;
	word = 0;
	whitespaces = 1;
	while (str && str[i])
	{
		while (str[i] && ft_strchr(" \t\n", str[i]))
		{
			++i;
			whitespaces = 1;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			word = (whitespaces) ? word + 1 : word;
			whitespaces = 0;
			++i;
			while (str[i] && str[i] != quote)
				++i;
			i = (str[i]) ? i + 1 : i;
		}
		else
		{
			word = (whitespaces) ? word + 1 : word;
			whitespaces = 0;
			while (str[i] && !ft_strchr(" \t\n\'\"", str[i]))
				++i;
		}
	}
	return (word);
}

static char			**parse(char *str)
{
	char			**args;
	size_t			begin;
	size_t			i;
	size_t			j;
	size_t			word;
	uint8_t			whitespaces;
	char			quote;

	args = NULL;
	word = word_count(str);
	if (!(args = (char **)malloc(sizeof(char *) * (word + 1))))
		ft_exit_malloc_crash();
	i = 0;
	j = 0;
	whitespaces = 1;
	begin = 0;
	while (str[i] && j < word)
	{
		if (str[i] && ft_strchr(" \t\n", str[i]))
		{
			args[j++] = ft_strndup(&str[begin], &str[i] - &str[begin]);
			++i;
			whitespaces = 1;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			begin = (whitespaces) ? i : begin;
			whitespaces = 0;
			ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
			++i;
			while (str[i] && str[i] != quote)
				++i;
			if (str[i])
				ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
		}
		else
		{
			begin = (whitespaces) ? i : begin;
			whitespaces = 0;
			++i;
			while (str[i] && !ft_strchr(" \t\n\'\"", str[i]))
				++i;
		}
	}
	if (!whitespaces)
		args[j++] = ft_strndup(&str[begin], &str[i] - &str[begin]);
	args[j] = NULL;
	return (args);
}

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
		if (stadia != STOP && !(*args = parse(str)))
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
