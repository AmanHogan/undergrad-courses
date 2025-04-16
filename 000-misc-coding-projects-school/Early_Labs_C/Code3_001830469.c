//Aman Hogan-Bailey MAV-ID: 1001830469//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void PrintCard(int Bingo[5][5]);
void FillCard(int Bingo[5][5]);
int PickNumber(char newLetter, int newNumber, int EveryVal[75], int AmountofNumbers);
bool NumberExist(int Bingo[5][5], int newNumber);
bool CompleteR(int Bingo[5][5]);
bool CompleteC(int Bingo[5][5]);

int main(void)
{
	//seeding the random number generator//
	srand(time(0));

	//creating Bingo array and array to store all values//
	int Bingo[5][5] = {0};
	int EveryVal[75] = {0};
	char answer[2];

	//setting bool values automatically to zero//
	bool CompletedRow = true;
	bool CompletedColumn = true;

	//creating variables to store randomized chacracters and numbers//
	int newNumber = 0;
	char newLetter = 'B';

	//creating varibele to count number of times a card has been drawn//
	int NumberofTimes = 0;
	int AmountofNumbers = 0;

	//bool value that stores whether function is true or false//
	bool FairGame = false;

	//calling funtion to fill the Bingo Card//
	FillCard(Bingo);

	//calling function to print the Bingo Card//
	PrintCard(Bingo);

	//until game is finished, program continues//
	bool gameOngoing = true;
	
	while (gameOngoing)
	{
		//calling function that finds a random number out of 75, that has not been used//
		//This function also prints "The next number is XXX" and returns the value//
		newNumber = PickNumber(newLetter , newNumber, EveryVal, AmountofNumbers);
		NumberofTimes++;
		AmountofNumbers++;

		//gettong user input//
		printf("\n\nDo you have it? (Y/N)");

		//storing user input in answer//
		scanf("%s", &answer[0]);

		//creatng loop that continues to ask user until they enter a valid response//
		if(answer[0] != 89)
		{
			//reprinting Bingo card if Y or N is not entered//
			PrintCard(Bingo);

			//incrementing numbers drawn as instructed by rubric//
			NumberofTimes++;
		}

		else if(answer[0] == 89)
		{
			//Incrementing the number of times a card has been drawn//
			NumberofTimes++;

			//setting fair game variable to called nuber exit funtion//
			FairGame = NumberExist(Bingo, newNumber);

			//if ther is no cheating do this contidtion//
			if(FairGame == true)
			{
				//setting bool values equal to return value of functions//
				CompletedRow = CompleteR(Bingo);
				CompletedColumn = CompleteC(Bingo);

				//printing Bingo Card//
				PrintCard(Bingo);
			}

			//if there is cheating, do this condition//
			if (FairGame == false)
			{
				printf("\nThat Value is not on your BINGO car - are you trying to cheat??\n");

				PrintCard(Bingo);

			}
		}

		//if a column is completed, end the game//
		if(CompletedColumn == false)
		{
			gameOngoing = false;
		}

		//if a row is completed, end the game//
		if(CompletedRow == false)
		{
			gameOngoing = false;
		}

		//if s row and a column are completed, end the game//
		if (CompletedColumn == false && CompletedRow == false)
		{
			gameOngoing = false;
		}

		//if the counter reaches 75, end the game//
		if(NumberofTimes == 75)
		{
			gameOngoing = false;
		}
	}

	//if the return value of the complted row was false, display this message//
	if(CompletedRow == false)
	{
		printf("\n\nYou filled out a row - BINGO!!!\n");
	}

	//if the return value of the completed row was false, display this message//
	else if(CompletedColumn == false)
	{
		printf("\n\nYou filled out a column - BINGO!!!\n");
	}

	else if (CompletedColumn == false && CompletedRow == false)
	{
		printf("You filled out a row and a column - BINGO!!!\n");
	}

	//if the number of times equate to 75, display this message//
	if(NumberofTimes == 75)
	{
		printf("\n\nAll numebrs were called. GAME OVER!!\n");
	}

	return 0;
}

//creating function to fill Bingo card//
void FillCard(int Bingo[5][5])
{
	//initializing variables//
	int n = 0;
	int start = 1;
	int end = 15;
	int DUP[25] = {0};
	int x;

	//creating loop that fills the 'B' column with random numbers//
	for(int i = 0; i < 5; i++)
	{
		x = rand() % (end - start + 1) + start;

		for(int j = 0; j < 5; j++)
		{
			if(x == DUP[j])
			{
				x = rand() % (end - start + 1) + start;
				j = -1;
			}
		}
		DUP[i] = x;
	}

	start = start +15;
	end = end + 15;

	//creating loop that fills the 'I' column with random numbers//
	for(int i = 5; i < 10; i++)
	{
		x = rand() % (end - start + 1) + start;

		for(int j = 5; j < 10; j++)
		{
			if(x == DUP[j])
			{
				x = rand() % (end - start + 1) + start;
				j = 4;
			}
		}
		DUP[i] = x;
	}

	start = start +15;
	end = end + 15; 

	//creating loop that fills the 'N' column//
	for(int i = 10; i < 15; i++)
	{
		x = rand() % (end - start + 1) + start;

		for(int j = 10; j < 15; j++)
		{
			if(x == DUP[j])
			{
				x = rand() % (end - start + 1) + start;
				j = 9;
			}
		}
		DUP[i] = x;
	}

	start = start +15;
	end = end + 15; 

	//creating loop that fills the 'G' column//
	for(int i = 15; i < 20; i++)
	{
		x = rand() % (end - start + 1) + start;

		for(int j = 15; j < 20; j++)
		{
			if(x == DUP[j])
			{
				x = rand() % (end - start + 1) + start;
				j = 14;
			}
		}
		DUP[i] = x;
	}

	start = start +15;
	end = end + 15; 

	//creeatig loop that fills the 'O' column//
	for(int i = 20; i < 25; i++)
	{
		x = rand() % (end - start + 1) + start;
		
		for(int j = 20; j < 25; j++)
		{
			if(x == DUP[j])
			{
				x = rand() % (end - start + 1) + start;
				j = 19;
			}
		}
		DUP[i] = x;
	}

	//using indexes of loops to store duplicated values in Bingo array// 
	for(int i = 0; i < 5; i++, n++)
	{
		Bingo[i][0] = DUP[n];
	}

	for(int i = 0; i < 5; i++, n++)
	{
		Bingo[i][1] = DUP[n];
	}

	for(int i = 0; i < 5; i++, n++)
	{
		//filling middle space//
		if(i == 2)
		{
			Bingo[i][2] = 0;
		}
		
		else
		{
			Bingo[i][2] = DUP[n];
		}
	}

	for(int i = 0; i < 5; i++, n++)
	{
		Bingo[i][3] = DUP[n];
	}

	for(int i = 0; i < 5; i++, n++)
	{
		Bingo[i][4] = DUP[n];
	}

	return;
}

//creating function that prints the Bingo Card//
void PrintCard(int BingoCard[5][5])
{
	//initializing variables that print BINGO and formatting//
	char B[5] = "B";
	char I[5] = "I";
	char N[5] = "N";
	char G[5] = "G";
	char O[5] = "O";
	char space[5] = " ";
	char X[5] = "X";
	printf("\n\n");
	printf("%5s%8s%8s%8s%8s", B,I,N,G,O);
	printf("\n");
	printf("-----------------------------------------");
	printf("\n");

	//printing the BINGO card//
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			if(BingoCard[i][j] == 0)
			{
				printf("|%4s%3s", X, space);
			}
			
			else
			{
				printf("|%4d%3s", BingoCard[i][j], space);
			}

		}
		printf("|\n-----------------------------------------");
		printf("\n");
	}

	return;
}
int PickNumber(char newLetter, int newNumber, int EveryVal[75], int AmountofNumbers)
{
	//intitalizing values//
	int start = 1;
	int end = 75;
	int RandomLet = 0;

	//creating array to hold all the EveryVal so far//
	int counter = 0;

	//finding a random letter, given the five letters//
	RandomLet = rand() % (5 - 1 + 1) + 1;

	//if letter is B, do this condition//
	if(RandomLet == 1)
	{
		newLetter = 'B';

		//choosing random number between 1 and 75 to put in newNumber//
		newNumber = rand() % (15 - 1 + 1) + 1;

		//creating loop, that increments counter if number has been used//
		for(int i = 0; i < 75; i++)
		{
			if (EveryVal[i] == newNumber)
			{
				counter++;
			}

			//if counter has been detected, randomize number again//
			if(counter >= 1)
			{
				newNumber = rand() % (15 - 1 + 1) + 1;
				//go through loop again, set counter back to 0//
				i = -1;
				counter = 0;
			}
		
		}
	}

	//if letter is I, do this condition//
	else if (RandomLet == 2)
	{
		newLetter = 'I';

		//choosing random number between 1 and 75 to put in newNumber//
		newNumber = rand() % (30 - 16 + 1) + 16;
		
		//creating loop, that increments counter if number has been used//
		for(int i = 0; i < 75; i++)
		{
			if (EveryVal[i] == newNumber)
			{
				counter++;
			}
		
			//if counter has been detected, randomize number again//
			if(counter >= 1)
			{
				newNumber = rand() % (30 - 16 + 1) + 16;
			
				//go through loop again, set counter back to 0//
				i = -1;
				counter = 0;
			}
		
		}
	}

	//if letter is N, do this condition//
	else if (RandomLet == 3)
	{
		newLetter = 'N';

		//choosing random number between 1 and 75 to put in newNumber//
		newNumber = rand() % (45 - 31 + 1) + 31;

		//creating loop, that increments counter if number has been used//
		for(int i = 0; i < 75; i++)
		{
			if (EveryVal[i] == newNumber)
			{
				counter++;
			}
		
			//if counter has been detected, randomize number again//
			if(counter >= 1)
			{
				newNumber = rand() % (45 - 31 + 1) + 31;
			
				//go through loop again, set counter back to 0//
				i = -1;
				counter = 0;
			}
		
		}
	}

	//if letter G, do this condition//
	else if (RandomLet == 4)
	{
		newLetter = 'G';
		//choosing random number between 1 and 75 to put in newNumber//
		newNumber = rand() % (60 - 46 + 1) + 46;

		//creating loop, that increments counter if number has been used//
		for(int i = 0; i < 75; i++)
		{
			if (EveryVal[i] == newNumber)
			{
				counter++;
			}

			//if counter has been detected, randomize number again//
			if(counter >= 1)
			{
				newNumber = rand() % (60 - 46 + 1) + 46;
				//go through loop again, set counter back to 0//
				i = -1;
				counter = 0;
			}
		}
	}

	//if letter is O, do this condtion//
	else if (RandomLet == 5)
	{
		newLetter = 'O';
		//choosing random number between 1 and 75 to put in newNumber//
		newNumber = rand() % (75 - 61 + 1) + 61;
		
		//creating loop, that increments counter if number has been used//
		for(int i = 0; i < 75; i++)
		{
			if (EveryVal[i] == newNumber)
			{
				counter++;
			}

			//if counter has been detected, randomize number again//
			if(counter >= 1)
			{
				newNumber = rand() % (75 - 61 + 1) + 61;
				//go through loop again, set counter back to 0//
				i = -1;
				counter = 0;
			}
		}
	}

	//setting Array position equal to number, so it can go through it next time function is called//
	EveryVal[AmountofNumbers] = newNumber;

	//Telling user the next number//
	printf("\nThe next number is %c%d", newLetter, newNumber);

	return newNumber;

}

bool NumberExist(int Bingo[5][5], int newNumber)
{
	// intitalizing checker variable//
	int checker = 0;

	//setting checker variabel equal to 0 again//
	checker = 0;

	//looping through Bingo array, if number is found, it is replaced with a 0//
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			if(Bingo[i][j] == newNumber)
			{
				//cheacker is incremented//
				checker++;

				//Bingo is set to 0//
				Bingo[i][j] = 0;
			}
		}
		
	}

	//if checker is equal to, or greater tha checker, then return true//
	if(checker >= 1)
	{
		return true;
	}

	//otherwise, return false, and user is cheating//
	else 
	{
		return false;
	}
}
//creating function that surveys earch row//
bool CompleteR(int Bingo[5][5])
{
	//initializing counter vairables//
	int RowCounter = 0;
	int RowComplete = 0;

	//creating loop that goes through each row//
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			//if a 0 is found, add to counter//
			if(Bingo[i][j] == 0)
			{
				RowCounter++;
			}
			
			//if 5 counters are found, mark a complete row//
			if (RowCounter == 5)
			{
				RowComplete = 1;
			}
		}

		//resetting row counter//
		RowCounter = 0;
	}

	//if a row was finisshed, return false//
	if(RowComplete == 1)
	{
		return false;
	}

	//otherwise, return true//
	else
	{
		return true;
	}
}

//creating function that surveys each column of BingoCard//
bool CompleteC(int Bingo[5][5])
{
	//Setting two different counters for saftey//
	int ColumnCounter = 0;
	int ColumnComplete = 0;

	//creating loop that specifically checks each column, using reversse index//
	for(int j = 0; j < 5; j++)
	{
		for(int i = 0; i < 5; i++)
		{
			//add counter eahc time a 0 in one row is spotted//
			if(Bingo[i][j] == 0)
			{
				ColumnCounter++;
			}
			//if the counter adds up to 5, mark a column complete//
			if(ColumnCounter == 5)
			{
				ColumnComplete = 1;
			}
			
		}

		//set column counter back to 0 for next iteration//
		ColumnCounter = 0;
	}

	//if a column was complter, return false//
	if(ColumnComplete == 1)
	{
		return false;
	}

	//otherwise, return true//
	else
	{
		return true;
	}
}
