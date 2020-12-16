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
		return (1);
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
	return (1);
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

static int		check_empty_zone(void *ptr, long long int *x, int type)
{
	t_block *block_ptr;

	block_ptr = ptr + *x;
	if (block_ptr && block_ptr->size >= 1)
	{
		*x = *x + sizeof(t_block) + block_ptr->size;
		if (block_ptr->alc == IS_ALLOCATED)
			return (0);
		else if (!block_ptr->alc && type == LARGE)
			return (2);
	}
	else
		(*x)++;
	return (1);
}

static int		ft_check_blocks(t_zones *tmp, long long *x)
{
	int rtn;
	int	empty;

	empty = 0;
	rtn = 0;
	while ((*x) - 1 < (long long int)tmp->size)
	{
		empty = check_empty_zone(tmp, x, tmp->zone_type);
		if (empty == 0)
			break ;
		if (empty == 2)
		{
			if ((rtn = ft_delete_zone(tmp)))
				return (1);
		}
	}
	if (empty == 1)
	{
		if ((rtn = ft_delete_zone(tmp)))
			return (1);
	}
	return (0);
}

int				ft_empty_zone(void)
{
	t_zones			*tmp;
	long long int	x;
	int				rtn;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		x = sizeof(t_zones);
		rtn = ft_check_blocks(tmp, &x);
		if (rtn != 0)
			return (rtn);
		tmp = tmp->next;
	}
	return (0);
}
