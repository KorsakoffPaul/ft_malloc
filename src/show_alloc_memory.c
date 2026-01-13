#include "malloc.h"

int printZones(t_memHeader *parser)
{
	long bytnbr = 0;
    while(parser->next)
    {
        if(!parser->isFree)
        {
            uintptr_t userMemStart = (uintptr_t)parser->userMemory;
            uintptr_t userMemEnd = (uintptr_t)parser->userMemory + parser->size;
            ft_printf("%X - %X : %u bytes\n", (unsigned long)userMemStart, (unsigned long)userMemEnd, (unsigned int)userMemEnd - (unsigned int)userMemStart);
			bytnbr += (unsigned int)userMemEnd - (unsigned int)userMemStart;
		}
        parser = parser->next;
    }
	return bytnbr;
}

long printLarge(t_memHeader *parser)
{
	long bytnbr = 0; 
	while(parser)
	{
	    uintptr_t userMemStart = (uintptr_t)parser->userMemory;
        uintptr_t userMemEnd = (uintptr_t)parser->userMemory + parser->size;
        ft_printf("%X - %X : %u bytes\n", (unsigned long)userMemStart, (unsigned long)userMemEnd, (unsigned int)userMemEnd - (unsigned int)userMemStart);
		bytnbr += (unsigned int)userMemEnd - (unsigned int)userMemStart;
		parser = parser->next;
	}
	return bytnbr;
}

void show_alloc_mem()
{
	long totalbyte = 0;

    t_memHeader *parser = g_zones.tiny;
    uintptr_t userMemStart = (uintptr_t)parser;
    // uintptr_t userMemEnd; 
    ft_printf("TINY : %X\n", userMemStart);
    if (parser)
        totalbyte += printZones(parser);

    parser = g_zones.small;
    userMemStart = (uintptr_t)parser;
    ft_printf("SMALL : %X\n", userMemStart);
    if(parser)
        totalbyte += printZones(parser);

    parser = g_zones.large;
    userMemStart = (uintptr_t)parser;
    ft_printf("LARGE : %X\n", userMemStart);
    if(parser)
	{
        totalbyte += printLarge(parser);
	}
	if (totalbyte >__INT32_MAX__)
		ft_printf("Total : maximum int reach\n");
	else
		ft_printf("Total : %d bytes\n", (int)totalbyte);
    // printf("end !!\n");
}