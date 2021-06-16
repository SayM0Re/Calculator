#include <stdio.h>

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct localInQueue {											//  structure for data inside the program
    char operation,choice;												//  operation - for select operation, choice - for select numbers/vectors
    int size;															//  size - for select size of vectors
    double *firstNum,*secondNum;										//  firstNum - first number, secondNum - second number :/
    char fill;															//  fill - for fill local queue
} localInQueue;

typedef struct inQueue {                                                //  structure for writing data from a file
    char operation,choice;
    int size;
    double *firstNum,*secondNum;
    char fill;
    struct inQueue *next;
} inQueue;

typedef struct outQueue {                                                //  structure for outputting data to a output file
    char *result;
    struct outQueue *next;
} outQueue;

typedef struct linksOfQueues {                                           //  structure with queue pointers for more convenience
	inQueue *headIn, *tailIn;
	outQueue *headOut, *tailOut;
} linksOfQueues;

void fillLocalInQueue(localInQueue *current, FILE *fileIn);              //  fill local queue
void pushInQueue(localInQueue localQueue, linksOfQueues *link);          //  add a queue with input data
void pushOutQueue(char *line, linksOfQueues *link);                      //  add a queue with output data
void popInQueue(linksOfQueues *link);                                    //  remove a queue with input data
char *popOutQueue(linksOfQueues *link);                                  //  remove a queue with output data
void deleteInQueue(linksOfQueues *link);                                 //  delete a queue with input data
void deleteOutQueue(linksOfQueues *link);                                //  delete a queue with output data
void queueIntoFile(FILE *fileOut, linksOfQueues *link);                  //  output the result to a output file

#endif
