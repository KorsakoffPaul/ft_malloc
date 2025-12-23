#include "memory_manager.h"

void show_alloc_mem()
{
    t_memHeader *parser = g_zones.tiny;
    uintptr_t userMemStart = (uintptr_t)parser;
    uintptr_t userMemEnd; 
    printf("TINY : %" PRIXPTR "\n", userMemStart);
    while(parser->next)
    {
        userMemStart = (uintptr_t)parser->userMemory;
        userMemEnd = (uintptr_t)parser->userMemory + parser->size;
        printf("%" PRIXPTR " - %" PRIXPTR " : %ld bytes\n", (unsigned long)userMemStart, (unsigned long)userMemEnd, userMemEnd - userMemStart);
        parser = parser->next;
    }
    parser = g_zones.small;
    userMemStart = (uintptr_t)parser;
    printf("SMALL : %" PRIXPTR "\n", )
    printf("end !!\n");
}