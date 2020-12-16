/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:27:22 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/15 18:27:34 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_zone_type_i(int type)
{
	t_zones	*tmp;
	int		i;

	tmp = g_zones_list;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->zone_type == type)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
