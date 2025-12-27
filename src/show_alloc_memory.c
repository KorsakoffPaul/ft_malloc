#include "memory_manager.h"

void printZones(t_memHeader *parser)
{
    while(parser->next)
    {
        if(!parser->isFree)
        {
            uintptr_t userMemStart = (uintptr_t)parser->userMemory;
            uintptr_t userMemEnd = (uintptr_t)parser->userMemory + parser->size;
            printf("%" PRIXPTR " - %" PRIXPTR " : %ld bytes\n", (unsigned long)userMemStart, (unsigned long)userMemEnd, userMemEnd - userMemStart);
        }
        parser = parser->next;
    }
}


void show_alloc_mem()
{
    t_memHeader *parser = g_zones.tiny;
    uintptr_t userMemStart = (uintptr_t)parser;
    // uintptr_t userMemEnd; 
    printf("TINY : %" PRIXPTR "\n", userMemStart);
    if (parser)
        printZones(parser);

    parser = g_zones.small;
    userMemStart = (uintptr_t)parser;
    printf("SMALL : %" PRIXPTR "\n", userMemStart);
    if(parser)
        printZones(parser);

    parser = g_zones.large;
    userMemStart = (uintptr_t)parser;
    printf("LARGE : %" PRIXPTR "\n", userMemStart);
    if(parser)
        printZones(parser);
    
    printf("end !!\n");
}