/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:30:10 by udraugr-          #+#    #+#             */
/*   Updated: 2019/08/07 12:27:04 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*tmp;

	while (alst && *alst && del)
	{
		del((*alst)->content, (*alst)->content_size);
		(*alst)->content = 0;
		(*alst)->content_size = 0;
		tmp = *alst;
		*alst = (*alst)->next;
		free(tmp);
		tmp = NULL;
	}
}
