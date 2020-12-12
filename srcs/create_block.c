/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:14:02 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/12 20:14:35 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*ft_reserv_zone(t_block *block, size_t size)
{
	t_block			*next_b;
	long long int	x;

	if (block->size >= size)
	{
		x = (block->size - sizeof(t_block) - size);
		if (x < 1 || block->size == size)
		{
			block->alc = IS_ALLOCATED;
			block->size = block->size;
			return (block + sizeof(t_block));
		}
		next_b = (void*)block + sizeof(t_block) + size;
		next_b->alc = 0;
		next_b->size = x;
		block->alc = IS_ALLOCATED;
		block->size = size;
		return (block + sizeof(t_block));
	}
	return (NULL);
}

static void	*ft_getblock(t_zones *list, size_t size)
{
	long long int	x;
	t_block			*block;
	void			*ptr;

	ptr = NULL;
	x = sizeof(t_zones);
	while (x - 1 < list->size)
	{
		block = (void*)list + x;
		if (block && block->size >= 1)
		{
			x += sizeof(t_block) + block->size;
			if (!block->alc)
				if ((ptr = ft_reserv_zone(block, size)))
					return (ptr);
		}
		else
			x++;
	}
	return (NULL);
}

void		*create_in_existing_z(size_t size, int type)
{
	t_zones	*tmp;
	void	*ptr;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		if (tmp->zone_type == type)
		{
			ptr = ft_getblock(tmp, size);
			if (ptr != NULL)
				return (ptr);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
