/* test5.c  This tests whether garbage collection works after a function 
 *          call exits. Note that after the AR is deallocated, a pointer 
 *          to the heap may still exist, and an unreachable block will
 *          not get garbage collected.
 */

#include "myalloc.h"

void f() {
  int *ip;
  char *cp;
  ip = (int *) myalloc(4 * sizeof(int));
  cp = (char *) myalloc(4 * sizeof(char));
  printf("In f after allocating ip, cp\n");
  printallocation();
  mygc();
  printf("In f after gc\n");
  printallocation();
}

void g() {   // this zeros out memory.
  int x[100];
  int i;
  for (i=0; i<100; i++)
    x[i] = 0;
}

int main() {
  int i;
  int *ip;
  char *cp;
  myallocinit(100);
  f();
  mygc();
  printf("In main after gc\n");
  printallocation();
  g();
  printf("In main after g() and gc\n");
  mygc();
  printallocation();

  ip = (int *) myalloc(4 * sizeof(int));
  printf("In main after allocating ip\n");
  printallocation();

  cp = (char *) myalloc(4 * sizeof(char));
  printf("In main after allocating cp\n");
  printallocation();
  for (i=0; i<4; i++) {
    ip[i] = i;
    cp[i] = 'A' + i;
  }

  mygc();
  printf("In main after gc\n");
  printallocation();
}
  
