// file: definitions.h
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: February 27, 2015

// PART B

/* a potential node definition */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

typedef struct word{
  char *w;
  int length;
  int freq;
  int lineCount;
  int *lines;
  struct word *next;
}word_t;

typedef struct string{
  char *stng;
  int len;
}String;

typedef struct wordContainer{
  word_t *wd;
  struct wordContainer *next;
}wordContainer_t;

typedef struct stringContainer{
  String *str;
  struct stringContainer *next;
}stringContainer_t;


//functions for reading from a file
int test_eol(char a);
int test_eof(char a);
char * returnLine(FILE *fp);  //returns line or NULL (if at end of file)
void printLine(char *line);

//functions for creating a  String
String *makeString(char * s);
void printString(String *s);
int stringLength(String *s);
int string_indexOf(String *s, String *sub, int from);
String *string_substring(String *s, int from, int to);
int string_indexOf(String *s, String *sub, int from);
int string_split(String *s, String *delim, String **array, int n);
int hasLine(word_t *word, int line);
void newLine(word_t **word, int line);
stringContainer_t *  insertStringIntoLinkedList(stringContainer_t * head, String * newString);
void displayStringList(stringContainer_t * head);

//functions for creating a word
word_t * createWord(char * w);
void printWord(word_t *m);
word_t *  insertWordIntoLinkedList(word_t *head, word_t *word, int line); 
void displayWordList(word_t * head);
word_t * findMostFrequentWord(word_t *head);
void printLines(int *lines, int numLines);
