/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 04:42:12 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:42:35 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem_ex(void)
{
	int		fd;
	char	c;

	fd = open(LOG_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	while (read(fd, &c, 1) > 0)
	{
		ft_putchar(c);
	}
}
