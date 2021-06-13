/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 02:22:42 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/11 14:27:18 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef t_list*	t_pl;

void	ft_lstadd_back(t_pl *lst, t_pl new)
{
	if (!lst)
		return ;
	if (*lst)
	{
		ft_lstadd_back(&((*lst)->next), new);
		return ;
	}
	*lst = new;
}
