#include "includes/memory_manager.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MB (1024 * 1024)
#define N 200

int main(void)
{
	printf("pagesize :%ld\n", sysconf(_SC_PAGESIZE));

	char *q;
	free(q);
	void *testt = malloc(899988);
	void *test2 = malloc(988888);
	void *test1 = malloc(98888);
	show_alloc_mem();
	free(testt);
	free(test1);
	free(test2);
	show_alloc_mem();
	if (testt)
		free(testt);
	else
		ft_printf("maloc error\n");
	void *atest = malloc(16);
	free(atest);
	free(atest); // doit crasher ou ignorer ?

	void *p1 = malloc(32);
	void *p2 = malloc(32);
	memset(p1, 'A', 32);
	memset(p2, 'B', 32);


    // printf("===== TEST GROSSES ALLOCATIONS =====\n");

    // /* 1️⃣ Allocation 1 MB */
    // printf("\n[1] malloc 1 MB\n");
    // char *a = malloc(1 * MB);
    // if (!a)
    //     return 1;
    // memset(a, 'A', 1 * MB);
    // printf("OK\n");

    // /* 2️⃣ Allocation 10 MB */
    // printf("\n[2] malloc 10 MB\n");
    // char *b = malloc(10 * MB);
    // if (!b)
    //     return 1;
    // memset(b, 'B', 10 * MB);
    // printf("OK\n");
    // // show_alloc_mem();
    // /* 3️⃣ realloc plus grand */
    // printf("\n[3] realloc 1 MB -> 5 MB\n");
    // a = realloc(a, 5 * MB);
    // if (!a)
    //     return 1;
    // if (a[0] != 'A')
    //     printf("❌ données corrompues après realloc\n");
    // memset(a, 'C', 5 * MB);
    // printf("OK\n");

    // /* 4️⃣ realloc plus petit (doit marcher même si tu ignores le shrink) */
    // printf("\n[4] realloc 10 MB -> 2 MB\n");
    // b = realloc(b, 2 * MB);
    // if (!b)
    //     return 1;
    // if (b[0] != 'B')
    //     printf("❌ données corrompues après realloc\n");
    // printf("OK\n");

    // /* 5️⃣ Free partiel */
    // printf("\n[5] free a (5 MB)\n");
    // free(a);
    // printf("OK\n");

    // /* 6️⃣ Nouvelle grosse alloc après free */
    // printf("\n[6] malloc 8 MB (test reuse / fragmentation)\n");
    // char *c = malloc(8 * MB);
    // if (!c)
    //     return 1;
    // memset(c, 'D', 8 * MB);
    // printf("OK\n");

    // /* 7️⃣ realloc énorme */
    // printf("\n[7] realloc 8 MB -> 32 MB\n");
    // c = realloc(c, 32 * MB);
    // if (!c)
    //     return 1;
    // printf("OK\n");

    // /* 8️⃣ Nettoyage */
    // printf("\n[8] free all\n");
    // free(b);
    // free(c);

    // printf("\n===== FIN TEST GROSSES ALLOCATIONS =====\n");
    // return 0;*/


    void *ptrs[N];

    printf("=== malloc / free basic ===\n");
    for (int i = 0; i < N; i++)
    {
        ptrs[i] = malloc(32 + (i % 64));
        // ft_printf("i = %d\t", i);
        if (!ptrs[i])
        {
            printf("malloc failed at %d\n", i);
            return 1;
        }
        memset(ptrs[i], i, 32);
    }

    printf("=== free half ===\n");
    for (int i = 0; i < N; i += 2)
        free(ptrs[i]);

    printf("=== realloc grow ===\n");
    for (int i = 1; i < N; i += 2)
    {
		// printf("\n\nfor nb :%d\n", i);
        void *p = realloc(ptrs[i], 254);
        if (!p)
        {
            printf("realloc grow failed at %d\n", i);
            return 1;
        }
        ptrs[i] = p;
    }

    printf("=== realloc shrink ===\n");
    for (int i = 1; i < N; i += 2)
    {
        void *p = realloc(ptrs[i], 16);
        if (!p)
        {
            printf("realloc shrink failed at %d\n", i);
            return 1;
        }
        ptrs[i] = p;
    }

    printf("=== free all ===\n");
    for (int i = 0; i < N; i++)
        free(ptrs[i]);

    printf("=== realloc NULL ===\n");
    void *p = realloc(NULL, 128);
    if (!p)
        printf("FAIL realloc(NULL)\n");
    free(p);

    printf("=== realloc ptr, 0 ===\n");
    p = malloc(64);
    p = realloc(p, 0);
    if (p != NULL)
        printf("FAIL realloc(ptr, 0)\n");

    printf("=== invalid realloc ===\n");
    int dummy;
    void *bad = realloc(&dummy, 32);
    if (bad != NULL)
        printf("FAIL realloc invalid ptr\n");

    printf("=== reuse freed blocks ===\n");
    void *a = malloc(64);
    void *b = malloc(64);
    free(a);
    void *c = malloc(64);
    if (c != a)
        printf("NOTE: block not reused (not an error)\n");
    free(b);
    free(c);

    printf("=== alternating alloc/free ===\n");
    for (int i = 0; i < 10000; i++)
    {
        void *x = malloc(32);
        free(x);
    }

    printf("=== test finished ===\n");
    return 0;
}
