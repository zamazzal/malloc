/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:50:43 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:47:31 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_delete_zone(t_zones *zone)
{
	size_t	ptr_len;

	if (zone->zone_type != LARGE)
	{
		if (check_zone_type_i(zone->zone_type) <= 1)
			return (0);
	}
	ptr_len = zone->size;
	g_zones_list = ft_delete_zone_list(zone);
	if (munmap((void*)zone, ptr_len) == -1)
		return (0);
	return (1);
}

static int		check_empty_zone(t_zones *zone)
{
	t_block			*block;

	block = (void*)zone + sizeof(t_block);
	while (block != NULL)
	{
		if (block->size > 0 && block->alc == IS_ALLOCATED)
			return (0);
		block = block->next;
	}
	return (1);
}

static void		ft_fusion(t_zones *zone)
{
	t_block		*block;
	t_block		*next_block;

	block = (void*)zone + sizeof(t_zones);
	while (block != NULL)
	{
		if (block->alc == 0 && block->next)
		{
			next_block = block->next;
			if (next_block->alc == 0)
			{
				block->size += next_block->size + sizeof(t_block);
				block->next = next_block->next;
			}
		}
		block = block->next;
	}
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
	free_log(ptr);
	if (block_tmp->alc == IS_ALLOCATED)
		block_tmp->alc = 0;
	if (check_empty_zone(zone_tmp))
		ft_delete_zone(zone_tmp);
	ft_fusion(zone_tmp);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_lock);
	ft_free(ptr);
	pthread_mutex_unlock(&g_lock);
}
