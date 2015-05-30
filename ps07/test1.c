#include "myalloc.h"

int main() {
  double *p1, *p2;
  myallocinit(50);
  printallocation();
  p1 = (double *)myalloc(20);
  printallocation();
  p2 = (double *)myalloc(10);
  printallocation();
  myfree(p1);
  printallocation();
  myfree(p2);
  printallocation();
  p1 = (double *)myalloc(18);
  printallocation();
  p2 = (double *)myalloc(20);
  printallocation();
  myfree(p1);
  printallocation();
  myfree(p2);
  printallocation();
  p1 = (double *)myalloc(56);
  printallocation();
}