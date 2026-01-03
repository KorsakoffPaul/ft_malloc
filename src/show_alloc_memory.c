#include "memory_manager.h"

void printZones(t_memHeader *parser)
{
    while(parser->next)
    {
        if(!parser->isFree)
        {
            uintptr_t userMemStart = (uintptr_t)parser->userMemory;
            uintptr_t userMemEnd = (uintptr_t)parser->userMemory + parser->size;
            ft_printf("%X - %X : %u bytes\n", (unsigned long)userMemStart, (unsigned long)userMemEnd, (unsigned int)userMemEnd - (unsigned int)userMemStart);
        }
        parser = parser->next;
    }
}


void show_alloc_mem()
{
    t_memHeader *parser = g_zones.tiny;
    uintptr_t userMemStart = (uintptr_t)parser;
    // uintptr_t userMemEnd; 
    ft_printf("TINY : %X\n", userMemStart);
    if (parser)
        printZones(parser);

    parser = g_zones.small;
    userMemStart = (uintptr_t)parser;
    ft_printf("SMALL : %X\n", userMemStart);
    if(parser)
        printZones(parser);

    parser = g_zones.large;
    userMemStart = (uintptr_t)parser;
    ft_printf("LARGE : %X\n", userMemStart);
    if(parser)
        printZones(parser);
    
    // printf("end !!\n");
}