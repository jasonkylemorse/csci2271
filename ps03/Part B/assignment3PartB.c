// file: assignment3PartB.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: February 27, 2015

// PART B

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "definitions.h"
  
int main() {
  char *line;
  char *test;
  String *S;
  stringContainer_t *scHead = NULL;
  stringContainer_t *scTemp;
  word_t *word, *wdHead=NULL, *mostFrequent;
  String * newString;
  word_t * W;
  FILE *fp;
  int lineNum=0;
  
  /* opening file for reading */
  fp = fopen("poem.txt" , "r");
  if(fp == NULL) {
    perror("Error opening file");
    return(-1);
  }
  
  line = returnLine(fp); //now you have a nice line, so play with it
  while(line != NULL){
    //printLine(line);
    newString = makeString(line);
    //printString(newString);
    scHead = insertStringIntoLinkedList(scHead, newString);
    line = returnLine(fp);//now you have a nice line, so play with it
  }
  fclose(fp);
  //displayStringList(scHead);

  scTemp = scHead;
  while (scTemp != NULL) {

    char *text = scTemp->str->stng;
    int i=0, curr=0;
    while (*(text+i)!='\0') {
        if (*(text+i)==' ') {
            *(text+i)='\0';
            word = createWord(text+curr);
            curr=i+1;
            wdHead = insertWordIntoLinkedList(wdHead, word, lineNum); 
        }
        i++;
    }
    word = createWord(text+curr);       
    curr=i+1;
    wdHead = insertWordIntoLinkedList(wdHead, word, lineNum); 
    
    scTemp=scTemp->next;
    lineNum++;
  }

  displayWordList(wdHead);

  mostFrequent = findMostFrequentWord(wdHead);
  puts("Most Frequent Word:");
  printWord(mostFrequent);

  return 0;
}