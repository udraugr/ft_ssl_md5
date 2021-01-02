/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:52:51 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/02 16:09:34 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

void				ft_print_hash(char *hash, t_input *input)
{
	if (input->flags & FLAG_Q ||
				(!(input->flags & FLAG_P) && input->from == NULL))
		ft_printf("%s\n", hash);
	else if (input->flags & FLAG_P)
		ft_printf("%s%s\n", input->input_str, hash);
	else if (input->flags & FLAG_R)
		ft_printf("%s %s\n", hash, input->from);
	else
		ft_printf("%s (%s) = %s\n", input->promt, input->from, hash);
}
