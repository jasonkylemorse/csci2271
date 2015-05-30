// file: assignment2bc-JasonMorse.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: February 13, 2015


// PART B & PART C

#include <stdio.h>
#include <stdlib.h>

// Declare functions, states, and booleans
void getString(char **m);
void printString(char *g);
char * findMatch(char *j, char *k);
void printIt(char *i);
int getIndex(char *a, char *b);
enum StateType {START, G, GC, GCA};
enum Boolean {true, false};

// Main function
int main(int argc, char *argv[]){
  char *line;
  char *address;
  char pattern[] = "GCAG";
  getString(&line);
  address = findMatch(line, pattern);
  printIt(address);
  if (address != NULL)
    getIndex(line, address);
}

// Reads in characters 1 at a time 
void getString(char **m) //note use of **m
{
  int a = 0; 
  char *k; // declare k as address of a char
  char c; // declare c as a char

  k =(char *)malloc(sizeof(char)); // allocate space at k for 1 char
  printf("Enter a series of characters and then press <return>: \n");
  printf("input    : ");
  while (1)  // infinite loop, very dangerous; 
    {
      c = getchar(); // take char from user input and put in c
      if (c == '\n') // if c is 'enter', break 
        break;
      *(k + a) = c; // else, put c at address of k + a
      a++; // increment a
      k = realloc(k,a+1); // reallocate by adding space for one more char
   }
  *(k + a) = '\0'; // once the while loop is broken ('enter' is pressed), set the last character to '\0'
  *m = k;
}

// FSM Logic
char * findMatch(char *j, char *k) {
  int x = 0;
  int y = 0;
  char *input;
  char *sequence;
  char *returnaddress;
  returnaddress = NULL;
  input = j;
  sequence = k;
  enum StateType state = START;
  enum Boolean foundPattern;
  foundPattern = false;
  enum Boolean foundLastG;
  foundLastG = false;

  while (*(input + x) != '\0') {

    switch(state) {

      case START:
        //printf("\nReached state START\n");
        if (*(input + x) == 'G') {
          state = G;
          returnaddress = input + x;
        }

        else
          state = START;
        break;

      case G:
        //printf("\nReached state G\n");
        

        if (*(input + x) == 'C')
          state = GC;
        //else if (*(input + x) == 'G')
        //  state = G;
        else {
          state = G;
          y++;
        }
        break;

      case GC:
        //printf("\nReached state GC\n");
        if (*(input + x) == 'A')
          state = GCA;
        //else if (*(input + x) == 'G')
        //  state = G;
        else {
          state = GC;
          y++;
        }
        break;

      case GCA:
        //printf("\nReached state GCA\n");
        if (*(input + x) == 'G'){
          foundPattern = true;
          if (foundLastG == false) {
            printf("\n%d characters were skipped (after the first G was found)\n", y);
            if (y > 10)
              printf("This is an innaccurate match\n");
      }
          foundLastG = true;
        }
        else {
          state = GCA;
          y++;
        }
        break;
    }

    x++;

  }

  if (foundPattern == false) {
    returnaddress = NULL;
  }

  return returnaddress;
}

// Print everything from some address till you reach a '\0'
void printString(char *g) // takes in address of char
{
  int a=0;
  char *k;
  k = g;
	while (*(k+a) != '\0')
   {
     printf("%c",*(k+a));
     a++;
   }
   printf("\n");
}

// Print results of search
void printIt(char *i) {
  char *address;
  address = i;
  if (address != NULL) {
    printf("\nThe pattern GCAG was found! :-)\n");
    //printf("Remaining characters are: ");
    //printString(address + 3);
  }
  else
    printf("\nThe pattern GCAG was not found! :-(\n");
}

// Determines the position where the pattern begins
int getIndex(char *a, char *b) {
  int x;
  char *beginning;
  beginning = a;
  char *end;
  end = b;
  x = b-a;
  printf("\nThe pattern begins at index %d\n", x);

}