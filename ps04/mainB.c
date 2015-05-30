// file: mainB.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: March 18, 2015

#include "stock.h"
#include "partA.h"

int menu();

int main(int argc, char *argv[]) {

	FILE *fp;
	char *line;
	char *symbol;
	char *closing;
	float closingNew;
	char *opening;
	float openingNew;
	char *number;
	int numberNew;

	int numeric;
	int choice = -1;
	int noneFound = 0;
	int noneFound2 = 0; 

	float desiredPrice;
	float desiredChange;

	list listOfStocks = createList();

	fp = fopen("stocks.txt" , "r");
  	if(fp == NULL) {
    	perror("Error opening file");
    	return(-1);
    }

    line = returnLine(fp);

    // read in file to stock structs & insert structs in double linked list
    while (line != NULL) {
    	//printLine(line);

    	stock_t * newStock;

    	symbol = parseWord(&line);
    	closing = parseWord(&line);
    	closingNew = strtof(closing, NULL);
    	opening = parseWord(&line);
    	openingNew = strtof(opening, NULL);
    	number = parseWord(&line);
    	numberNew = atoll(number);

    	newStock = createStock(symbol, closingNew, openingNew, numberNew);
    	insertNodeEnd(listOfStocks, newStock);

    	line = returnLine(fp);

    }
    fclose(fp);

    //forwardTraversal(listOfStocks, printStock);

    // menu reaction
    choice = menu();
    while (choice != 4) {
    	switch(choice) {
    		case 1:
    			printf("Please enter the minimum closing price you are searching for: \n");
    			scanf("%f", &desiredPrice);

    			node_t *temp = listOfStocks->firstNode;
				printf("\nThe following stocks match your request: \n");
				while (temp != NULL) {
					stock_t *myStock = temp->item;
					if (myStock->getClosingPrice(myStock) > desiredPrice) {
						printStock(myStock);
						noneFound = 1;
					}
					temp = temp->next;
				}
				if (noneFound == 0) {
					printf("Sorry, no closing prices are greater than that value! :-(");
				}
				printf("\n");
				noneFound = 0;

    			break;
    		case 2:
    			printf("Please enter the minimum percent change you are searching for: \n");
    			scanf("%f", &desiredChange);

    			node_t *temp2 = listOfStocks->firstNode;
				printf("\nThe following stocks match your request: \n");
				while (temp2 != NULL) {
					stock_t *myStock2 = temp2->item;
					if (myStock2->getPercentChange(myStock2) > desiredChange) {
						printStock(myStock2);
						noneFound2 = 1;
					}
					temp2 = temp2->next;
				}
				if (noneFound2 == 0) {
					printf("Sorry, no percent changes are greater than that value! :-(");
				}
				printf("\n");
				noneFound2 = 0;

    			break;
    		case 3:
    			forwardTraversal(listOfStocks, printStock);
    			printf("END OF LIST\n");
    			break;
    		case 4:
    			printf("Goodbye!\n");
    			return 0;

    	}
    	choice = menu();
    }

    printf("Goodbye!\n");
    return 0;
}

// menu interface
int menu() {
	int a;
	char carriageReturn;
	puts("\n--------------------------------------------------------------");
	puts("Please choose from the following choices: ");
	puts("1. Search for stock with closing price > some amount");
	puts("2. Search for stock with percent change > some amount");
	puts("3. List all stocks using toString");
	puts("4. Quit and leave");
	puts("--------------------------------------------------------------");
	scanf("%d%c", &a, &carriageReturn);

	return a;
}