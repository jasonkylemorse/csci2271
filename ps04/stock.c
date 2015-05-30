// file: stock.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: March 18, 2015

#include "stock.h"

#define TRUE 1
#define FALSE 0

// creates new stock struct
stock_t * createStock(char *name, float closingSharePrice, float openingSharePrice, int numberOfShares) {
	stock_t *newStock = (stock_t*)malloc(sizeof(stock_t));
	
	newStock->stockSymbol = name;
	newStock->closingSharePrice = closingSharePrice;
	newStock->openingSharePrice = openingSharePrice;
	newStock->numberOfShares = numberOfShares;

	newStock->getClosingPrice = getClosingPrice;
	newStock->getOpeningPrice = getOpeningPrice;
	newStock->getTotalDollarAmount = getTotalDollarAmount;
	newStock->getPercentChange = getPercentChange;
	newStock->toString = printStock;
	return newStock;
}

// return closing share price
float getClosingPrice(void * S) {
	stock_t *x = (stock_t *) S;
	float price = x->closingSharePrice;
	return price;
}

// return opening share price
float getOpeningPrice(void * S) {
	stock_t *x = (stock_t *) S;
	float price = x->openingSharePrice;
	return price;
}

// return total dollar amount
float getTotalDollarAmount(void * S) {
	stock_t *x = (stock_t *) S;
	float closingPrice = x->getClosingPrice(x);
	int numShares = x->numberOfShares;
	float result = closingPrice * numShares;
	return result;
}

// return percent change between closing and opening prices
float getPercentChange(void * S) {
	stock_t *x = (stock_t *) S;
	float closingPrice = x->getClosingPrice(x);
	float openingPrice = x->getOpeningPrice(x);
	float result = ((closingPrice - openingPrice) / openingPrice)*100;
	return result;
}

// print stock
void printStock(void *item){
	stock_t *x = (stock_t *) item;
	printf("\nStock Name: %s\n", x->stockSymbol);
	printf("Closing Share Price: %f\n", x->closingSharePrice);
	printf("Opening Share Price: %f\n", x->openingSharePrice);
	printf("Number of Shares: %d\n", x->numberOfShares);
}

// functions for reading in the file
int test_eol(char a){
  if (a == '\n')
    return TRUE;
  else
    return FALSE;
}

int test_eof(char a){
  if (a == EOF)
    return TRUE;
  else
    return FALSE;
}

char * returnLine(FILE *fp){  //returns line or NULL (if at end of file)
  char c;
  char *line;
  int size=0;
  line = NULL;
  line = realloc(line,sizeof(char));
  c = fgetc(fp);  //read in first char of first line of the file
  if (test_eof(c))  //at end of the file
    return NULL;
  while (!test_eol(c)){//read the line
    *(line+size) = c;
    size++;
    line = realloc(line,sizeof(char)* (size+1));
    c = fgetc(fp);
  }
  *(line+size) = '\0';
  return line;
}

void printLine(char *line){
  int i=0;
  while (*(line+i) != '\0'){
    printf("%c",*(line+i)); //no end of line
    i++;
  }
  printf("\n");
}

char * parseWord(char ** s){
	int i=0,j=0;
	char * t,*w= NULL;
	t = *s;
	//printf("t: %s\n",t);
	if (*(t+i) == '\0'){
	  //puts("NULL");
	  return NULL;
	  }
	while (*(t+i) != ' ' && *(t+i) != '\0') {
		w = realloc(w,j+1);
		*(w+j) = *(t+i);
		i++;
		j++;
	}
	w = realloc(w,j+1);
	*(w+j) = '\0';
	*s = (t+i+1);
	//printf("s: %s\n",*s);
	return w;
}


