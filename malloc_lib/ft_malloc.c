#include "memory_manager.h"
// #include

t_zones g_zones = {NULL};

bool initZones()
{
    g_zones.tiny = (t_memHeader *)mmap(NULL, TINYSIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    g_zones.small = (t_memHeader *)mmap(NULL, SMALLSIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    
    if (!g_zones.tiny || !g_zones.small)
        return 0;

    g_zones.tiny->zoneEnd = (char *)g_zones.tiny + TINYSIZE;
    g_zones.small->zoneEnd = (char *)g_zones.small + SMALLSIZE;

    g_zones.tiny->userMemory = (char *)g_zones.tiny + sizeof(t_memHeader);// g_zone.tiny + x ajoute x element de taille g_zone.tiny et g_zone + 1 trompe le compilateur qui pense qu'il s'agit d'un tableau
    g_zones.tiny->size = TINYSIZE - sizeof(t_memHeader);
    g_zones.tiny->isFree = YES;
    g_zones.tiny->next = NULL;
    
    g_zones.small->userMemory = (char *)g_zones.small + sizeof(t_memHeader);
    g_zones.small->size = SMALLSIZE - sizeof(t_memHeader);
    g_zones.small-> isFree = YES;
    g_zones.small->next = NULL;
    return 1;
}

void *createNewZone(int size)
{
    t_memHeader *newZone = (t_memHeader *)mmap(NULL, TINYSIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    if (!newZone)
        return NULL;//undefined
    newZone->isFree = YES;
    newZone->next = NULL;
    newZone->size = size - sizeof(t_memHeader);
    newZone->userMemory = (char *)newZone + sizeof(t_memHeader);
    newZone->zoneEnd = (char *)newZone + size;
    return newZone;
}

void *tinySmallAlloc(t_memHeader *parser, size_t alignedUserSize, size_t alignedBlockSize)//ici size = alignedUserSize + alligneHeaderSiez
{
    //reach an available freememHeader
    printf("parser->size :%ld\n", parser->size);
    while(parser->isFree == NO || parser->size < alignedUserSize)//tant que on a pas de block assez grand pour stocker size
    {
        printf("parser->size :%ld\n", parser->size);
        if (parser->next == NULL && (char *)parser->zoneEnd - ((char *)parser->userMemory + parser->size) > alignedBlockSize)//si on dépasse une zone/qu'il n'y en a plus
        {   printf("creating new zone\n");
            parser->next = createNewZone(TINYSIZE);
            if (!parser->next)
                return NULL;
        }
        parser = parser->next;
    }
    //useable place found
    parser->size = alignedUserSize;
    parser->isFree = NO;
    parser->userMemory = (char *)parser + sizeof(t_memHeader);
    printf("found useable place for %ld size\n", parser->size);
    if (!parser->next)//pas besoins de "couper" la zone valide. On ne coupe que si on veux optimiser
    {//si on est la, on était sur la fin de la chaine
        parser->next = (t_memHeader *)((char *) parser + alignedBlockSize);
        parser->next->isFree = YES;
        parser->next->size = (size_t)((char *)parser->next->zoneEnd - (char *)parser->next - sizeof(t_memHeader));
    }
    return parser->userMemory;
}

void *largeAlloc(size_t alignedUserSize, size_t alignedBlockSize)
{
    t_memHeader *newBlock = mmap(NULL, alignedBlockSize, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    t_memHeader *largeList = g_zones.large;
    
    if (!newBlock)
        return NULL;

    newBlock->isFree = NO;
    newBlock->next = NULL;
    newBlock->size = alignedUserSize;
    newBlock->userMemory = (char *)newBlock + sizeof(t_memHeader);
    newBlock->zoneEnd = NULL; //not important
    if (!largeList)
        g_zones.large = newBlock;
    else
    {
        while(largeList->next)
            largeList = largeList->next;
        largeList->next = newBlock;
    }
    return newBlock->userMemory;
        
}


void *ft_malloc(size_t size)//alliner size sur la memoire physique (8 ou 16)
{
    if (size <= 0)
        return NULL;
    if (g_zones.tiny == 0)//first call
    {
        if (!initZones())
            return NULL;
    }
    size_t alignedUserSize = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);//taille utilisateur alligné
    size_t alignedBlockSize = alignedUserSize + sizeof(t_memHeader);//taille utilisateur alligné + header alligné
    if (size <= 256)
        return(tinySmallAlloc(g_zones.tiny, alignedUserSize, alignedBlockSize));
    else if (size >= 4096)
        largeAlloc(alignedUserSize, alignedBlockSize);
    else
        return(tinySmallAlloc(g_zones.small, alignedUserSize, alignedBlockSize));
}

int main()
{
    // printf("%d", sizeof(t_memHeader));
    char *str = ft_malloc(15);
    str[0] = 'B';
    str[1] = 'o';
    str[2] = 'n';
    str[3] = 'j';
    str[4] = 'o';
    str[5] = 'u';
    str[6] = 'r';
    str[7] = 's';
    str[8] = ' ';
    str[9] = '9';
    str[10] = '1';
    str[11] = '1';
    str[12] = '1';
    str[13] = '\n';
    str[14] = '\n';
    str[15] = 0;
    // printf("test :%s", str);
    for(int i = 0; i < 20; i++)
    {
        ft_malloc(i);
    }
    show_alloc_mem();

}
