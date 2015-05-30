// file: mainA.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: March 18, 2015

#include "partA.h"

// tests functions
int main(int argc, char *argv[]) {

	printf("Creating list...\n");
	list myList = createList();

	printf("Inserting string 'hi'...\n");
	insertNodeEnd(myList, "hi");

	printf("Inserting string 'my'...\n");
	insertNodeEnd(myList, "my");

	printf("Inserting string 'name'...\n");
	insertNodeEnd(myList, "name");

	printf("Inserting string 'is'...\n");
	insertNodeEnd(myList, "is");

	printf("Inserting string 'jason'...\n");
	insertNodeEnd(myList, "jason");

	forwardTraversal(myList, printString);
	backwardTraversal(myList, printString);

	printf("\nDeleting string 'name'...\n");
	deleteNode(myList, "name");

	printf("\nDeleting string 'zebra'...\n");
	deleteNode(myList, "zebra");

	forwardTraversal(myList, printString);
	backwardTraversal(myList, printString);

	printf("\nObtaining item at index 3 (should be jason)...\n");
	char *result = getItem(myList, 3);

	printf("The item at index 3 is: %s\n", result);

	printf("\nTest complete.\n");
	return 0;
}