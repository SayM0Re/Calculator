/*
############################################
# Name: Calculator-prototype with <3       #
# Made by: Roman Skvortsov                 #
# Copyright: for free using                #
# Powered by: IVT's group                  #
############################################
*/
/*
Example for work: "input.txt": 						v 2 4 9 - 7 2 y
					n 2 + 3 y           			n/v - choosing work with numbers/vectors
					n 9 - 15 y						2   - choosing size of vectors
                    n 4 * 16 y						4   - entering first vector 1/2
                    n 100 / 11 y					9   - entering first vector 2/2
                    n 2 ^ 6 y 						-   - choosing operation
                    n 6 ! y 						7   - entering second vector 1/2
                    v 4 2 6 4 5 + 1 3 5 4 y			2   - entering second vector 2/2
                    v 2 4 9 - 7 2 y					y   - choosing work with next line
	  				v 3 1 2 3 * 6 5 4 n
*/
#include <stdio.h>
#include <stdlib.h>

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
linksOfQueues queue;

void fillLocalInQueue(localInQueue *current, FILE *fileIn);              //  fill local queue
void pushInQueue(localInQueue localQueue, linksOfQueues *link);          //  add a queue with input data
void pushOutQueue(char *line, linksOfQueues *link);                      //  add a queue with output data
void popInQueue(linksOfQueues *link);                                    //  remove a queue with input data
char *popOutQueue(linksOfQueues *link);                                  //  remove a queue with output data
void deleteInQueue(linksOfQueues *link);                                 //  delete a queue with input data
void deleteOutQueue(linksOfQueues *link);                                //  delete a queue with output data
void queueIntoFile(FILE *fileOut, linksOfQueues *link);                  //  output the result to a output file

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	queue.headIn = NULL;
	queue.tailIn = NULL;
	queue.headOut = NULL;
	queue.tailOut = NULL;

	FILE *fileIn, *fileOut;
	char input[255], output[255];                                        //  input/output - for file name
	char back, continueCalculate;										 //  back - for program reuse, continueCalculate - to work with more than one line
	printf("Welcome, %%user%% ! \n");  									 //  welcome text for any user
		do{
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
							unsigned long int fuct = queue.headIn->firstNum[0];             	    // Результат вычисления факториала
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
							else{// Если степень равна 0, то число в этой степени равно 1
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
					default:
						lineExpression = malloc(sizeof(char));
						sprintf(lineExpression,"Unknown operation or you pressed the wrong button. Try again :) \n"); // Если операция не известна, выведет эту строку
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
      		printf("Start over? (y/n) \n");					//  feedback
			scanf(" %c", &back);                  			//  expect from %%user%% "y" or "n"
		}
		while (back == 'y'); 					 			//  waiting 'y' from %user%
		if (back == 'n'){     								//  waiting 'n' from %user%
			printf("Have a nice day! <3 \n");
		}
		else{  												//  a little joke for those who like to press the wrong button
			printf("You entered a WRONG key - system will detonate!\n"
					".......******.......\n"
					".....***BOOM***.....\n"
					".......******.......\n");
		}
	return 0;
}

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
