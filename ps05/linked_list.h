// file: linked_list.h
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: March 31, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
	void *item;
	struct node *next;
	struct node *prev;
}node_t;

typedef struct doubleLinkedList{
	node_t *firstNode;
	node_t *lastNode;
}doubleLinkedList_t;

typedef doubleLinkedList_t * list;

// create a new double linked list
list createList(void);

// create a new node
struct node * createNode(void *item);

// insert a node at the end of the list
void insertNodeEnd(list myList, void *item);

// delete a node from the list
void deleteNode(list myList, void *item);

// traverse the list using the next field (a forward traversal)
void forwardTraversal(list myList, void (*printData)(void *item));

// traverse the list using the prior field (a backward traversal)
void backwardTraversal(list myList, void (*printData)(void *item));

// return an item from a particular node in the list
void * getItem(list myList, int nodeIndex);

// print integer
void printInt(void *item);

// print string
void printString(void *item);


