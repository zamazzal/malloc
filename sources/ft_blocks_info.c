/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blocks_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 04:40:02 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:41:21 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block			*ft_get_block(void *ptr)
{
	t_zones			*tmp;
	t_block			*block;
	void			*ptr_tmp;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		block = (void*)tmp + sizeof(t_block);
		while (block != NULL)
		{
			if (block && block->size > 0)
			{
				ptr_tmp = (void*)block + sizeof(t_block);
				if (ptr == ptr_tmp)
					return (block);
			}
			block = block->next;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_zones			*ft_get_zone(void *ptr)
{
	t_zones			*tmp;
	t_block			*block;
	void			*ptr_tmp;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		block = (void*)tmp + sizeof(t_block);
		while (block != NULL)
		{
			if (block && block->size > 0)
			{
				ptr_tmp = (void*)block + sizeof(t_block);
				if (ptr == ptr_tmp)
					return (tmp);
			}
			block = block->next;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

size_t			ft_blocks_info(void const *ptr)
{
	t_block			*block_tmp;

	block_tmp = ft_get_block((void*)ptr);
	if (!block_tmp)
		return (-1);
	ft_putstr("0x10");
	ft_putbase((long long int)ptr, 16);
	ft_putstr(" - ");
	ft_putnbr(block_tmp->size);
	ft_putendl(" bytes");
	return (block_tmp->size);
}

size_t			ft_zone_info(void const *ptr)
{
	t_zones			*zones_tmp;

	zones_tmp = ft_get_zone((void*)ptr);
	if (!zones_tmp)
		return (-1);
	ft_show_zone(zones_tmp);
	return (zones_tmp->size);
}

size_t			ft_block_len(void const *ptr)
{
	t_block			*block_tmp;

	block_tmp = ft_get_block((void*)ptr);
	if (!block_tmp)
		return (0);
	return (block_tmp->size);
}
