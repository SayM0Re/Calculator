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
char choice, back, input[50], output[50];  // choice - for select operation, back - for program reuse, input/output - for file name
float num1, num2;                          // num1 - first number, num2 - second number
float *a,*b;                               // alley A and B for operation with vectors
int size;                                  // size - size of vectors

int main(void)  // beginning of program
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf("Welcome, %%user%% ! \n");  //  welcome text for any user

	do
	{
	printf("Enter the input \"name.txt\" - ");
	scanf(" %s", &input);
	printf("Enter the output \(you can reselect the output file\) \"name.txt\" - ");
	scanf(" %s", &output);

    FILE *in,*out;
    in = fopen(input,"r");
    out = fopen(output,"w");
		while(feof(in) == 0)
		{

			fprintf(out, "What do you want to work with? (v - vectors, n - numbers)\n ");  //  offer to choose between two types
			fscanf(in, " %c",&choice);
			fprintf(out, "Selected: %c \n",choice);
			switch(choice)
			{
			case'v':  // a case of operations with vectors
				fprintf(out, "Select operation \(+(addition) -(subtraction) *(multiplication) \n");
				fscanf(in, " %c",&choice);
				fprintf(out, "Selected: %c \n",choice);
				switch(choice)
				{
				case'+':  //  an addition case
					fprintf(out, "Enter the size of vectors - ");
					fscanf(in, " %i", &size);
					fprintf(out, "%i \n",size);
					a = malloc(size*sizeof(int));
					b = malloc(size*sizeof(int));
					fprintf(out, "Enter the first vector  - ");
						for (int i=0;i<size;i++)
							{
							fscanf(in, " %f",&a[i]);
							}
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f ",a[i]);  //  a print of addition result
							}
					fprintf(out, " \n");
					fprintf(out, "Enter the second vector - ");
						for (int i=0;i<size;i++)
							{
							fscanf(in, " %f",&b[i]);
							}
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f ",b[i]);  //  a print of addition result
							}
					fprintf(out, " \n");
					fprintf(out, "Result: \n");
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f + %.3f = %.3f \n",a[i],b[i],a[i]+b[i]);  //  a print of addition result
							}
					fprintf(out, " \n");
					free(a);
					free(b);
					break;
				case'-':  //	a subtraction case
					fprintf(out, "Enter the size of vectors - ");
					fscanf(in, " %i", &size);
					fprintf(out, "%i \n",size);
					a = malloc(size*sizeof(int));
					b = malloc(size*sizeof(int));
					fprintf(out, "Enter the first vector  - ");
						for (int i=0;i<size;i++)
							{
							fscanf(in, " %f",&a[i]);
							}
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f ",a[i]);  //  a print of addition result
							}
					fprintf(out, " \n");
					fprintf(out, "Enter the second vector - ");
						for (int i=0;i<size;i++)
							{
							fscanf(in, " %f",&b[i]);
							}
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f ",b[i]);  //  a print of addition result
							}
					fprintf(out, " \n");
					fprintf(out, "Result: \n");
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f - %.3f = %.3f \n",a[i],b[i],a[i]-b[i]);  //  a print of addition result
							}
					fprintf(out, " \n");
					free(a);
					free(b);
					break;
				case'*':    //	a multiplication case
					fprintf(out, "Enter the size of vectors - ");
					fscanf(in, " %i", &size);
					fprintf(out, "%i \n",size);
					a = malloc(size*sizeof(int));
					b = malloc(size*sizeof(int));
					fprintf(out, "Enter the first vector  - ");
						for (int i=0;i<size;i++)
							{
							fscanf(in, " %f",&a[i]);
							}
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f ",a[i]);  //  a print of addition result
							}
					fprintf(out, " \n");
					fprintf(out, "Enter the second vector - ");
						for (int i=0;i<size;i++)
							{
							fscanf(in, " %f",&b[i]);
							}
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f ",b[i]);  //  a print of addition result
							}
					fprintf(out, " \n");
					fprintf(out, "Result: \n");
						for (int i=0;i<size;i++)
							{
							fprintf(out, "%.3f * %.3f = %.3f \n",a[i],b[i],a[i]*b[i]);  //  a print of addition result
							}
					fprintf(out, "\n");
					free(a);
					free(b);
					break;
				}
				break;
			case'n':  // a case of operation with numbers
			//  operation selection "menu"
			fprintf(out, "Select operation \(+(addition) -(subtraction) /(division) *(multiplication) ^(exponentiation) !(factorial)) \n ");
			fscanf(in, " %c",&choice);
			fprintf(out, "Selected: %c \n",choice);
				switch(choice)  //  operation fetch block
				{
				case '+':  //  an addition case
					fprintf(out, "Enter the first number - ");
					fscanf(in, " %f",&num1);
					fprintf(out, "%f \n",num1);
					fprintf(out, "Enter the second number - ");
					fscanf(in, " %f",&num2);
					fprintf(out, "%f \n",num2);
					fprintf(out, "Result: %f + %f = %f\n",num1,num2,num1+num2);  //  a print of addition result
					break;
				case '-':  //	a subtraction case
					fprintf(out, "Enter the first number - ");
					fscanf(in, " %f",&num1);
					fprintf(out, "%f \n",num1);
					fprintf(out, "Enter the second number - ");
					fscanf(in, " %f",&num2);
					fprintf(out, "%f \n",num2);
					fprintf(out, "Result: %f - %f = %f\n",num1,num2,num1-num2);  //  a print of subtraction result
					break;
				case '*':  //	a multiplication case
					fprintf(out, "Enter the first number - ");
					fscanf(in, " %f",&num1);
					fprintf(out, "%f \n",num1);
					fprintf(out, "Enter the second number - ");
					fscanf(in, " %f",&num2);
					fprintf(out, "%f \n",num2);
					fprintf(out, "Result: %f * %f = %f\n",num1,num2,num1*num2);  //  a print of multiplication result
					break;
				case '/':  //	a division case
					fprintf(out, "Enter the first number - ");
					fscanf(in, " %f",&num1);
					fprintf(out, "%f \n",num1);
					fprintf(out, "Enter the second number - ");
					fscanf(in, " %f",&num2);
					fprintf(out, "%f \n",num2);
					fprintf(out, "Result: %f / %f = %f\n",num1,num2,num1/num2);  //  a print of division result
					break;
				case '^':  //  an exponentiation case
					fprintf(out, "Enter the first number - ");
					fscanf(in, " %f",&num1);
					fprintf(out, "%f \n",num1);
					fprintf(out, "Enter the second number(integer) - ");
					fscanf(in, " %f",&num2);
					fprintf(out, "%f \n",num2);
					if (num2 - (int)num2 == 0)  //  a non-float number check
					{
						if ((int)num2 > 0)  //  a positive number check
						{
							float st = 1;  //  st - 'степень'
							for (int i=1;i<num2+1;i++)  //  beginning cycle of exponentiation
							{
								st=st*num1;  //  the exponentiation process
							}
							fprintf(out, "Result: %f ^ %f = %f \n",num1,num2,st);  //  a print of exponentiation result
						}
						else if((int)num2 < 0)  //  a negative number check
						{
							float x = 1/num1;           //  flip the number due to the negative exponent
							num2 = -num2;               //  replacing negative with positive
							float st = 1;               //  st - 'степень'
							for (int i=1;i<num2+1;i++)  //  beginning cycle of exponentiation
							{
								st=st*x;                //  the exponentiation process
							}
							fprintf(out, "Result: %f ^ %f = %f \n",num1,num2,st);  //  a print of exponentiation result
						}
						else
						{
							fprintf(out, "Result: %f ^ %f = 1.000000 \n",num1,num2);
						}
					}
					else  //  a report about incorrect type of number
					{
						fprintf(out, "Try again :( (Enter an integer in \"second number\") \n");
					}
					break;
				case '!':  //  factorial case
					fprintf(out, "Enter the number(integer) - ");
					fscanf(in, " %f",&num1);
					fprintf(out, "%f \n",num1);
					if (num1 - (int)num1 == 0)  //  a non-float number check
					{
						if (num1 > 0)  //  a positive number check
						{
							long long int r = 1;        //  the beginning of the cycle of multiplying...
							for (int i=1;i<num1+1;i++)  //...the number by the previous one for the factorial
							{
								r = r*i;
							}
							fprintf(out, "Result: %f\! = %lli \n" ,num1 ,r);  //  a print of factorial result
						}
						else  //  a report about 'number <=0'
						{
							fprintf(out, "Try again :( (Enter an integer more than 0) \n");
						}
					}
					else  //  a report about incorrect type of number
					{
						fprintf(out, "Try again :( (Enter an integer) \n");
					}
					break;
				default:  //  a report that this operation does not exist
					fprintf(out, "Unknown operation or you pressed the wrong button. Try again :) \n");
					break;
				}
				break;
			default:  //  a report about incorrect input among the possible 'n' and 'v'
				fprintf(out, "Maybe you pressed the wrong button. Try again :) \n ");
				break;
			}
			fprintf(out, " \n");  //  add an empty line if you need to perform another operation...
								//  ...and output it to the file that was used earlier
		}
        fclose(in);          //  closing input file
        fclose(out);         //  closing output file

		//  feedback
		printf("Start over? (y/n) \n");
		scanf(" %c",&back);

	}
	while(back == 'y');  //  waiting 'y' from %user%
	if (back == 'n')     //  waiting 'n' from %user%
	{
		printf("Have a nice day! <3 \n");
	}
	else  //  a little joke for those who like to press the wrong buttons
	{
		printf("You entered a WRONG key - system will detonate!\n"
				".......******.......\n"
				".....***BOOM***.....\n"
				".......******.......\n");
	}
	return 0;  //  ending of program
}
