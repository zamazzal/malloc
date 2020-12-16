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

void			ft_free(void *ptr)
{
	long long int	x;
	t_block			*block_tmp;
	int				empty;

	if (!ptr)
		return ;
	x = (long long int)ptr;
	x -= sizeof(t_block);
	if (x < (long long int)sizeof(t_zones))
		return ;
	block_tmp = ptr - sizeof(t_block);
	if (block_tmp->alc == IS_ALLOCATED)
		block_tmp->alc = 0;
	empty = 1;
	while (empty)
		empty = ft_empty_zone();
}
