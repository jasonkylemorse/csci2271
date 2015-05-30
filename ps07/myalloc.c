// file: myalloc.c
// author: Jason Morse
// date: May 3, 2015
// class: Computer Systems - Garbage Collector Assignment
//

#include "myalloc.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <signal.h>

void *myalloc2(int size);
void coalesce();
void mark(int *p);
void sweep(int *p);

//helper functions
int *isPtr(int *p);
int blockMarked(int *p);
void markBlock(int *p);
void unmarkBlock(int *p);
int blockAllocated(int *p);
void allocateBlock(int *p);
void unallocateBlock(int *p);
int length(int *p);
int *nextBlock(int *p);

int *start; // points to first block in pseudo-heap (after header)
int heap; // contains size of the pseudo-heap

void myallocinit(int size) {

  // add space for header and alignment padding, then malloc
  int blocklen = ((size + 3) / 8 + 1) * 8;
  start = (int *)malloc(blocklen + 8);
  if (start == NULL) {
    printf("Cannot init that much space\n");
    exit(1);
  }

  heap = blocklen; // store size of pseudo-heap for later usage
  *start = blocklen; // since pseudo-heap is completely unallocated, store entire size in header
  start++; // move pointer to after header
  *(nextBlock(start)-1) = 1; // set sentinel block = 1 (size = 0, allocated = 1)
}

void printallocation() {

  int size = length(start);
  int *temp = start;
  char yes[] = "Allocated";
  char no[] = "Unallocated";
  char * isAlloc;
  
  // iterate through heap and print out block information
  while (size != 0){

    if (blockAllocated(temp) == 1) {
      isAlloc = yes;
    } else {
      isAlloc = no;
    }

    printf("Block Address: %p \tSize: %d words (%d bytes) \t%s\n", temp, size, size*4, isAlloc);
    temp = nextBlock(temp);
    size = length(temp);
  }
  printf("\n");
}

void *myalloc(int size) {

  void *ptr = myalloc2(size);

  // if myalloc2 can't find a big enough space, coalesce and try again
  if (ptr == NULL) {
    printf("Not enough size in heap for this request! Coalescing and trying again...\n");
    coalesce();
    ptr = myalloc2(size);
  }
  return ptr;
}

void *myalloc2(int size) {

  int newsize = ((size+3) / 8 + 1) * 8; // add space for alignment purposes
  printf("In myalloc2: asked for %d bytes, got %d\n", size, newsize);
  int *ptr = start; // points to first block
  int *newptr = start-1; // points to first block's header
  int sizeOfBlock = *(newptr); // get size of block from header

  while (sizeOfBlock != 0) {

    // if block is unallocated and big enough to fit the request, allocate it and adjust sizes
    if (sizeOfBlock > newsize && (blockAllocated(ptr) == 0)) {
      *newptr = newsize;
      allocateBlock(ptr);
      *(nextBlock(ptr)-1) = sizeOfBlock - newsize;
      return ptr;
    }

    // if block is unallocated and a perect fit for the request, just allocate it
    if (sizeOfBlock == newsize && (blockAllocated(ptr) == 0)) {
      allocateBlock(ptr);
      return ptr;
    }

    // if block doesn't meet requirements, jump to the next one
    ptr = nextBlock(ptr);
    newptr = ptr - 1;
    sizeOfBlock = *(ptr-1);

    // allocating makes size 1 higher than it actually is
    if (blockAllocated(ptr) == 1) {
      sizeOfBlock = sizeOfBlock - 1;
    }
  }
  return NULL;
}

void myfree(void *p) {
  printf("In myfree: freeing block at address %p\n", p);
  unallocateBlock(p);
}

void coalesce() {
  int *ptr = start; //start at the first block
  int *nextptr; //an extra pointer

  while (length(ptr) != 0) {

    nextptr = nextBlock(ptr);

    // if the current block and next block are both unallocated, merge them
    if (blockAllocated(ptr) == 0 && blockAllocated(nextptr) == 0) {
      *(ptr-1) = *(ptr-1) + *(nextptr-1);
      nextptr = nextBlock(nextptr);
      continue; // skip next line and continue while-loop
    }
    ptr = nextBlock(ptr);
  }
} 

void mygc() {
  //int **max = (int **) 0xbfffffffUL;   // the address of the top of the stack
  
  unsigned long stack_bottom;
  int **max =  (int **) GC_init();   // get the address of the bottom of the stack
  int* q;
  int **p = &q;    // the address of the bottom of the stack
  
  while (p < max) {
    //printf("0. p: %u, *p: %u max: %u\n",p,*p,max);
    mark(*p);
    p++;
  }

  // sweep from root and then call coalesce
  sweep(q);
  coalesce();
}

void mark(int *p) {
  
  int i = 0;
  int size;
  int *ptr;
  ptr = isPtr(p);

  // if the item is a pointer, allocated, and unmarked, then mark it
  if (ptr != NULL && blockAllocated(ptr) == 1) {
    if (blockMarked(ptr) == 0) {
      markBlock(ptr);
    }
    
    // call mark on entire length of the block that we found
    size = length(ptr);
    while(++i < size) {
      mark(ptr + i);
    }
  }
}

void sweep(int *ptr) {
  ptr = start;

  while (length(ptr) != 0) {

    // if the block is allocated and unmarked, then free it
    if (blockAllocated(ptr) == 1 && blockMarked(ptr) == 0) {
      myfree(ptr);

    // else if the block is marked, unmark it
    } else if (blockMarked(ptr) == 1) {
      unmarkBlock(ptr);
    }
    ptr = nextBlock(ptr);
  }
}

int *isPtr(int *p) {  
 // this is a very inefficient algorithm
 //return the pointer or NULL
  int *ptr = start;

  // if the item is between the start of the pseudo-heap and the end of it, then it's a pointer
  if (ptr <= p && p <= (ptr + heap)) {
    return p;
  } else {
    return NULL;
  }
}

int blockMarked(int *p) {
  // check if block is marked (second to last bit) by arithmetic AND between size and ~2 (1111...1101) 
  if (*(p-1) == (*(p-1) & ~0x2)) {
    return 0;
  } else {
    return 1;
  }
}

void markBlock(int *p) {
  // mark block (toggle second to last bit) by arithmetic OR between size and 2 (0000...0010) 
  *(p-1) = *(p-1) | 0x2;
}

void unmarkBlock(int *p) {
 // unmark block (toggle second to last bit) by arithmetic AND between size and ~2 (111...1101) 
  *(p-1) = *(p-1) & ~0x2;
}

int blockAllocated(int *p) {
  // check if block is allocated (last bit) by size mod 2
  if (*(p-1) % 2 == 1) {
    return 1;
  } else {
    return 0;
  }
}

void allocateBlock(int *p) {
  // allocate block (toggle last bit) by adding 1
  *(p-1) = *(p-1) + 1;
}

void unallocateBlock(int *p) {
  // unallocate block (toggle last bit) by subtracting 1
  *(p-1) = (*(p-1) - 1);
}

int *nextBlock(int *p) {
  // get to next block by adding the current block's size (in words) to its address
  return p + length(p);
}

int length(int *p) { 
  // get size of block (in words) by looking in header and dividing by 4
  return (*(p-1)/8*8)/4;

}
