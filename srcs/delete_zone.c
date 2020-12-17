/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:35:50 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/15 18:36:30 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_delete_zone_list(t_zones *zone)
{
	t_zones *tmp;

	tmp = g_zones_list;
	if (tmp == zone)
	{
		g_zones_list = (!tmp->next) ? NULL : g_zones_list->next;
		return (0);
	}
	while (tmp->next != NULL)
	{
		if (tmp->next == zone)
		{
			tmp->next = (tmp->next->next) ? tmp->next->next : NULL;
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

static int		ft_delete_zone(t_zones *zone)
{
	void	*ptr;
	size_t	ptr_len;
/* // ask for this
	if (zone->zone_type == SMALL || zone->zone_type == TINY)
	{
		if (check_zone_type_i(zone->zone_type) <= 1)
			return (0);
	}
*/
	ptr = (void*)zone;
	ptr_len = zone->size;
	ft_delete_zone_list(zone);
	ft_bzero(ptr, ptr_len);
	if (munmap(ptr, ptr_len) == -1)
		return (0);
	return (1);
}

static int		check_empty_zone(t_zones *zone)
{
	long long int	x;
	t_block			*block;

	x = sizeof(t_block);
	while (x + 1 < (long long)zone->size)
	{
		block = (void*)zone + x;
		if (block && block->size > 0)
		{
			if (block->alc == IS_ALLOCATED)
				return (0);
			else if (!block->alc && zone->zone_type == LARGE)
				return (1);
			x += block->size;
		}
		else
			x++;
	}
	return (1);
}

int		ft_empty_zone(t_zones *zone)
{
	if (check_empty_zone(zone))
		return (ft_delete_zone(zone));
	return (0);
}
