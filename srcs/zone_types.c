/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:15:10 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/12 18:15:30 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		ft_check_type(size_t size)
{
	if (size > SMALL_SIZE)
		return (LARGE);
	else if (size > TINY_SIZE)
		return (SMALL);
	else
		return (TINY);
}

size_t	get_size_bytype(int type)
{
	size_t size;

	if (type == TINY)
		size = TINY_SIZE;
	if (type == SMALL)
		size = SMALL_SIZE;
	return (size);
}
