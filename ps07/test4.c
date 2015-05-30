#include "myalloc.h"

int main() {
  char *p;
  myallocinit(100);
  p = (char *)myalloc(4);
  printallocation();
    myfree(p);
  printallocation();
  p = (char *)myalloc(6);
  printallocation();
  p = (char *)myalloc(10);
  printallocation();
  
  mygc();
  printallocation();
}