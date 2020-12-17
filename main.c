/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:40:49 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/15 12:41:22 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main()
{
int i;
char *addr;

i = 0;
while (i < 1024)
{
addr = (char*)ft_malloc(1024);
addr[0] = 42;
ft_free(addr);
i++;
}
show_alloc_mem();
return (0);
}