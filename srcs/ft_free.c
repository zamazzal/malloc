/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:59:01 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/13 13:00:02 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block			*ft_get_block(void *ptr)
{
	t_zones			*tmp;
	t_block			*block;
	long long int	x;
	void			*ptr_tmp;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		x = sizeof(t_zones);
		while (x + 1 < (long long)tmp->size)
		{
			block = (void*)tmp + x;
			if (block && block->size > 0)
			{
				ptr_tmp = (void*)block + sizeof(t_block);
				if (ptr == ptr_tmp)
					return (block);
				x += block->size;
			}
			else
				x++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_zones			*ft_get_zone(void *ptr)
{
	t_zones			*tmp;
	t_block			*block;
	long long int	x;
	void			*ptr_tmp;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		x = sizeof(t_zones);
		while (x + 1 < (long long)tmp->size)
		{
			block = (void*)tmp + x;
			if (block && block->size > 0)
			{
				ptr_tmp = (void*)block + sizeof(t_block);
				if (ptr == ptr_tmp)
					return (tmp);
				x += block->size;
			}
			else
				x++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void			ft_free(void *ptr)
{
	t_block			*block_tmp;
	t_zones			*zone_tmp;

	if (!ptr)
		return ;
	block_tmp = ft_get_block(ptr);
	zone_tmp = ft_get_zone(ptr);
	if (!zone_tmp || !block_tmp)
		return ;
	if (block_tmp->alc == IS_ALLOCATED)
		block_tmp->alc = 0;
	ft_empty_zone(zone_tmp);
}
