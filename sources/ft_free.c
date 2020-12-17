/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:50:43 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/17 18:50:45 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_delete_zone(t_zones *zone)
{
	size_t	ptr_len;

	ptr_len = zone->size;
	g_zones_list = ft_delete_zone_list(zone);
	ft_bzero((void*)zone, ptr_len);
	if (munmap((void*)zone, ptr_len) == -1)
		return (0);
	return (1);
}

static int		check_empty_zone(t_zones *zone)
{
	long long int	x;
	t_block			*block;

	x = sizeof(t_zones);
	while (x + 1 < (long long)zone->size)
	{
		block = (void*)zone + x;
		if (block && block->size > 0)
		{
			if (block->alc == IS_ALLOCATED)
				return (0);
			else if (!block->alc && zone->zone_type == LARGE)
				return (1);
			x += sizeof(t_block) + block->size;
		}
		else
			x++;
	}
	return (1);
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
	if (check_empty_zone(zone_tmp))
		ft_delete_zone(zone_tmp);
}

void	free(void *ptr)
{
	ft_free(ptr);
}
