//Aman Hogan-Bailey MAV-ID: 1001830469 //

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITS 8

//creating function that converts decimal to binary//
void ConvertDecimalToBinary(int AnyN, char CBitArry[BITS])
{
	//intializing integer array and bitmask//
	int IBitArry[BITS] = {0};
	int Bitmask = 1;

	for(int i = 0; i < BITS; i++)
	{
		//determining if integer is odd, bitmasking//
		if(AnyN & Bitmask)
		{
			//if integer is odd, a 1 is placed into ineger array//
			IBitArry[i] = 1;
		}

		else
		{
			//if integer is even, a 0 is placeed into integer array//
			IBitArry[i] = 0;
		}

		//using "Divide in half, ignore remainder" method, also known as bitshifting//
		AnyN = AnyN >> 1;
	}

	//creating loop places charcater array values that correspond to integer array//
	for(int i = 0; i < BITS; i++)
	{
		//if integer array has a one, give charcater array a 1//
		if(IBitArry[i] == 1)
		{
			CBitArry[i] = 49;
		}
		
		//if integer array has a 0, character array has a 0//
		else
		{
			CBitArry[i] = 48;
		}
	}
}

int main()
{
	//initializing values and arrays//
	int FirstN, SecondN, ResultN;
	char BitOp[3];
	char BitArry[BITS] = {0};

	//printing blovked text to console//
	printf("Bitwise Calculator\n\n");
	printf("Enter two base 10 values with a bitwise operator to see the decimal result\n");
	printf("and the binary result. The format is\n\n");
	printf("FirstNumber BitwiseOperator SecondNumber\n\n");
	printf("For example, enter the expression\n\n");
	printf("2 & 3\n\n");
	printf("This calculator can used with &, |, ^, << and >>\n\n");
	printf("Please note that the spaces between numbers and operator is essential\n");
	printf("and the two entered values must be between 0 and 255\n\n");
	printf("Enter expression ");

	//scanning initial input and storing values//
	scanf("%d %s %d", &FirstN, &BitOp[0], &SecondN);

	//while input is not in rage, continue to ask user correct input//
	while((FirstN < 0 || FirstN > 255)||(SecondN < 0 || SecondN > 255))
	{
		scanf("%d %s %d", &FirstN, BitOp, &SecondN);
	}

	//if user did not enter an acceptable operator, send error message// 
	if(BitOp[0] == '&' || BitOp[0] == '|' || BitOp[0] == '^' || BitOp[0] == '>'|| BitOp[0] == '<')
	{
		//printing required text//
		printf("\nIn base 10...\n\n%d %s %d =", FirstN, BitOp, SecondN);

		//storing result of performed function using &//
		if(BitOp[0] == '&')
		{
			ResultN = FirstN & SecondN;
			printf(" %d", ResultN); 
		}

		//storing result of performed function using |//
		else if(BitOp[0] == '|')
		{
			ResultN = FirstN | SecondN;
			printf(" %d", ResultN); 
		}

		//storing result of performed function using >//
		else if(BitOp[0] == '>')
		{
			ResultN = (FirstN >> SecondN);
			printf(" %d", ResultN); 
		}

		//storing result of performed function using <//
		else if(BitOp[0] == '<')
		{
			ResultN = (FirstN << SecondN);
			printf(" %d", ResultN); 
		}

		//storing result of performed function using ^//
		else if(BitOp[0] == '^')
		{
			ResultN = FirstN ^ SecondN;
			printf(" %d", ResultN); 
		}

		//calling D to B function to convert first number//
		ConvertDecimalToBinary(FirstN, BitArry);

		//printing required text//
		printf("\n\n\nIn %d-bit base 2...\n", BITS);

		if(BitOp[0] != '<' && BitOp[0] != '>' && BITS == 8)
		{
			printf("\n   ");
		}

		else if (BitOp[0] != '<' && BitOp[0] != '>' && BITS == 16)
		{
			printf("\n");
		}

		else
		{
			printf("\n");
		}

		//printing first number Binary conversion//
		for(int i = BITS-1; i >=0; i--)
		{
			printf("%c", BitArry[i]);
		}

		//if operator is not > or <, then format the answer differently//
		if(BitOp[0] != '<' && BitOp[0] != '>')
		{
			if(BITS == 8)
			{
				//printing operator//
				printf("\n%s\n   ", BitOp);
			}
			else if (BITS == 16)
			{
				printf("\n%s\n", BitOp);
			}

			//calling D to B function to convert second number//
			ConvertDecimalToBinary(SecondN, BitArry);

			//printing second number binary conversion//
			for(int i = BITS-1; i >=0; i--)
			{
				printf("%c", BitArry[i]);
			}

		}
		//if operator is > or <, format the answer in this way//
		else
		{
			printf("  %s  %d", BitOp, SecondN);
		}

		//formatting correction//
		printf("\n");

		//if operator is &, |, or ^, print out "=" depending on the BITS of program//
		if(BitOp[0] == '&' || BitOp[0] == '|' || BitOp[0] == '^')
		{
			if(BITS != 16)
			{
				printf("   ");
			}

			for(int i = 0; i < BITS; i++)
			{
				printf("=");
			}
		}

		//calling D to B function to convert Result// 
		ConvertDecimalToBinary(ResultN, BitArry);

		//formatting correction//
		if(BitOp[0] != '<' && BitOp[0] != '>' && BITS != 16)
		{
			printf("\n   ");
		}

		else
		{
			printf("\n");
		}

		//printing Result number binary conversion//
		for(int i = BITS-1; i >= 0; i--)
		{
			printf("%c", BitArry[i]);
		}
		printf("\n\n");
	}

	else
	{
		printf("\n");
		printf("\nOperator \'%c\' is not supported by this calculator\n", BitOp[0]);
		printf("\n");
	}
	return 0;
}
