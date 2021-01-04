/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_malloc_crash.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:26:50 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 15:26:59 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

void			ft_exit_malloc_crash(void)
{
	ft_putendl_fd("malloc can't allocate memory!", STDERR_FILENO);
	exit(FAIL);
}
