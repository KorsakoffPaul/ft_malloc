#include "includes/memory_manager.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int main()
// {
//     char *s = malloc(4);
//     free(s);
//     ft_printf("new malloc\n");
//     s = malloc(4);
// }


int main(void)
{
    ft_printf("=== realloc basic tests ===\n");

    /* realloc(NULL, size) */
    char *p = realloc(NULL, 32);
    if (!p)
    {
        ft_printf("FAIL: realloc(NULL, 32)\n");
        return 1;
    }
    strcpy(p, "Hello realloc");
    ft_printf("OK: realloc(NULL, 32) -> %s\n", p);

    /* grow realloc */
    char *p2 = realloc(p, 128);
    if (!p2)
    {
        ft_printf("FAIL: realloc grow\n");
        free(p);
        return 1;
    }
    // ft_printf("OK: realloc grow preserved -> %s\n", p2);

    /* shrink realloc (no split, allowed) */
    char *p3 = realloc(p2, 8);
    if (!p3)
    {
        ft_printf("FAIL: realloc shrink\n");
        free(p2);
        return 1;
    }
    // ft_printf("OK: realloc shrink preserved -> %.7s\n", p3);

    /* realloc(ptr, 0) */
    char *p4 = realloc(p3, 0);
    if (p4 != NULL)
        ft_printf("FAIL: realloc(ptr, 0) should return NULL\n");
    else
        ft_printf("OK: realloc(ptr, 0)\n");

    /* realloc invalid pointer */
    int dummy;
    char *bad = realloc(&dummy, 32);
    if (bad != NULL)
        ft_printf("FAIL: realloc on invalid pointer\n");
    else
        ft_printf("OK: realloc invalid pointer rejected\n");

    ft_printf("=== test done ===\n");
    show_alloc_mem();
    return 0;

}