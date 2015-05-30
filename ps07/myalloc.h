#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void myallocinit(int size); // allocates "size" bytes for use, returns nothing
void *myalloc(int size); // break initialized block into a size that can fit the request, returns void pointer
void myfree(void *ptr); // mark space as unallocated
void printmyallocation(); // print
void mygc(); // garbage collector 
