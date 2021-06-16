/*
 ############################################
 # Name: Calculator-prototype with <3       #
 # Made by: Roman Skvortsov                 #
 # Copyright: for free using                #
 # Powered by: IVT's group                  #
 ############################################
*/
// Example for work: "input.txt":                   2 1 + 7 * 2 - n
//                    2 1 + 7 * 2 - n               2 - entering first number
//                    3 6 + 4 - 4 * n               1 - entering second number
//                    4 6 * 15 - 24 + n             + - choosing operation between numbers (result - new first number)
//                                                  7 - entering new second number
//                                                  * - choosing new operation between new first and new second number (result - new new first number)
//                                                  e.t.c.
// 													n - separating the new expression with an empty line

#include <stdio.h>
#include <stdlib.h>
// some variables are moved to the top for comfortably work
typedef struct element {
	float data;
	struct element *next;
} stack;
stack *headStack = NULL;

void pushElement(stack **head, float data);                                             //  add element in stack`s struct
float popElement(stack **head);                                                         //  remove element from stack`s struct
float numberFunction(char operation, float number1, float number2);                     //  function for working with numbers

int main(int argc, char *argv[]){
	char again, lineExpression[255], line = '0';
	char input[255], output[255];
	int i = 0;
	float localNum, number1, number2;
	FILE *fileIn, *fileOut;
	do{
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
		fileOut = fopen(output, "a");  //  opening output file
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
				pushElement(&headStack, numberFunction(lineExpression[i], number1, number2));
				fprintf(fileOut, "%.3f %c %.3f = %.3f \n", number1, lineExpression[i], number2, numberFunction(lineExpression[i], number1, number2));
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

float numberFunction(char operation, float number1, float number2){
    float r = 1, st = 1, resultNumber;
    switch (operation){  //  operation fetch block
        case '+':  //  an addition case
            resultNumber = number1 + number2;
            return resultNumber;  //  a result of addition
        case '-':  //	a subtraction case
            resultNumber = number1 - number2;
            return resultNumber;  //  a result of subtraction
        case '*':  //	a multiplication case
            resultNumber = number1 * number2;
            return resultNumber;  //  a result of multiplication
        case '/':  //	a division case
            if (number2 != 0){
                resultNumber = number1 / number2;
                return resultNumber;  //  a result of division
            }
            else{
                return 0;
            }
        case '!':  //  factorial case
            for (int i=1; i <= number1; i++){
                r = r*i;
            }
            resultNumber = r;
            return resultNumber;  //  a result of factorial
        case '^':  //  an exponentiation case
            for (int i=1; i <= number2; i++){
                st = st*number1;
            }
            resultNumber = st;
            return resultNumber;  //  a result of exponentiation
    }
    return number1;  //  results of first...
    return number2;  //  ...and second numbers
}

void pushElement(stack **head, float data){
	stack *pushLocal = malloc(sizeof(stack));
	pushLocal->next = *head;
	pushLocal->data = data;
	*head = pushLocal;
}

float popElement(stack **head){
	stack *popLocal;
	float data;
	popLocal = *head;
	*head = (*head)->next;
	data = popLocal->data;
	return data;
}
