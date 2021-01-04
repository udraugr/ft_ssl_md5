/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count_argv_from_stdin.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:22:20 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 22:12:44 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

static void			quotes_case(char *str, size_t *i,
								size_t *word, uint8_t *whitespaces)
{
	char			quote;
	size_t			j;

	j = *i;
	quote = str[j];
	*word = (*whitespaces) ? *word + 1 : *word;
	*whitespaces = 0;
	++j;
	while (str[j] && str[j] != quote)
		++j;
	j = (str[j]) ? j + 1 : j;
	*i = j;
}

static void			letter_case(char *str, size_t *i,
								size_t *word, uint8_t *whitespaces)
{
	size_t			j;

	j = *i;
	*word = (*whitespaces) ? *word + 1 : *word;
	*whitespaces = 0;
	while (str[j] && !ft_strchr(" \t\n\'\"", str[j]))
		++j;
	*i = j;
}

static void			whitespaces_case(size_t *i, uint8_t *whitespaces)
{
	*i += 1;
	*whitespaces = 1;
}

size_t				word_count_argv_from_stdin(char *str)
{
	size_t			word;
	size_t			i;
	uint8_t			whitespaces;

	i = 0;
	word = 0;
	whitespaces = 1;
	while (str && str[i])
	{
		while (str[i] && ft_strchr(" \t\n", str[i]))
			whitespaces_case(&i, &whitespaces);
		if (str[i] == '\'' || str[i] == '\"')
			quotes_case(str, &i, &word, &whitespaces);
		else
			letter_case(str, &i, &word, &whitespaces);
	}
	return (word);
}
