/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:31:12 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/14 19:31:14 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		ft_print_time(void)
{
	time_t		rawtime;
	struct tm	*timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	ft_putstr("[ ");
	ft_putnbr(timeinfo->tm_hour);
	ft_putchar(':');
	ft_putnbr(timeinfo->tm_min);
	ft_putchar(':');
	ft_putnbr(timeinfo->tm_sec);
	ft_putchar(' ');
	ft_putnbr(timeinfo->tm_mday);
	ft_putchar('/');
	ft_putnbr(timeinfo->tm_mon + 1);
	ft_putchar('/');
	ft_putnbr(1900 + timeinfo->tm_year);
	ft_putstr(" ]");
}

static void		ft_putzone_type(int type)
{
	if (type == TINY)
		ft_putstr("TINY");
	else if (type == SMALL)
		ft_putstr("SMALL");
	else if (type == LARGE)
		ft_putstr("LARGE");
}

static void		log_created_zone(void *ptr)
{
	long long int	x;
	t_zones			*zone_tmp;

	x = (long long int)ptr;
	x -= (sizeof(t_block) + sizeof(t_zones));
	if (x <= 0)
		return ;
	zone_tmp = (void*)ptr - (sizeof(t_block) + sizeof(t_zones));
	ft_putstr("+zone ");
	ft_print_time();
	ft_putchar(' ');
	ft_putzone_type(zone_tmp->zone_type);
	ft_putstr(" : ");
	ft_putnbr(zone_tmp->size);
	ft_putendl(" bytes");
}

static void		log_created_block(void *ptr)
{
	long long int	x;
	t_block			*block_tmp;

	x = (long long int)ptr;
	x -= sizeof(t_block);
	if (x < (long long int)sizeof(t_zones))
		return ;
	block_tmp = (void*)ptr - sizeof(t_block);
	ft_putstr("+block ");
	ft_print_time();
	ft_putchar(' ');
	ft_putstr("0x10");
	ft_putbase((long long int)ptr, 16);
	ft_putstr(" - ");
	ft_putstr("0x10");
	ft_putbase((long long int)ptr + block_tmp->size, 16);
	ft_putstr(" : ");
	ft_putnbr(block_tmp->size);
	ft_putendl(" bytes");
}

void			malloc_log(void *ptr, int new_z)
{
	if (new_z)
		log_created_zone(ptr);
	log_created_block(ptr);
	return ;
}
