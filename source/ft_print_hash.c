/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:52:51 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/01 19:55:23 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

void				ft_print_hash(char *hash, t_input *input)
{
	if (input->flags & FLAG_Q)
		ft_printf("%s\n", hash);
	else if (input->flags & FLAG_R)
		ft_printf("%s\n", hash);
	else if (input->flags & FLAG_S)
		ft_printf("%s\n", hash);
	else if (input->flags & FLAG_P)
		ft_printf("%s\n", hash);
}