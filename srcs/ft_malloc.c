/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:13:06 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/12 20:13:52 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*alloc_by_type(size_t size)
{
	int		type;
	void	*ptr;

	ptr = NULL;
	type = ft_check_type(size);
	if (type == TINY || type == SMALL)
	{
		if (!(ptr = create_in_existing_z(size, type)))
			ptr = create_new_zone(size, type);
	}
	else
		ptr = alloc_large_zone(size);
	return (ptr);
}

void		*ft_malloc(size_t size)
{
	void *ptr;

	ptr = alloc_by_type(size);
	return (ptr);
}
