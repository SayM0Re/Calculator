/*
 ############################################
 # Name: Calculator-prototype with <3       #
 # Made by: Roman Skvortsov                 #
 # Copyright: for free using                #
 # Powered by: IVT's group                  #
 ############################################
*/
// Example for work: "input.txt": v * 2 1.2 2.1 2.3 3.2
//                                v - choosing work with vectors
//                                * - choosing operation
//                                2 - choosing size of vectors
//                                1.2 - entering first vector 1/2
//                                2.1 - entering first vector 2/2
//                                2.3 - entering second vector 1/2
//                                3.2 -  entering second vector 2/2
#include <stdio.h>
#include <stdlib.h>
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
// function for working with numbers
float* numberFunction(char operation, float *number1, float *number2){
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
        localResult->result = numberFunction(current->operation, current->first, current->second);
    }
    localResult->nextResult = NULL;
    currentResult->nextResult = localResult;
}

int main(int argc, char *argv[]){
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    char in[30], out[30];
    printf("Welcome, %%user%% ! \n");
    FILE *fileIn, *fileOut;
    struct listIn *head, *current;
    struct listOut *headResult, *currentResult;
    do{
        printf("Enter the input \"name.txt\" - ");
        scanf("%s", in);
        fileIn = fopen(in,"r");  //  opening input file
        if (fileIn == NULL){
            printf("File is empty. Try again.\n");
            while (fileIn == NULL){
                printf("Enter the input \"name.txt\" - ");
                scanf(" %s", in);
                fileIn = fopen(in,"r");
            }
        }
        printf("Enter the output \(you can reselect the output file\) \"name.txt\" - ");
        scanf("%s", out);
        if (feof(fileIn) == 0){
            head = malloc(sizeof(struct listIn));
            fscanf(fileIn, " %c", &head->back);
            fscanf(fileIn, " %c", &head->operation);
            if (head->back == 'v'){
                fscanf(fileIn, " %i", &head->size);
            }
            else{
                head->size = 1;
            }
            if (head->operation != '!'){
                head->first = pushNumber(fileIn, head->size);
                head->second = pushNumber(fileIn, head->size);
            }
            else{
                head->first = pushNumber(fileIn, head->size);
                head->second = NULL;
            }
            current = head;
            while (feof(fileIn) == 0){
                pushCurrent(current, fileIn);
                current = current->next;
            }
            headResult = malloc(sizeof(struct listOut));
            current = head;
            if (current->back == 'v'){
                headResult->result = vectorFunction(current->operation, current->size, current->first, current->second);
            }
            else{
                headResult->result = numberFunction(current->operation, current->first, current->second);
            }
            headResult->nextResult = NULL;
            current = current->next;
            currentResult = headResult;
            while (current != NULL) {
                resultCurrent(currentResult, current);
                current = current->next;
                currentResult = currentResult->nextResult;
            }
            current = head;
            currentResult = headResult;
            fclose(fileIn);  //  closing input file

            fileOut = fopen(out, "a");  //  opening output file
            while (current != NULL){
                fprintf(fileOut,"What do you want to work with? (v - vectors, n - numbers) \n ");  //  offer to choose between two types
				fprintf(fileOut, "Selected: %c \n",current->back);
                if (current->back == 'v'){  // a case of operations with vectors
                    fprintf(fileOut,"Enter the size of vectors - ");
                    fprintf(fileOut,"%i \n",current->size);
                    fprintf(fileOut,"Enter the first vector  - ");
                    for(int i=0; i < current->size ;i++){
						fprintf(fileOut,"%.3f ",current->first[i]);
					}
                    fprintf(fileOut, " \n");
                    fprintf(fileOut,"Enter the second vector - ");
                    for(int i=0; i < current->size ;i++){
						fprintf(fileOut,"%.3f ",current->second[i]);
					}
                    fprintf(fileOut, " \n");
                    fprintf(fileOut,"Select operation (+(addition) -(subtraction) *(multiplication)) \n ");  //  operation selection "menu"
                    fprintf(fileOut,"Selected: %c \n",current->operation);
                    fprintf(fileOut, "Result: \n");
                    if (current->operation != '*') {
                        for (int i = 0; i < current->size; i++) {
                            fprintf(fileOut, "%.3f %c %.3f = %.3f \n", current->first[i], current->operation,current->second[i], currentResult->result[i]);
                        }
                    }
                    else {
                        fprintf(fileOut, "( ");
                        for (int i = 0; i < current->size; i++) {
                            fprintf(fileOut,"%.3f ",current->first[i]);
                        }
                        fprintf(fileOut, ")");
                        fprintf(fileOut, " * ");
                        fprintf(fileOut, "( ");
                        for(int i=0; i < current->size ;i++){
						    fprintf(fileOut,"%.3f ",current->second[i]);
					    }
                        fprintf(fileOut, ") ");
                        fprintf(fileOut, "=  %.3f \n", currentResult->result[0]);
                    }

					fprintf(fileOut, " \n");
                }
                else if (current->back == 'n'){    // a case of operation with numbers
                    fprintf(fileOut,"Select operation \(+(addition) -(subtraction) /(division) *(multiplication) ^(exponentiation) !(factorial)) \n ");
                    fprintf(fileOut,"Selected: %c \n",current->operation);
                    fprintf(fileOut, "%f %c %f = %f \n", current->first[0], current->operation,current->second[0], currentResult->result[0]);
                }
                current = current->next;
                currentResult = currentResult->nextResult;
                fprintf(fileOut, " \n");
            }

            fclose(fileOut);  //  closing output file
        }
		//  feedback
		printf("Start over? (y/n) \n");
		scanf(" %c",&current->back);
	}
	while(current->back == 'y');  //  waiting 'y' from %user%
	if (current->back == 'n'){     //  waiting 'n' from %user%
		printf("Have a nice day! <3 \n");
	}
	else{  //  a little joke for those who like to press the wrong buttons
		printf("You entered a WRONG key - system will detonate!\n"
				".......******.......\n"
				".....***BOOM***.....\n"
				".......******.......\n");
	}
	return 0;  //  ending of program
}
