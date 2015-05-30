// file: assignment3-jasonmorse.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: February 27, 2015

// PART A

#include "assignment3-jasonmorse.h"

//functions for creating a String
String * makeString(char * s) //pass in a pointer to a block of chars
{
  String *new = (String *) malloc (sizeof(String)); //create memory for String
  new->stng = (char *) malloc(sizeof(char) * strlen(s)); //create memory for chars in String
  strcpy(new->stng,s);  //copy the passsed chars to field in String
  new->len = strlen(new->stng);
  return new; //return filled in Sreing struct
}

void printString(String *s){
  char * c;
  int i=0;
  c = s->stng;  //point to the start of the chars in the String struct
  
  while (*(c+i) != '\0'){
    printf("%c",*(c+i)); //no end of line
    i++;
  }
  printf("\n");
}


int stringLength(String *s)
{
  return s->len;
}