/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:31:12 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:39:51 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			ft_print_time(int fd)
{
	time_t		rawtime;
	struct tm	*timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	ft_putstr_fd("[ ", fd);
	ft_putnbr_fd(timeinfo->tm_hour, fd);
	ft_putchar_fd(':', fd);
	ft_putnbr_fd(timeinfo->tm_min, fd);
	ft_putchar_fd(':', fd);
	ft_putnbr_fd(timeinfo->tm_sec, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(timeinfo->tm_mday, fd);
	ft_putchar_fd('/', fd);
	ft_putnbr_fd(timeinfo->tm_mon + 1, fd);
	ft_putchar_fd('/', fd);
	ft_putnbr_fd(1900 + timeinfo->tm_year, fd);
	ft_putstr_fd(" ]", fd);
}

static void		ft_putzone_type(int type, int fd)
{
	if (type == TINY)
		ft_putstr_fd("TINY", fd);
	else if (type == SMALL)
		ft_putstr_fd("SMALL", fd);
	else if (type == LARGE)
		ft_putstr_fd("LARGE", fd);
}

static void		log_created_zone(void *ptr, int fd)
{
	t_zones			*zone_tmp;

	zone_tmp = ft_get_zone(ptr);
	if (!zone_tmp)
		return ;
	ft_print_time(fd);
	ft_putchar_fd(' ', fd);
	ft_putstr_fd("+zone ", fd);
	ft_putzone_type(zone_tmp->zone_type, fd);
	ft_putstr_fd(" : ", fd);
	ft_putnbr_fd(zone_tmp->size, fd);
	ft_putendl_fd(" bytes", fd);
}

static void		log_created_block(void *ptr, int fd)
{
	t_block			*block_tmp;

	block_tmp = ft_get_block(ptr);
	if (!block_tmp)
		return ;
	ft_print_time(fd);
	ft_putstr_fd(" : ", fd);
	ft_putstr_fd("+block ", fd);
	ft_putnbr_fd(block_tmp->size, fd);
	ft_putendl_fd(" bytes", fd);
}

void			malloc_log(void *ptr, int new_z)
{
	int fd;

	if (DEBUG)
	{
		if (new_z)
			log_created_zone(ptr, 1);
		log_created_block(ptr, 1);
	}
	if (LOG)
	{
		fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (fd == -1)
			return ;
		if (new_z)
			log_created_zone(ptr, fd);
		log_created_block(ptr, fd);
	}
	return ;
}
