// file: assignment3main-jasonmorse.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: February 27, 2015

// PART A

#include <stdio.h>
#include "assignment3-jasonmorse.h"

void getString(char **m);
int findMatch(String *input, String *pattern);
enum StateType {IN, OUT};


int main(int argc, char *argv[]){

	char *inputString;
	char *patternString;
	int result;

	printf("Enter a series of characters and then press <return>: \n");

	printf("input   :          ");
	getString(&inputString);
	String *input = makeString(inputString);

	printf("pattern :          ");
	getString(&patternString);
	String *pattern = makeString(patternString);

	result = findMatch(input, pattern);

	if (result == 1) {
		printf("\nA match was found :-)\n\n");
	} else {
		printf("\nNo match found :-(\n\n");
	}

}

int findMatch(String *input, String *pattern) {

	int x = 0; // index for input
	int y = 0; // index for pattern
	int start;
	enum StateType state = OUT;

	while (*(input->stng + x) != '\0') {

		switch(state) {

			case OUT:
				
				if (*(input->stng + x) != *(pattern->stng + y)) {
					state = OUT;
					x++;
					if (*(input->stng + x) == '\0') {
						return 0;
					}
				} else {
					state = IN;
					x++;
					y++;
					start = x;
					if (*(pattern->stng + y) == '\0') {
						return 1;
					}
					
				}
				break;

			case IN:
				
				if (*(input->stng + x) != *(pattern->stng + y)) {
					state = OUT;
					x = start;
					y = 0;
				} else {
					state = IN;
					x++;
					y++;
					if (*(pattern->stng + y) == '\0') {
						return 1;
					}
				}
				break;
		}

	}

	return 0;

}

void getString(char **m) //note use of **m
{
	int a = 0; 
	char *k; // declare k as address of a char
	char c; // declare c as a char

	k =(char *)malloc(sizeof(char)); // allocate space at k for 1 char
	//printf("Enter a series of characters and then press <return>: \n");
	//printf("input    : ");
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