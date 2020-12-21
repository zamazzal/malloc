/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:31:12 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:45:57 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		log_deleted_block(void *ptr, int fd)
{
	t_block			*block_tmp;

	block_tmp = ft_get_block(ptr);
	if (!block_tmp)
		return ;
	ft_print_time(fd);
	ft_putstr_fd(" : ", fd);
	ft_putstr_fd("-block ", fd);
	ft_putnbr_fd(block_tmp->size, fd);
	ft_putendl_fd(" bytes", fd);
}

void			free_log(void *ptr)
{
	int fd;

	if (DEBUG)
		log_deleted_block(ptr, 1);
	if (LOG)
	{
		fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (fd == -1)
			return ;
		log_deleted_block(ptr, fd);
	}
	return ;
}
