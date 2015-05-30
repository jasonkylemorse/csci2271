// file: temperatures_main.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: March 31, 2015

#include "linked_list.h"

#define MAX_SENSORS 25

list myList;
pthread_mutex_t lock; /* mutex ensuring exclusive access to buffer */
pthread_cond_t self; // conditional variable
int num_temp_sensors; // user input

// variables for randomness
int stime;
long ltime;

int endOfCycle;

// temperature structure that contains ID and seed for random number generation
typedef struct {
	int id;
	int seed;
}temperature_struct;

// function definitions 
void insertTemp(temperature_struct * info);
void printTempStruct(void *item);

// main
int main(int argc, char *argv[]) {

	//printf("Creating list...\n");
	myList = createList();
	temperature_struct * info;
	int n;
	endOfCycle = 0;

	// each sensor is a thread
	pthread_t sensors[MAX_SENSORS];

	if(argc != 2) {
		puts("Error: not enough arguments supplied.");
		exit(0);
	}

	// take user input
	num_temp_sensors = atoi(argv[1]);
	printf("# of sensors are: %d\n",num_temp_sensors);

	// initialize lock and conditional variable
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&self, NULL);

	// for each customer, malloc space for struct, assign values
	for (n = 0;n < num_temp_sensors;n++){ 
    	info = (temperature_struct *)malloc(sizeof(temperature_struct));
    	info->id = n;

    	ltime = time(NULL);
		stime = (unsigned) ltime/2;
    	info->seed = stime;

    	sleep(1);

    	// call to insertTemp
    	if (pthread_create(&(sensors[n]), NULL, (void *)insertTemp, info) != 0) {
    		
    		perror("pthread_create");
      		exit(1);
    	}
  	}

  	// join all threads
  	for (n = 0; n < num_temp_sensors; n++){
  		pthread_join(sensors[n],NULL);
  	}

  	//puts("traversing...");
  	//forwardTraversal(myList, printInt);
	return 0;
}

void insertTemp(temperature_struct * info) {
	int x = 0;
	int y;
	temperature_struct * z;
	node_t * traverseList;
	traverseList = myList->firstNode;
	temperature_struct * myTempStruct;
	//sleep(1);
	//puts("got to insertTemp");
	//puts("\n--------------------------------------------------------\n")

	srand(info->seed);	

	// ensure 10 cycles
	while (x < 10) {
		// generate random temperature using seed and put in new struct
		y = (rand() % 200) - 100;
		z = (temperature_struct *)malloc(sizeof(temperature_struct));
		z->id = info->id;
		z->seed = y;

		// lock, insert new struct, increment endOfCycle, wait, broadcast, unlock
		printf("Sensor #%d is trying to insert a temperature of %d into the list...\n", info->id, y);
		pthread_mutex_lock(&lock);
		insertNodeEnd(myList, z);

		endOfCycle++;

		// wait until each thread gets a chance to execute per cycle
		while (endOfCycle < ((x+1)*num_temp_sensors)) {
			//printf("sensor %d is waiting\n", info->id);
			pthread_cond_wait(&self, &lock);
		}

		pthread_cond_broadcast(&self);
		traverseList = myList->firstNode;
		float average = 0;
		int counter = 0;
		while (traverseList != NULL) {

			myTempStruct = (temperature_struct *) traverseList->item;
			//printf("\nSeed: %d\n", myTempStruct->seed);
			average = average + myTempStruct->seed;
			counter++;
			traverseList = traverseList->next;
		}
		forwardTraversal(myList, printTempStruct);
		average = average/counter;
		printf("\nAverage: %f\n\n", average);
		myList = createList();
		pthread_mutex_unlock(&lock);
		
		sleep(1);
		
		x++;
	}

	myList = NULL;

	pthread_exit(NULL);
}

// print temperature structure
void printTempStruct(void *item){
	temperature_struct *x = (temperature_struct *) item;
	printf("Sensor ID: %d\n", x->id);
	printf("Temperature: %d\n\n", x->seed);
}