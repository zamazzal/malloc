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
	char	*str;
	int i;

	i = 0;
	while (i < 1024)
	{
		str = ft_malloc(8024);
		i++;
	}
	//show_alloc_mem();
	//char	*ptr;
/*
	str = ft_malloc(578);
*/
	//ptr = ft_malloc(478);
	//ft_free(str);
	return (0);
}
