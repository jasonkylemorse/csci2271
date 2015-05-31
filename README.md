Computer Systems
==================

This repository contains problem set assignments from CSCI2271 - Computer Systems (Spring 2015). More information on how the code works as well as known problems can be found in each problem set's writeup. 

#####Problem Set 1 (Introduction to C, Pointers, Finite State Machines)
* `assignment1-jasonmorse.c` - This program reads in a string of characters and uses an FSM to replace comments (chars surrounded by /* */) with a single space character. 

#####Problem Set 2 (Malloc, More FSMs, More Pointers)
* `assignment2a-jasonmorse.c` - This program reads in a string of characters and uses an FSM to determine if the pattern 'GCAG' exists. 
* `assignment2bc-jasonmorse.c` - This program reads in a string of characters and uses an FSM to determine if the characters 'G', 'C', 'A', and 'G' exist in that order, but not necessarily consecutively. 
* `assignment2d-jasonmorse.c` - This program reads in a string of characters and uses an FSM to determine how many times the pattern 'GCAG' occurs. 

#####Problem Set 3 (Pointers to Pointers, Linked Lists)
* `Part A`
	* `assignment3main-jasonmorse.c` - This program reads in a string of chars and uses an FSM to determine if a user-specified pattern exists. Structs were used to contain the string and its length.
	* `assignment3-jasonmorse.h` & `assignment3-jasonmorse.c` - Header and implementation for the string struct and related functions. 
* `Part B`
	* `assignment3PartB.c` - This program reads in a poem and splits it into individual lines. Each line is linked together using a double linked list data structure. 
	* `definitions.h` & `definitions.c` - Header and implementation for the node structs and related functions. 

#####Problem Set 4 (Structs as Linked List Payloads, Pointers to Functions)
* `Part A` 
	* `partA.h` & `partA.c` – Header and implementation for node struct, linked list struct, and related functions.
	* `mainA.c` – This program tests the creation of a linked list and manipulation of its contents.
* `Part B` 
	* `stock.h` & `stock.c` – Header and implementation for stock struct and related functions.
	* `mainB.c` – This program tests the addition, deletion, and traversal of stock structs within the linked list.

#####Problem Set 5 (Threads, Mutex Locks, Conditional Variables)
* `linked_list.h` & `linked_list.c` – Header and implementation for linked list data structure and related functions (taken from problem set 4).
* `temperatures_main.c` - Program that creates a linked list to contain temperature probe readings. Each temeprature probe's random number is generated simultaneously within independent threads, but since multiple threads cannot modify the linked list at the same, mutex locks are used to ensure that everything is done safely. 

#####Problem Set 6 (Pipes, Processes, Forking, PIDs)
* `assignment6-jasonmorse.c` - This program takes an input `.txt` file, toggles the case of each char, and creates a new `.txt` file with the result. A chain of three processes are created with pipes in between to send and receive information to/from one another. 

#####Problem Set 7 (Memory Allocation, Mark & Sweep Algorithm for Garbage Collection)
* `myalloc.h` & `myalloc.c` - This program is a recreation of the malloc and free Unix functions. It creates a pseudo heap to work with, and it explores the inner workings of memory allocation and garbage collection. There are functions for marking, allocating, coalescing free blocks, and cleaning up garbage.
* Various test files are provided.