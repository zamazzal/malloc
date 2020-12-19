/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:41:03 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:42:51 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zones	*ft_addinlist(t_zones *new_zone)
{
	t_zones		*tmp;

	if (!g_zones_list)
		return (new_zone);
	tmp = g_zones_list;
	while (g_zones_list->next != NULL)
		g_zones_list = g_zones_list->next;
	g_zones_list->next = new_zone;
	g_zones_list = tmp;
	return (g_zones_list);
}

t_zones	*ft_delete_zone_list(t_zones *zone)
{
	t_zones *tmp;
	t_zones *tmp2;

	if (!g_zones_list)
		return (NULL);
	tmp = g_zones_list;
	if (tmp == zone)
		return ((!tmp->next) ? NULL : tmp->next);
	tmp2 = g_zones_list;
	while (tmp->next != NULL)
	{
		if (tmp->next == zone)
		{
			tmp->next = (zone->next) ? zone->next : NULL;
			break ;
		}
		tmp = tmp->next;
	}
	g_zones_list = tmp2;
	return (g_zones_list);
}
