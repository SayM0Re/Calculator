#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// function for working with numbers
float* numberFunctionList(char operation, float *number1, float *number2){
    float r = 1, st = 1, *resultNumber;
    resultNumber = malloc(sizeof(float));
    switch (operation){  //  operation fetch block
        case '+':  //  an addition case
            resultNumber[0] = number1[0] + number2[0];
            return resultNumber;  //  a result of addition
        case '-':  //	a subtraction case
            resultNumber[0] = number1[0] - number2[0];
            return resultNumber;  //  a result of subtraction
        case '*':  //	a multiplication case
            resultNumber[0] = number1[0] * number2[0];
            return resultNumber;  //  a result of multiplication
        case '/':  //	a division case
            if (number2 != 0){
                resultNumber[0] = number1[0] / number2[0];
                return resultNumber;  //  a result of division
            }
            else{
                return 0;
            }
        case '!':  //  factorial case
            for (int i=1; i <= number1[0]; i++){
                r = r*i;
            }
            resultNumber[0] = r;
            return resultNumber;  //  a result of factorial
        case '^':  //  an exponentiation case
            for (int i=1; i <= number2[0]; i++){
                st = st*number1[0];
            }
            resultNumber[0] = st;
            return resultNumber;  //  a result of exponentiation
    }
    return number1;  //  results of first...
    return number2;  //  ...and second numbers
    free(resultNumber);
    free(number1);
    free(number2);
}
// function for working with vectors
float* vectorFunction(char operation, int size, float *vector1, float *vector2){
    float *resultVector;
    switch (operation){  //  operation fetch block
        case '+':  //  an addition case
            resultVector = malloc(size * sizeof(float));
            for (int i=0; i < size; i++){
                resultVector[i] = vector1[i] + vector2[i];
            }
            return resultVector;  //  a result of addition
        case '-':  //	a subtraction case
            resultVector = malloc(size * sizeof(float));
            for (int i=0; i < size; i++){
                resultVector[i] = vector1[i] - vector2[i];
            }
            return resultVector;  //  a result of subtraction
        case '*':  //	a multiplication case
            resultVector = malloc(sizeof(float));
            resultVector[0] = 0;
            for (int i=0; i < size; i++){
                resultVector[0] = resultVector[0] + vector1[i] * vector2[i];
            }
            return resultVector;  //  a result of multiplication
    }
    return vector1;  //  results of first...
    return vector2;  //  ...and second vectors
    free(vector1);
    free(vector2);
    free(resultVector);
}
//  adding numbers
float* pushNumber(FILE *fileIn, int size){
    float *number;
    number = malloc(size * sizeof(float));
    for (int i=0; i < size; i++){
        fscanf(fileIn, "%f", &number[i]);
    }
    return number;
}

//  adding current items to the `listIn`
void pushCurrent(struct listIn *current, FILE *fileIn){
    struct listIn *currentElement = malloc(sizeof(struct listIn));
    fscanf(fileIn, " %c", &currentElement->back);
    fscanf(fileIn, " %c", &currentElement->operation);
    if (currentElement->back == 'v'){
        fscanf(fileIn, " %i", &currentElement->size);
    }
    else{
        currentElement->size = 1;
    }
    if (currentElement->operation != '!'){
        currentElement->first = pushNumber(fileIn, currentElement->size);
        currentElement->second = pushNumber(fileIn, currentElement->size);
    }
    else{
        currentElement->first = pushNumber(fileIn, currentElement->size);
        currentElement->second = NULL;
    }
    currentElement->next = NULL;
    current->next = currentElement;
}

void resultCurrent(struct listOut *currentResult, struct listIn *current){
    struct listOut *localResult = malloc(sizeof(struct listIn));
    if (current->back == 'v'){
        localResult->result = vectorFunction(current->operation, current->size, current->first, current->second);
    }
    else{
        localResult->result = numberFunctionList(current->operation, current->first, current->second);
    }
    localResult->nextResult = NULL;
    currentResult->nextResult = localResult;
}
