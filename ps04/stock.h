// file: stock.h
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: March 18, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct stock{
	char * stockSymbol;
	float closingSharePrice;
	float openingSharePrice; 
	int numberOfShares;

	float (* getClosingPrice)(void * S);
	float (* getOpeningPrice)(void * S);
	float (* getTotalDollarAmount)(void * S);
	float (* getPercentChange)(void * S);
	void (* toString)(void * S);
}stock_t;

// creates new stock struct
stock_t * createStock(char *name, float closingSharePrice, float openingSharePrice, int numberOfShares);

// return closing share price
float getClosingPrice(void * S);

// return opening share price
float getOpeningPrice(void * S);

// return total dollar amount
float getTotalDollarAmount(void * S);

// return percent change between closing and opening prices
float getPercentChange(void * S);

// print stock
void printStock(void *item);

// functions for reading in the file
int test_eol(char a);
int test_eof(char a);
char * returnLine(FILE *fp);  //returns line or NULL (if at end of file)
void printLine(char *line);
char * parseWord(char ** s);

