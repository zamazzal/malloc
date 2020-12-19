/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:16:09 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:39:21 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		ft_check_type(size_t size)
{
	if (size > SMALL_SIZE)
		return (LARGE);
	else if (size > TINY_SIZE)
		return (SMALL);
	else
		return (TINY);
}

size_t	get_size_bytype(int type)
{
	size_t size;

	size = getpagesize();
	if (type == TINY)
		size = TINY_SIZE;
	if (type == SMALL)
		size = SMALL_SIZE;
	return (size);
}

size_t	multipleof_pages(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	while (size % page_size != 0)
		size++;
	return (size);
}

size_t	ft_getlen(int type, size_t size)
{
	size_t len;

	if (type != LARGE)
		len = (get_size_bytype(type) + sizeof(t_block)) * PREALLOC_SIZE;
	else
		len = size + sizeof(t_block);
	len += sizeof(t_zones);
	len = multipleof_pages(len);
	return (len);
}

int		check_zone_type_i(int type)
{
	t_zones	*tmp;
	int		i;

	tmp = g_zones_list;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->zone_type == type)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
