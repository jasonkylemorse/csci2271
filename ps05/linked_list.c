// file: linked_list.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: March 31, 2015

#include "linked_list.h"
//#include "stock.h"

// create a new double linked list
list createList(void) {
	list myList;
	myList = (list)malloc(sizeof(doubleLinkedList_t));
	myList->firstNode = NULL;
	myList->lastNode = NULL;
	return myList;
}

// create a new node
struct node * createNode(void *item) {
	node_t *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->item = item;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

// insert a node at the end of the list
void insertNodeEnd(list myList, void *item) {
	node_t *newNode = createNode(item);
	if (myList->firstNode == NULL) {
		myList->firstNode = newNode;
		myList->lastNode = newNode;
		return;
	}

	newNode->prev = myList->lastNode;
	myList->lastNode->next = newNode;
	myList->lastNode = newNode;
}

// delete a node from the list
void deleteNode(list myList, void *item) {
	node_t *temp = myList->firstNode;
	node_t *a;
	node_t *b;

	if (temp == NULL) {
		printf("No items in this list to delete!");
		return;
	} else {
		while(temp != NULL) {
			if (temp->item == item) {

				a = temp->prev;
				b = temp->next;

				if (a == NULL && b == NULL) { // empty list
					a->next = NULL;
					b->prev = NULL;
					return;
				} else if (a != NULL && b != NULL) { // middle of list
					a->next = b;
					b->prev = a;
					return;
				} else if (a != NULL && b == NULL) { // last element
					a->next = NULL;
					myList->lastNode = a;
					return;
				} else if (a == NULL && b != NULL) { // first element
					b->prev = NULL;
					myList->firstNode = b;
					return;
				}

			} else if (temp->next == NULL) {
				printf("That item was not found in this list!\n");
				return;
			} else {
				temp = temp->next;
			}
		}

	}
}

// traverse the list using the next field (a forward traversal)
void forwardTraversal(list myList, void (*printData)(void *item)) {
	node_t *temp = myList->firstNode;
	printf("\nForward Traversal: \n\n");
	while (temp != NULL) {
		printData(temp->item);
		temp = temp->next;
	}
	printf("\n");
}

// traverse the list using the prior field (a backward traversal)
void backwardTraversal(list myList, void (*printData)(void *item)) {
	node_t *temp = myList->lastNode;
	printf("\nBackward Traversal: \n");
	while (temp != NULL) {
		printData(temp->item);
		temp = temp->prev;
	}
	printf("\n");
}

// return an item from a particular node in the list
void * getItem(list myList, int nodeIndex) {
	int index = 0;
	node_t *temp = myList->firstNode;
	while (index < nodeIndex) {
		temp = temp->next;
		index++;
	}
	return temp->item;
}

// print integer
void printInt(void *item){
	int *x = (int *)item;
	printf("%d ", *x);
}

// print string
void printString(void *item){
	char *x = (char *)item;
	printf("%s ", x);
}