/*
 ############################################
 # Name: Calculator-prototype with <3       #
 # Made by: Roman Skvortsov                 #
 # Copyright: for free using                #
 # Powered by: IVT's group                  #
 ############################################
*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"
#include "list.h"

int main(int argc, char *argv[]){
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char again, module, continueCalculate, lineExpression[255], line = '0', input[255], output[255];
	int i = 0;
	float localNum, number1, number2;
	FILE *fileIn, *fileOut;
	linksOfQueues queue;
    queue.headIn = NULL;
	queue.tailIn = NULL;
	queue.headOut = NULL;
	queue.tailOut = NULL;
	stack *headStack = NULL;
	struct listIn *head, *current;
	struct listOut *headResult, *currentResult;

	printf("Welcome, %%user%% ! \n");
    do{
        printf("What do you want to work with?(l - list, q - queue, s - stack) ");
        scanf(" %c", &module);
        switch (module){
        case 'l':
            printf("Enter the input \"name.txt\" - ");
            scanf(" %s", input);
            fileIn = fopen(input,"r");  //  opening input file
            if (fileIn == NULL){
                printf("File is empty. Try again.\n");
                while (fileIn == NULL){
                    printf("Enter the input \"name.txt\" - ");
                    scanf(" %s", input);
                    fileIn = fopen(input,"r");
                }
            }
            printf("Enter the output \(you can reselect the output file\) \"name.txt\" - ");
            scanf(" %s", output);
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
                    headResult->result = numberFunctionList(current->operation, current->first, current->second);
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
                fileOut = fopen(output, "a");  //  opening output file
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
            break;
        case 'q':
            printf("Enter the input \"name.txt\" - ");
			scanf(" %s", input);
			fileIn = fopen(input, "r");
			while (fileIn == NULL || feof(fileIn)){                  	 // Проверяем целлосность данны
				if (feof(fileIn)){
					printf("The file is empty\n");
				}
				else{
					printf("Incorrect file name\n");
				}
				scanf(" %s", input);
				fileIn = fopen(input, "r");
			}
			while (!feof(fileIn)){										 //  fill the local queue
				localInQueue localQueue;
				fillLocalInQueue(&localQueue, fileIn);
				pushInQueue(localQueue, &queue);
			}
			fclose(fileIn);
			printf("Enter the output \"you can reselect the output file\" \"name.txt\" - ");
			scanf(" %s", output);
			fileOut = fopen(output, "a");
			do{
				char *lineExpression;									 //  represent the answer as a char array
				switch (queue.headIn->choice){
				case 'n': ; 	//  a case of operation with numbers
					double res;
					switch (queue.headIn->operation){ 		//  operation fetch block
					case '+':	//  an addition case
						res = queue.headIn->firstNum[0]+ queue.headIn->secondNum[0];
						lineExpression = malloc(((int) queue.headIn->firstNum[0]+(int)queue.headIn->secondNum[0]+(int) res + 3 * 7+ 2 * 3 + 1)* sizeof(char));  //  allocate memory for the future obtained expression
						sprintf(lineExpression, "%lf + %lf = %lf",queue.headIn->firstNum[0],queue.headIn->secondNum[0], res); //  a print of addition result
						break;
					case '-': 	//	a subtraction case
						res = queue.headIn->firstNum[0]- queue.headIn->secondNum[0];
						lineExpression = malloc(((int)queue.headIn->firstNum[0]+(int)queue.headIn->secondNum[0]+(int) res + 3 * 7+ 2 * 3 + 1)* sizeof(char));
						sprintf(lineExpression, "%lf - %lf = %lf",queue.headIn->firstNum[0],queue.headIn->secondNum[0], res); //  a print of subtraction result
						break;
					case '*': 	//	a multiplication case
						res = queue.headIn->firstNum[0] * queue.headIn->secondNum[0];
						lineExpression = malloc(((int)queue.headIn->firstNum[0]+(int)queue.headIn->secondNum[0]+(int) res + 3 * 7+ 2 * 3 + 1)* sizeof(char));
						sprintf(lineExpression, "%lf * %lf = %lf",queue.headIn->firstNum[0],queue.headIn->secondNum[0], res); //  a print of multiplication result
						break;
					case '/': 	//	a division case
						if (queue.headIn->secondNum[0] == 0){ //  a report that cannot be divided by zero
							lineExpression = malloc(sizeof(char));
							sprintf(lineExpression,"Cannot be divided by 0");
						}
						res = queue.headIn->firstNum[0] / queue.headIn->secondNum[0];
						lineExpression =malloc(((int)queue.headIn->firstNum[0]+ (int)queue.headIn->secondNum[0]+ (int) res + 3 * 7+ 2 * 3 + 1)* sizeof(char));
						sprintf(lineExpression, "%lf / %lf = %lf",queue.headIn->firstNum[0],queue.headIn->secondNum[0], res); //  a print of division result
						break;
					case '!': 	//  factorial case
						if ((queue.headIn->firstNum[0] - (int) queue.headIn->firstNum[0])== 0){		//  a non-float number check
							unsigned long int fuct = queue.headIn->firstNum[0];
							if ((int)queue.headIn->firstNum[0]> 0){      					 		//  a positive number check
								for (int i = 1;i<(int)queue.headIn->firstNum[0];i++){		 		//  the beginning of the cycle of multiplying...
									fuct = fuct * i; 										 		//...the number by the previous one for the factorial
								}
								lineExpression = malloc(((int)queue.headIn->firstNum[0] + (int)res+ 6)* sizeof(char));
								sprintf(lineExpression, "%i ! = %lu",(int) queue.headIn->firstNum[0],fuct);  //  a print of factorial result
							}
							else{	//  a report about 'number <=0'
								lineExpression = malloc(sizeof(char));
								sprintf(lineExpression,"Try again :( (Enter an integer more than 0) \n");
							}
						}
						else{ 	//  a report about incorrect type of number
							lineExpression = malloc(sizeof(char));
							sprintf(lineExpression, "Try again :( (Enter an integer) \n");
						}
						break;
					case '^': 	 //  an exponentiation case
						if ((queue.headIn->secondNum[0]- (int) queue.headIn->secondNum[0])== 0){  	//  a non-float number check
							res = queue.headIn->firstNum[0];
							if ((int)queue.headIn->secondNum[0]>0){  //  a positive number check
								for (int j = 0;j < (int)queue.headIn->secondNum[0] - 1; j++){
									res = res * queue.headIn->firstNum[0];  //  the exponentiation process
								}
								lineExpression = malloc((int)queue.headIn->firstNum[0] + (int)queue.headIn->secondNum[0] +(int)sizeof(char));
								sprintf(lineExpression, "%lf ^ %i = %lf",queue.headIn->firstNum[0],(int) queue.headIn->secondNum[0],res);  //  a print of exponentiation result
								}
							else if ((int) queue.headIn->secondNum[0]< 0){  //  a negative number check
								double c, d; 								//  add help variables
								res = 1 / queue.headIn->firstNum[0];
								c = 1 / queue.headIn->firstNum[0];  		//  flip the number due to the negative exponent
								d = -queue.headIn->secondNum[0];			//  replacing negative with positive
								for (int j = 0; j < (int) d - 1; j++){ 		//  beginning cycle of exponentiation
									res = res * c;							//  the exponentiation process
								}
								lineExpression = malloc(((int)queue.headIn->firstNum[0] + (int)queue.headIn->secondNum[0] + (int) res	+ 2 * 7 + 2 * 3 + 1) * sizeof(char));
								sprintf(lineExpression, "%lf ^ %i = %lf",queue.headIn->firstNum[0],(int) queue.headIn->secondNum[0],res);
							}
							else{  //  a zero number check
								lineExpression = malloc(((int)queue.headIn->firstNum[0] + (int)queue.headIn->secondNum[0] + 7 + 2 * 3 + 1)*sizeof(char));
								sprintf(lineExpression, "%lf ^ %i = 1",queue.headIn->firstNum[0],(int) queue.headIn->secondNum[0]); 	  //  a print of exponentiation result
							}
						}
						else{   //  a report about incorrect type of number
							lineExpression = malloc(sizeof(char));
							sprintf(lineExpression,"Try again :( (Enter an integer) \n");
							break;
						}
						break;
					default:  //  a report about unknown operation
						lineExpression = malloc(sizeof(char));
						sprintf(lineExpression,"Unknown operation or you pressed the wrong button. Try again :) \n");
					}
					break;
				case 'v': 		// a case of operations with vectors
					while (queue.headIn->size < 1){		//  a report that the size must be greater than or equal to 1
						lineExpression = malloc(sizeof(char));
						sprintf(lineExpression, "Try again :( (Enter an integer(size) more than 1) \n");
						break;
					}
					double *resultVector;	//  a new variable to count the result with vectors
					resultVector = malloc(queue.headIn->size*sizeof(double));
					int sizeLine = 1;
					switch (queue.headIn->operation){ 		//  operation fetch block
					case '+':		//  an addition case
						for (int i = 0;i < queue.headIn->size;i++){
							resultVector[i] = queue.headIn->firstNum[i] + queue.headIn->secondNum[i];
							sizeLine += (int)queue.headIn->firstNum[i] + (int)queue.headIn->secondNum[i] + (int)resultVector[i]+ 7 * 3;
						}
						sizeLine += (2 + (queue.headIn->size - 1) * 2) * 3 + 2 * 3 + 1;
						lineExpression = malloc(sizeLine * sizeof(char));
						sprintf(lineExpression, "(");
						for (int i = 0;i < queue.headIn->size;i++){
							sprintf(lineExpression, "%s%lf", lineExpression,queue.headIn->firstNum[i]);
							if (i < queue.headIn->size - 1){
								sprintf(lineExpression, "%s, ",lineExpression);
							}
							else{
								sprintf(lineExpression, "%s) ",lineExpression);
							}
						}
						sprintf(lineExpression, "%s+ (", lineExpression);
						for (int i = 0;i < queue.headIn->size;i++){
							sprintf(lineExpression, "%s%lf", lineExpression,queue.headIn->secondNum[i]);
							if (i < queue.headIn->size - 1){
								sprintf(lineExpression, "%s, ",lineExpression);
							}
							else{
								sprintf(lineExpression, "%s) ",lineExpression);
							}
						}
						sprintf(lineExpression, "%s= (", lineExpression);
						for (int i = 0; i < queue.headIn->size;i++){
							sprintf(lineExpression, "%s%lf", lineExpression,resultVector[i]);
							if (i < queue.headIn->size - 1) {
								sprintf(lineExpression, "%s, ",lineExpression);
							}
							else{
								sprintf(lineExpression, "%s)",lineExpression);
							}
						}
						break;
					case '-':		//	a subtraction case
						for (int i = 0;i < queue.headIn->size;i++){
							resultVector[i] = queue.headIn->firstNum[i] - queue.headIn->secondNum[i];
							sizeLine +=(int)queue.headIn->firstNum[i] + (int)queue.headIn->secondNum[i] + (int)resultVector[i]+ 7 * 3;
						}
						sizeLine += (2 + (queue.headIn->size - 1) * 2) * 3 + 2 * 3 + 1;
						lineExpression = malloc(sizeLine * sizeof(char));
						sprintf(lineExpression, "(");
						for (int i = 0;i < queue.headIn->size;i++){
							sprintf(lineExpression, "%s%lf", lineExpression,queue.headIn->firstNum[i]);
							if (i < queue.headIn->size - 1){
								sprintf(lineExpression, "%s, ",lineExpression);
							}
							else{
								sprintf(lineExpression, "%s) ",lineExpression);
							}
						}
						sprintf(lineExpression, "%s- (", lineExpression);
						for (int i = 0;i < queue.headIn->size;i++){
							sprintf(lineExpression, "%s%lf", lineExpression,queue.headIn->secondNum[i]);
							if (i< queue.headIn->size- 1) {
								sprintf(lineExpression, "%s, ",lineExpression);
							}
							else{
								sprintf(lineExpression, "%s) ",lineExpression);
							}
						}
						sprintf(lineExpression, "%s= (", lineExpression);
						for (int i = 0;i < queue.headIn->size;i++){
							sprintf(lineExpression, "%s%lf", lineExpression,resultVector[i]);
							if (i < queue.headIn->size - 1){
								sprintf(lineExpression, "%s, ",lineExpression);
							} else {
								sprintf(lineExpression, "%s)",lineExpression);
							}
						}
						break;
					case '*': ;		//	a multiplication case
						double resultVector = 0.0;
						for (int i = 0;i < queue.headIn->size;i++){
							resultVector += queue.headIn->firstNum[i]* queue.headIn->secondNum[i];
							sizeLine +=(int) queue.headIn->firstNum[i]+(int) queue.headIn->secondNum[i]+ 7 * 2;
						}
						sizeLine += (2 + (queue.headIn->size - 1) * 2) * 2 + 2 * 3 + 2 + (int) resultVector + 7;
						lineExpression = malloc(sizeLine * sizeof(char));
						sprintf(lineExpression, "((");
						for (int i = 0;i < queue.headIn->size;i++){
							sprintf(lineExpression, "%s%lf", lineExpression,queue.headIn->firstNum[i]);
							if (i < queue.headIn->size - 1) {
								sprintf(lineExpression, "%s, ",lineExpression);
							}
							else{
								sprintf(lineExpression, "%s) ",lineExpression);
							}
						}
						sprintf(lineExpression, "%s* (", lineExpression);
						for (int i = 0;i < queue.headIn->size;i++){
							sprintf(lineExpression, "%s%lf", lineExpression,queue.headIn->secondNum[i]);
							if (i < queue.headIn->size	- 1){
								sprintf(lineExpression, "%s, ",lineExpression);
							}
							else{
								sprintf(lineExpression, "%s)) ",lineExpression);
							}
						}
						sprintf(lineExpression, "%s= %lf", lineExpression,resultVector);
						break;
					default:	//  a report that this operation does not exist
						lineExpression = malloc(sizeof(char));
						sprintf(lineExpression,"Unknown operation or you pressed the wrong button. Try again :) \n");
					}
					break;
				default:	//  a report about incorrect input among the possible 'n' and 'v'
					lineExpression = malloc(sizeof(char));
					sprintf(lineExpression,"Maybe you pressed the wrong button. Try again :) \"n\" or \"v\"");
				}
				pushOutQueue(lineExpression, &queue);
				continueCalculate = queue.headIn->fill;
				popInQueue(&queue);
			}
			while (continueCalculate == 'y');
			deleteInQueue(&queue); 							//  freeing memory
			queueIntoFile(fileOut, &queue);					//  put the expression into the output file
			deleteOutQueue(&queue); 						//  freeing memory
			fprintf(fileOut, "\n");
			fclose(fileOut);								//  closing output file
            break;
        case 's':
            printf("Enter the input \"name.txt\" - ");
            scanf("%s", input);
            fileIn = fopen(input,"r");  //  opening input file
            if (fileIn == NULL){
                printf("File is empty. Try again.\n");
                while (fileIn == NULL){
                    printf("Enter the input \"name.txt\" - ");
                    scanf(" %s", input);
                    fileIn = fopen(input,"r");
                }
            }
		    printf("Enter the output \(you can reselect the output file\) \"name.txt\" - ");
		    scanf(" %s", output);
		    fileOut = fopen(output, "w");  //  opening output file
		    while (feof(fileIn) == 0){
			    fscanf(fileIn, "%c", &lineExpression[i]);
			    if (lineExpression[i] == ' '){
			    	if (line == '0'){
			    		localNum = strtof(lineExpression, NULL); //  split the expression into symbols
			    		pushElement(&headStack, localNum);
			    		i = 0;
			    	}
			    }
			    else if (lineExpression[i] == '*' || lineExpression[i] == '+' || lineExpression[i] == '-'	|| lineExpression[i] == '/' || lineExpression[i] == '^'){
			    	number1 = popElement(&headStack);
			    	number2 = popElement(&headStack);
			    	pushElement(&headStack, numberFunctionStack(lineExpression[i], number1, number2));
			    	fprintf(fileOut, "%.3f %c %.3f = %.3f \n", number1, lineExpression[i], number2, numberFunctionStack(lineExpression[i], number1, number2));
			    	line = '1';
			    }
			    else if (lineExpression[i] == 'n'){
			    	while (headStack != NULL){
			    		popElement(&headStack);
			    	}
			    	fprintf(fileOut, "\n");
			    }
			    else{
			    	line = '0';
			    	i = i + 1;
		    	}
		    }
		    fclose(fileIn);
		    fclose(fileOut);
            break;
        default:
            printf("You entered a WRONG key - system will detonate!\n"
				".......******.......\n"
				".....***BOOM***.....\n"
				".......******.......\n");
            break;
        }
        printf("Start over? (y/n) \n");
	    scanf(" %c", &again);
    }
    while (again == 'y');  //  waiting 'y' from %user%
	if (again == 'n'){     //  waiting 'n' from %user%
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
