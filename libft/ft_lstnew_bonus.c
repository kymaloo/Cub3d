/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:33:44 by trgaspar          #+#    #+#             */
/*   Updated: 2024/10/24 18:40:43 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char input, int type)
{
	t_list	*memb;

	memb = malloc(sizeof(t_list));
	if (!memb)
		return (NULL);
	memb->character = input;
	memb->type = type;
	memb->next = NULL;
	return (memb);
}
