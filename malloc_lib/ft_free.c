#include "memory_manager.h"

void merge(t_memHeader *firstBlock, t_memHeader *secondBlock)
{
    firstBlock->next = secondBlock->next;
    firstBlock->size = firstBlock->size + secondBlock->size + sizeof(t_memHeader);
    if (secondBlock->next)
        secondBlock->next->prev = firstBlock;

}

void free(void *ptr)
{
    if(!ptr)
        return NULL;
    t_memHeader *blockToFree = (t_memHeader *)((char *)ptr - sizeof(t_memHeader));
    if(blockToFree->userMemory != ptr)
        return NULL;

    blockToFree->isFree = YES;
    if(blockToFree->next && blockToFree->next->isFree == YES)//UNIQUEMENT SI ILS APPARTIENNENT A LA MEME ZONE
        merge(blockToFree, blockToFree->next);
    if(blockToFree->prev && blockToFree->prev->isFree == YES)
        merge(blockToFree->prev, blockToFree);
}