#include "malloc.h"

t_block		   *ft_get_block(void *ptr)
{
	t_zones			*tmp;
	t_block			*block;
	long long int	x;
	void			*ptr_tmp;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		x = sizeof(t_zones);
		while (x + 1 < (long long)tmp->size)
		{
			block = (void*)tmp + x;
			if (block && block->size > 0)
			{
				ptr_tmp = (void*)block + sizeof(t_block);
				if (ptr == ptr_tmp)
					return (block);
				x += sizeof(t_block) + block->size;
			}
			else
				x++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_zones        *ft_get_zone(void *ptr)
{
	t_zones			*tmp;
	t_block			*block;
	long long int	x;
	void			*ptr_tmp;

	tmp = g_zones_list;
	while (tmp != NULL)
	{
		x = sizeof(t_zones);
		while (x + 1 < (long long)tmp->size)
		{
			block = (void*)tmp + x;
			if (block && block->size > 0)
			{
				ptr_tmp = (void*)block + sizeof(t_block);
				if (ptr == ptr_tmp)
					return (tmp);
				x += sizeof(t_block) + block->size;
			}
			else
				x++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}


size_t		ft_blocks_info(void const *ptr)
{
	t_block			*block_tmp;

	block_tmp = ft_get_block((void*)ptr);
	if (!block_tmp)
		return (-1);
	ft_putstr("0x10");
	ft_putbase((long long int)ptr, 16);
	ft_putstr(" - ");
	ft_putnbr(block_tmp->size);
	ft_putendl(" bytes");
	return (block_tmp->size);
}

size_t		ft_block_len(void const *ptr)
{
	t_block			*block_tmp;

	block_tmp = ft_get_block((void*)ptr);
	if (!block_tmp)
		return (0);
	return (block_tmp->size);
}