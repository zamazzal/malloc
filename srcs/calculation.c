/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:16:09 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/12 18:16:31 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	multipleof_pages(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	while (size % page_size != 0)
		size++;
	return (size);
}

size_t	ft_getlen(int type)
{
	size_t len;
	size_t len_by_type;

	len_by_type = get_size_bytype(type);
	len = (len_by_type + sizeof(t_block)) * PREALLOC_SIZE;
	len += sizeof(t_zones);
	len = multipleof_pages(len);
	return (len);
}
