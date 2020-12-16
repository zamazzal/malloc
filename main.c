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
char *addr;

addr = ft_malloc(400);
ft_free(addr);
/*addr = ft_malloc(400);
ft_free(addr);
addr = ft_malloc(400);
ft_free(addr);
addr = ft_malloc(400);
ft_free(addr);
*/
show_alloc_mem();
return (0);
}