/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:40:49 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/12 20:05:21 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		main(void)
{
	char	*ktr, *str;

	ktr = ft_malloc(24);
	ktr = ft_malloc(13);
	str = ft_malloc(1337);
	ft_blocks_info(str);

	ft_free(str);
	show_alloc_mem();
	//char	*ptr;
/*
	str = ft_malloc(578);
*/
	//ptr = ft_malloc(478);
	return (0);
}