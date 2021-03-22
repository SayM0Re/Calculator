/*
 ############################################
 # Name: Calculator-prototype with <3       #
 # Made by: Roman Skvortsov, for free using #
 # Powered by: IVT's group                  #
 ############################################
*/
#include <stdio.h>
#include <stdlib.h>
// some variables are moved to the top for comfortably work
char choice, back; //choice - for select operation, back - for program reuse
float num1, num2; //num1 - first number, num2 - second number

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf("Welcome, %%user%% ! \n");  //  welcome text for any user
	do
	{
		//  operation selection "menu"
		printf("Select operation \(+(addition) -(subtraction) /(division) *(multiplication) ^(exponentiation) !(factorial))\n ");
		scanf(" %c",&choice);
			switch(choice)  //  operation fetch block
			{
			case '+':  //  an addition case
				printf("Enter the first number - ");
				scanf(" %f",&num1);
				printf("Enter the second number - ");
				scanf(" %f",&num2);
				printf("%f\n",num1+num2);  //  a print of addition result
				break;
			case '-':  //	a subtraction case
				printf("Enter the first number - ");
				scanf(" %f",&num1);
				printf("Enter the second number - ");
				scanf(" %f",&num2);
				printf("%f\n",num1-num2);  //  a print of subtraction result
				break;
			case '*':  //	a multiplication case
				printf("Enter the first number - ");
				scanf(" %f",&num1);
				printf("Enter the second number - ");
				scanf(" %f",&num2);
				printf("%f\n",num1*num2);  //  a print of multiplication result
				break;
			case '/':  //	a division case
				printf("Enter the first number - ");
				scanf(" %f",&num1);
				printf("Enter the second number - ");
				scanf(" %f",&num2);
				printf("%f\n",num1/num2);  //  a print of division result
				break;
			case '^':  //  an exponentiation case
				printf("Enter the first number - ");
				scanf(" %f",&num1);
				printf("Enter the second number(integer) - ");
				scanf(" %f",&num2);
				if (num2 - (int)num2 == 0)  //  a non-float number check
				{
					if ((int)num2 > 0)  //  a positive number check
					{
						float st = 1;  //  st - 'степень'
						for (int i=1;i<num2+1;i++)  //  beginning cycle of exponentiation
						{
							st=st*num1;  //  the exponentiation process
						}
						printf("%f\n",st);  //  a print of exponentiation result
					}
					else if((int)num2 < 0) //  a negative number check
					{
						float x = 1/num1;  //  flip the number due to the negative exponent
						num2 = -num2;  //  replacing negative with positive
						float st = 1;  //  st - 'степень'
						for (int i=1;i<num2+1;i++)  //  beginning cycle of exponentiation
						{
							st=st*x;  //  the exponentiation process
						}
						printf("%f\n",st);  //  a print of exponentiation result
					}
					else
					{
						printf("1.000000\n");
					}
				}
				else  //  a report about incorrect type of number
				{
					printf("Try again :( (Enter an integer in \"second number\")\n");
				}
				break;
			case '!':  //  factorial case
				printf("Enter the number(integer) - ");
				scanf(" %f",&num1);
				if (num1 - (int)num1 == 0)  //  a non-float number check
				{
					if (num1 > 0)  //  a positive number check
					{
						long long int r = 1;        //  the beginning of the cycle of multiplying...
						for (int i=1;i<num1+1;i++)  //...the number by the previous one for the factorial
						{
							r = r*i;
						}
						printf("%lli\n",r);  //  a print of factorial result
					}
					else  //  a report about 'number <=0'
					{
						printf("Try again :( (Enter an integer more than 0)\n");
					}
				}
				else  //  a report about incorrect type of number
				{
					printf("Try again :( (Enter an integer)\n");
				}
				break;
			default:  //  a report that this operation does not exist
				printf("Unknown operation or you missed the button. Try again :)\n");
				break;
			}
		//  feedback
		printf("Start over? (y/n)\n");
		scanf(" %c",&back);
	}
	while(back == 'y');  //  waiting 'y' from %user%
	if (back == 'n')     //  waiting 'n' from %user%
	{
		printf("Have a nice day! <3\n");
	}
	else  //  a little joke for those who like to poke the wrong buttons
	{
		printf("You entered a WRONG key - system will detonate!\n"
				".......******.......\n"
				".....***BOOM***.....\n"
				".......******.......\n");
	}
	return 0;
}
