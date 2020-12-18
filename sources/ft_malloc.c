/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:13:06 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/14 19:31:32 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*alloc_by_type(size_t size)
{
	int		type;
	void	*ptr;
	int		new_z;

	ptr = NULL;
	new_z = 0;
	type = ft_check_type(size);
	if (type != LARGE)
	{
		if (!(ptr = create_in_existing_z(size, type)))
		{
			ptr = create_new_zone(size, type);
			new_z = 1;
		}
	}
	else
	{
		ptr = create_new_zone(size, type);
		new_z = 1;
	}
	// malloc_log(ptr, new_z); for bonus
	return (ptr);
}

void		*ft_malloc(size_t size)
{
	void			*ptr;

	if (size < 1)
		return (NULL);
	ptr = alloc_by_type(size);
	return (ptr);
}

void	*malloc(size_t size)
{
	void	*ptr;

	ptr = ft_malloc(size);
	return (ptr);
}
