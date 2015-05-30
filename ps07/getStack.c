/*
 * Find the absolute bottom of the stack and set stuff up.
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
 
unsigned long GC_init()
//void main(void)
{
    static int initted;
    FILE *statfp;
		unsigned long stack_bottom;
 //   if (initted)
 //       return;

    initted = 1;

    statfp = fopen("/proc/self/stat", "r");
    assert(statfp != NULL);
    fscanf(statfp,
           "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
           "%*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld "
           "%*ld %*ld %*ld %*ld %*llu %*lu %*ld "
           "%*lu %*lu %*lu %lu", &stack_bottom);
    fclose(statfp);
    printf("stack_bottom: %u\n",stack_bottom);
    return stack_bottom;
}

