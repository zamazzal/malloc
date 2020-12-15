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

static int		ft_delete_zone_list(t_zones *zone)
{
	t_zones *tmp;
	t_zones *tmp2;

	tmp = g_zones_list;
	tmp2 = tmp;
	if (tmp == zone)
	{
		g_zones_list = (!tmp->next) ? NULL : g_zones_list->next;
		return (1);
	}
	while (tmp->next != NULL)
	{
		if (tmp->next == zone)
		{
			tmp->next = zone->next;
			if (!zone->next)
				tmp->next = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	g_zones_list = tmp2;
	return (1);
}

static int		ft_delete_zone(t_zones *zone)
{
	ft_delete_zone_list(zone);
	munmap((void*)zone, zone->size);
	return (0);
}

static int		check_empty_zone(void *ptr, long long	int *x)
{
	t_block *block_ptr;

	block_ptr = ptr + *x;
	if (block_ptr && block_ptr->size >= 1)
	{
		*x = *x + sizeof(t_block) + block_ptr->size;
		if (block_ptr->alc == IS_ALLOCATED)
			return (0);
		else
			return (2);
	}
	else
		(*x)++;
	return (1);
}

static int		ft_empty_zone(void)
{
	t_zones			*tmp;
	long long int	x;
	int				empty;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		empty = 0;
		x = sizeof(t_zones);
		while (x - 1 < (long long int)tmp->size)
		{
			empty = check_empty_zone(tmp, &x);
			if (empty == 0)
				break ;
			if (empty == 2 && tmp->zone_type == LARGE)
				return (ft_delete_zone(tmp));
		}
		if (empty == 1)
			return (ft_delete_zone(tmp));
		tmp = tmp->next;
	}
	return (0);
}

void			ft_free(void *ptr)
{
	long long int	x;
	t_block			*block_tmp;
	int				empty;

	x = (long long int)ptr;
	x -= sizeof(t_block);
	if (x < (long long int)sizeof(t_zones))
		return ;
	block_tmp = ptr - sizeof(t_block);
	block_tmp->alc = 0;
	empty = 1;
	while (empty)
		empty = ft_empty_zone();
}
