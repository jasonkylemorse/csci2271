#include "myalloc.h"


int main() {
  double *p1, *p2;
  printf("&p1: %u, &p2: %u\n",&p1,&p2);
  myallocinit(80);
  printf("asked for an initial space of 80 and got .....\n");
  printallocation();
  p1 = (double *)myalloc(20);
  printf("asked for 20 and got .....\n");
  printallocation();
  p2 = (double *)myalloc(10);
  printf("asked for 10 and got .....\n");
  printallocation();
  p1 = (double *)myalloc(18);
  printf("asked for 18 without freeing so orphaned a block and got .....\n");
  printallocation();
  p2 = (double *)myalloc(20);
	printf("asked for 20 without freeing so orphaned a block and got .....\n");
  printallocation();
  p1 = NULL;
  //p2 = NULL;
  printf("Just set p1 = NULL, but p2 is unchanged and we see ...\n");
  printallocation();
  printf("time to do some garbage collection ...\n");
  mygc();
  printf("\nAfter GC is done......\n");
  printallocation();
}
