// file: assignment3-jasonmorse.h
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: February 27, 2015

// PART A

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct string{
  char *stng;
  int len;
}String;

String *makeString(char * s);
void printString(String *s);
int stringLength(String *s);