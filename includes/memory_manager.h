#ifndef MEMORY_MANAGER_H
# define MEMORY_MANAGER_H
# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <stdint.h>
# include <inttypes.h>
# include "../libft/includes/libft.h"


#define YES 1
#define NO 0
#define ALIGNMENT 16
#define TINYSIZE 32768//block = 320|8 * 4096(pagesize) = tinysize
#define SMALLSIZE 110592 //block = 1088|27 * 4096(pagesize) = smallsize

typedef struct s_memHeader
{
    void *zoneStart;
    void *zoneEnd;
    void *userMemory;
    size_t size;
    bool isFree;
    struct s_memHeader *next;
    struct s_memHeader *prev;
    int zoneLenght;
    char pading[4];
}t_memHeader __attribute__((aligned(ALIGNMENT)));

typedef struct s_zones
{
    t_memHeader *tiny;
    t_memHeader *small;
    t_memHeader *large;
}t_zones;

extern t_zones g_zones;

bool inZones(void *ptr);
bool searchInZone(uintptr_t ptr, t_memHeader *parser);
void merge(t_memHeader *firstBlock, t_memHeader *secondBlock);

void show_alloc_mem();
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);


#endif