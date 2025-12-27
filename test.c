#include "includes/memory_manager.h"

int main()
{
    // printf("header is %ld bytes size\n", sizeof(t_memHeader));
    char *str = malloc(50);
    (void)str;
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
// 
    printf("test :%s", str);
    // for(int i = 0; i < 20; i++)
    // {
    //     char *s = malloc(i);
    //     (void)s
    // }
    show_alloc_mem();
// 
// 
    printf("----------test free--------------\n\n");
    free(str);
    char *nstr = malloc(1);
    char *nnstr = malloc(1);
// 
    show_alloc_mem();

}