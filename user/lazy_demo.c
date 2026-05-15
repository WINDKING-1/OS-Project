#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    char *p;
    int pages = 5;

    printf("lazy allocation demo\n");

    p = sbrk(4096 * pages);

    printf("sbrk finished\n");
    printf("accessing pages\n");

    for(int i = 0; i < pages; i++) {

        p[i * 4096] = 'A' + i;

        printf("touched page %d\n", i);
    }

    printf("done\n");

    exit(0);
}
