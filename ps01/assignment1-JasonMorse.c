// file: assignment1-JasonMorse.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: February 4, 2015
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Declare functions and states
int getLine(char *line);
void printLine(char *line, int size);
void switcharoo(char *line, int size, int start, int end);
int findComment(char *line, int size);
enum Statetype {START, SLASH, SLASHSTAR, SLASHSTARSTAR, SLASHSTARSTARSLASH, QUOTE};

// Main function
int main(){
	char m[80];
	char *a;
	int i, size = 0;
	int newSize;
	printf("Input : \t");
	size = getLine(m); // Sets size equal to the length of the input
	newSize = findComment(m, size);
	printf("Output : \t");
	printLine(m, newSize);
}

// Reads in the user input to certain address
int getLine(char *line){
	char *a,b;
	int i,size = 0;
	a = line;
	b = getchar();
	while( b != '\n' && size < 80)
    {
		*(a+size) = b;
		size++;
		b = getchar();
    }
	return size;
}

// Prints out chars at certain address
void printLine(char *line, int size){
	char *a;
	int i;
	a = line;
	for (i=0;i<size;i++)
		printf("%c",*(a+i));
	printf("\n");
}

// Function that removes comment and moves remaining chars back
void switcharoo(char *line, int size, int start, int end) {
	char *a;
	a = line;
	*(a + (start-1)) = ' ';
	while (end < size) {
		*(a + start) = *(a + end);
		start++;
		end++;
	}
}

// FSM logic
int findComment(char *line, int size) {
	int i = 0;
	int j, k, m;
	int newSize = size;
	char *a;
	enum Statetype state = START;
	a = line;

	while (i < newSize + 1) {
		switch (state) {
			case START:
				if (*(a + i) == '/')
					state = SLASH;
				else if (*(a + i) == '"')
					state = QUOTE;
				else
					state = START;
				break;

			case QUOTE:
				if (*(a + i) == '"')
					state = START;
				else if (i == size)
					newSize = size;
				else
					state = QUOTE;
				break;

			case SLASH:
				j = i;
				if (*(a + i) == '*')
					state = SLASHSTAR;
				else if (*(a + i) == '/')
					state = SLASH;
				else if (*(a + i) == '"')
					state = QUOTE;
				else
					state = START;
				break;

			case SLASHSTAR:
				if (*(a + i) == '*')
					state = SLASHSTARSTAR;
				else if (i == newSize) {
					newSize = j - 1;
					printf("\nError: unterminated comment\n");
				}
				else
					state = SLASHSTAR;
				break;

			case SLASHSTARSTAR:
				if (*(a + i) == '/')
					state = SLASHSTARSTARSLASH;
				else if (i == newSize) {
					newSize = j - 1;
					printf("\nError: unterminated comment\n");
				}
				else
					state = SLASHSTAR;
				break;

			case SLASHSTARSTARSLASH:
				m = j;
				k = i;
				switcharoo(a, size, j, k);
				newSize = newSize - (i - m);
				i = i - k;
				if (*(a + i) == '/')
					state = SLASH;
				else if (*(a + i) == '"')
					state = QUOTE;
				else
					state = START;
				break;
		}
		i++;
	}
	return newSize;
}
