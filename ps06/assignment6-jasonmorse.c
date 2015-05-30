// file: assignment6-jasonmorse.c
// author: Jason Morse
// class: Computer Systems T/TH 1:30 PM
// date: April 14, 2015

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int test_eol(char a);
int test_eof(char a);
char * returnLine(FILE *fp);
char * change_case(char *input);

// function for reading in the file
int test_eol(char a){
  if (a == '\n')
    return TRUE;
  else
    return FALSE;
}

// function for reading in the file
int test_eof(char a){
  if (a == EOF)
    return TRUE;
  else
    return FALSE;
}

// function for reading in the file
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

int main(int argc, char* argv[]) {
  int pipe_1[2];
  //int pipe_1_reverse[2];
  int pipe_2[2];
  //int pipe_2_reverse[2];
  int rc1;
  //int rc1_reverse;
  int rc2;
  //int rc2_reverse;
  int pid, pid2, status;

  FILE *fp;
  FILE *fpout;
  fpout = fopen("mobydicknew.txt", "wb");
  char *line;

  char read_buffer_1[80];
  char read_buffer_2[80];

  rc1 = pipe(pipe_1); // create first pipe
  if (rc1 == -1) {
    perror("pipe");
    exit(1);
  }

  rc2 = pipe(pipe_2); // create first pipe
  if (rc2 == -1) {
    perror("pipe");
    exit(1);
  }

  fp = fopen("mobydick.txt", "r"); // open the file
  if (fp == NULL) {
    perror("Error opening file");
    return(-1);
  }

  line = returnLine(fp);
  //printf("line: %s\n", line);
while(line != NULL) {
  pid = fork();
  if (pid != 0) { // in parent (Process 1)
    //printf("in process 1\n");
    //printf("writing '%s' to pipe 1\n", line);
    rc1 = write(pipe_1[1], line, strlen(line) + 1);
    if (rc1 == -1) {
      perror("Process1: write");
      close(pipe_1[1]);
      exit(1);
    }
    waitpid(pid, &status, 0);
    //printf("END AND EXIT\n");
    exit(1);
  } else { // in child (Process 2)
    //printf("in process 2\n");
    rc1 = read(pipe_1[0], read_buffer_1, sizeof(read_buffer_1));
    //printf("reading '%s' from pipe 1\n", read_buffer_1);
    //printf("converting case...\n");
    int j = strlen(read_buffer_1);
    int i;
    //printf("String Length = %d\n", j);
    for (i = 0; i < j; i++) {
      int y = islower(read_buffer_1[i]);
      int z = isupper(read_buffer_1[i]);
      //printf("islower = %d\n", y);
      //printf("isupper = %d\n", z);
      if ((y != 0) && (z == 0)) {
        read_buffer_1[i] = toupper(read_buffer_1[i]);
      }
      else if ((y == 0) && (z != 0)) {
        read_buffer_1[i] = tolower(read_buffer_1[i]);
      }
    }
    //read_buffer_1[0] = tolower(read_buffer_1[0]);
    //printf("new content: %s\n", read_buffer_1);
    rc2 = write(pipe_2[1], read_buffer_1, sizeof(read_buffer_1));
    pid2 = fork();
    if (pid2 != 0) { // in parent (Process 2)
      //printf("still in process 2, waiting for process 3 to complete...\n");
      waitpid(pid2, &status, 0);
    } else { // in child (Process 3)
      //printf("in process 3\n");
      //printf("writing string to file...\n\n");
      rc2 = read(pipe_2[0], read_buffer_2, sizeof(read_buffer_2));
      //printf("writing %s...\n", read_buffer_2);
      strcat(read_buffer_2, "\n");
      fputs(read_buffer_2, fpout);
      //printf("-----------------------------\n");
      exit(0);
    }
  }
  line = returnLine(fp);
}

  //printf("back into parent\n");
  //exit(0);
  return 0;
}