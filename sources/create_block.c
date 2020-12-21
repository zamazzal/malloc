/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:14:02 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:47:21 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*ft_reserv_zone(t_block *block, size_t size)
{
	t_block			*next_b;
	long long int	x;
	void			*ptr;

	x = block->size - (sizeof(t_block) + size);
	ptr = (void*)block + sizeof(t_block);
	if (x < 1 || block->size == size)
	{
		block->alc = IS_ALLOCATED;
		block->size = block->size;
		return (ptr);
	}
	next_b = (void*)block + sizeof(t_block) + size;
	next_b->alc = 0;
	next_b->size = x;
	next_b->next = block->next;
	block->alc = IS_ALLOCATED;
	block->size = size;
	block->next = next_b;
	return (ptr);
}

static void		*ft_appand_block(t_block *block, size_t size)
{
	t_block		*new_block;
	void		*ptr;
	ptr = NULL;
	new_block = (void*)block + sizeof(t_block) + block->size;
	new_block->alc = IS_ALLOCATED;
	new_block->size = size;
	new_block->next = NULL;
	ptr = (void*)new_block + sizeof(t_block);
	block->next = new_block;
	return (ptr);
}

static void		*ft_create_block(t_zones *zone, t_block *block, size_t size)
{
	void		*ptr;
	t_block		*old_block;
	long long	x;

	while (block != NULL)
	{
		if (block && block->size >= 1)
		{
			if (!block->alc && block->size >= size)
				if ((ptr = ft_reserv_zone(block, size)))
					return (ptr);
		}
		old_block = block;
		block = block->next;
	}
	if (old_block && !block)
	{
		x = (long long)old_block - (long long)zone;
		x += sizeof(t_block) + old_block->size;
		x += sizeof(t_block) + size;
		if (x < (long long)zone->size)
			return (ft_appand_block(old_block, size));
	}
	return (NULL);
}

void			*create_in_existing_z(size_t size, int type)
{
	void			*ptr;
	t_zones			*tmp;
	t_block			*block;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		if (tmp->zone_type == type)
		{
			block = (void*)tmp + sizeof(t_zones);
			ptr = ft_create_block(tmp, block, size);
			if (ptr)
				return (ptr);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
