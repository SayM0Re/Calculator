#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

float numberFunctionStack(char operation, float number1, float number2){
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
