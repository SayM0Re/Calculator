#include <stdio.h>

#ifndef LIST_H_
#define LIST_H_

// some variables are moved to the top for comfortably work
struct listIn {
    char operation, back;
    int size;
    float *first, *second;
    struct listIn *next;
};

struct listOut {
    float *result;
    struct listOut *nextResult;
};

float* numberFunctionList(char operation, float *number1, float *number2);                      //  function for working with numbers
float* vectorFunction(char operation, int size, float *vector1, float *vector2);                //  function for working with vectors
float* pushNumber(FILE *fileIn, int size);                                                      //  adding numbers
void pushCurrent(struct listIn *current, FILE *fileIn);                                         //  adding current items to the `listIn`
void resultCurrent(struct listOut *currentResult, struct listIn *current);

#endif
