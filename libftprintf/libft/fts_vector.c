/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:00:39 by udraugr-          #+#    #+#             */
/*   Updated: 2019/08/06 19:34:32 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector		*ft_create_vector(void *content)
{
	t_vector	*new_vector;

	if (!(new_vector = (t_vector *)malloc(sizeof(t_vector))))
		return (0);
	new_vector->next = 0;
	new_vector->previous = 0;
	new_vector->content = content;
	return (new_vector);
}

int				ft_count_vector(t_vector *begin)
{
	int			ans;

	if (!begin)
		return (0);
	ans = 1;
	while (begin->next)
	{
		++ans;
		begin = begin->next;
	}
	return (ans);
}

void			ft_del_vector(t_vector **chain)
{
	if (!chain || !(*chain))
		return ;
	if ((*chain)->previous)
		((*chain)->previous)->next = (*chain)->next;
	if ((*chain)->next)
		((*chain)->next)->previous = (*chain)->previous;
	(*chain)->next = 0;
	(*chain)->previous = 0;
	if ((*chain)->content != 0)
	{
		free((*chain)->content);
		(*chain)->content = 0;
	}
	free(*chain);
	*chain = 0;
}

t_vector		*ft_add_vector(t_vector *begin, void *content)
{
	t_vector	*tmp;
	t_vector	*new;

	if (!(new = ft_create_vector(content)))
		return (NULL);
	if (!begin)
		return (new);
	tmp = begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
	return (begin);
}
