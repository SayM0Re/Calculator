#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void fillLocalInQueue(localInQueue *current, FILE *fileIn){
    fscanf(fileIn, " %c", &current->choice);
    switch (current->choice){
        case 'v':
            fscanf(fileIn, "%d", &current->size);
            current->firstNum = malloc(current->size * sizeof(double));
            for (int i = 0; i < current->size; i++){
                fscanf(fileIn, "%lf", &current->firstNum[i]);
            }

            fscanf(fileIn, " %c", &current->operation);

            current->secondNum = malloc(current->size * sizeof(double));
            for (int i = 0; i < current->size; i++){
                fscanf(fileIn, "%lf", &current->secondNum[i]);
            }
            break;
        default:
            current->firstNum = malloc(sizeof(double));
            fscanf(fileIn, "%lf", current->firstNum);
            fscanf(fileIn, " %c", &current->operation);
            if (current->operation != '!'){
                current->secondNum = malloc(sizeof(double));
                fscanf(fileIn, "%lf", current->secondNum);
            }
    }
    fscanf(fileIn, " %c ", &current->fill);
}

void pushInQueue(localInQueue localQueue, linksOfQueues *link){
    if (link->headIn == NULL){
    	link->headIn = malloc(sizeof(inQueue));
    	link->tailIn = link->headIn;
    }
	else{
    	link->tailIn->next = malloc(sizeof(inQueue));
    	link->tailIn = link->tailIn->next;
    }
    link->tailIn->next = NULL;
    link->tailIn->choice = localQueue.choice;
    switch (link->tailIn->choice){
        case 'v':
        	link->tailIn->size = localQueue.size;
        	link->tailIn->firstNum = localQueue.firstNum;
        	link->tailIn->operation = localQueue.operation;
        	link->tailIn->secondNum = localQueue.secondNum;
            break;
        default:
        	link->tailIn->firstNum = localQueue.firstNum;
        	link->tailIn->operation = localQueue.operation;
            if (link->tailIn->operation != '!'){
            	link->tailIn->secondNum = localQueue.secondNum;
            }
    }
    link->tailIn->fill = localQueue.fill;
}

void pushOutQueue(char *line, linksOfQueues *link){
    if (link->headOut == NULL){
    	link->headOut = malloc(sizeof(outQueue));
        link->tailOut = link->headOut;
    }
	else{
    	link->tailOut->next = malloc(sizeof(outQueue));
    	link->tailOut = link->tailOut->next;
    }
    link->tailOut->next = NULL;
    link->tailOut->result = line;
}

void popInQueue(linksOfQueues *link){
    if (link->headIn == NULL){
        return;
    }
    if (link->headIn->next == NULL){
        free(link->headIn);
        link->headIn = NULL;
        link->tailIn = NULL;
        return;
    }
    inQueue *localVar = link->headIn;
    link->headIn = localVar->next;
    free(localVar);
}

char *popOutQueue(linksOfQueues *link){
    char *line;
    if (link->headOut == NULL){
        return NULL;
    }
    if (link->headOut->next == NULL){
        line = link->headOut->result;
        free(link->headOut);
        link->headOut = NULL;
        link->tailOut = NULL;
        return line;
    }
    outQueue *localVar = link->headOut;
    link->headOut = localVar->next;
    line = localVar->result;
    free(localVar);
    return line;
}

void deleteInQueue(linksOfQueues *link){
    while (link->headIn != NULL){
        popInQueue(link);
    }
}

void deleteOutQueue(linksOfQueues *link){
    while (link->headOut != NULL){
        popOutQueue(link);
    }
}

void queueIntoFile(FILE *fileOut, linksOfQueues *link){
    while (link->headOut != NULL){
        fprintf(fileOut, "%s\n", popOutQueue(link));
    }
}
