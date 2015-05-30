/* test2.c  This program reads up to 5 doubles from stdin, terminated
 * by a negative number.  It then inserts them into a list, prints the
 * list, and frees the list nodes.
 * More than 5 doubles gives a segmentation fault.
 */

#include "myalloc.h"

struct doubleNode {
  double val;
  struct doubleNode *next;
};

int main() {
  struct doubleNode *startnode, *endnode, *currentnode;
  double d;

  myallocinit(100);  // large enough for holding 6 nodes.
  // Create a chain of doubles, with header node
  startnode = (struct doubleNode *)myalloc(sizeof(struct doubleNode));
  endnode = startnode;
  while(1) {
    scanf("%lf", &d);
    if (d < 0.0) break;
    currentnode = (struct doubleNode *)myalloc(sizeof(struct doubleNode));
    currentnode->val = d;
    currentnode->next = NULL;
    endnode->next = currentnode;
    endnode = endnode->next;
  }

  printallocation();

  // Traverse the chain
  currentnode = startnode->next;
  while (currentnode != NULL) {
    printf("%0.2lf\t", currentnode->val);
    currentnode = currentnode->next;
  }
  printf("\n");

  // Free the nodes on the chain
  while (startnode != NULL) {
    currentnode = startnode->next;
    myfree(startnode);
    startnode = currentnode;
  }

  printallocation();
}