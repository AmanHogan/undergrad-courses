//Aman Hogan-Bailey MAV-ID: 1001830469//
/* Coding Assignment 6 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "GameLib.h"

void StartGame(char ChosenPhrase[])
{
	#include "PhraseBank.txt"
	
	char DashPhrase[MAX_INPUT] = {};
	int i = 0;
	int Choice = 0;
	
	printf("\n\nWelcome to %d STRIKES - YOU'RE OUT - the CSE version\n\n", STRIKES);
	
	printf("Please pick a phrase from the following menu\n\n");
	
	/* while PhraseBank[i] is not empty "" */
	while (PhraseBank[i] != "")
	{
		/* Call CheckPhrase with PhraseBank[i] */
		CheckPhrase(PhraseBank[i]);
		
		/* Call DashIt with PhraseBank[i] and DashPhrase */
		DashIt(PhraseBank[i],DashPhrase);
		
		printf("%d.\t%s\n", i+1, DashPhrase);
		i++;
	}
	
	printf("\nEnter choice : ");
	scanf("%d", &Choice);
	getchar();
	
	/* create a while condition that is true when Choice is less than 1 or greater than i */
	while((Choice < 1) || (Choice > i))
	{
		printf("You entered an invalid choice.\nPlease reenter ");
		scanf("%d", &Choice);
	}
	
	/* copy the phrase from PhraseBank based on Choice into ChosenPhrase */ 
	strcpy(ChosenPhrase, PhraseBank[Choice - 1]);
}

void CheckPhrase(char *Phrase)
{
	/* Declare a char pointer named FindDash and initialize it to NULL */
	char *FindDash = NULL;
	
	/* call strchr() with Phrase and a dash and store the result in FindDash.  If that */
	/* value is not NULL, then you found a dash
	*/
	FindDash = strchr(Phrase, '-');
	
	if(FindDash != NULL)
	{
		printf("\n\"%s\" contains a dash in position %d!!\n", Phrase, abs(Phrase-FindDash)+1);
		printf("\nYou broke the rules.  We can't play.  BYE!!\n\n");
		
		/* exit the program */
		exit(0);
	}
}

int GuessALetter(char Phrase[MAX_INPUT], char DashedPhrase[MAX_INPUT], char UpperPhrase[MAX_INPUT])
{
	char Guess;
	char *FindGuess = NULL;
	char UpperPhraseCopy[MAX_INPUT];
	int FoundALetter = 0;
	
	/* copy UpperPhrase into UpperPhraseCopy */
	strcpy(UpperPhraseCopy, UpperPhrase);
		
	printf("\n\n%s", DashedPhrase);	
	printf("\n\nGuess a letter : ");
	scanf(" %c", &Guess);
	getchar();
	
	/* uppercase Guess */
	Guess = toupper(Guess);

	/* Use strchr() to look for Guess in UpperPhraseCopy.  Store the result of strchr() */
	/* in FindGuess                                                                     */
	FindGuess = strchr(UpperPhraseCopy, Guess);
	
	while(FindGuess != NULL)
	/* while FindGuess is not NULL */
	{
		FoundALetter = 1;
		DashedPhrase[FindGuess - UpperPhraseCopy] = Phrase[FindGuess - UpperPhraseCopy];
		/* Dereference FindGuess and set it to a dash */
		*FindGuess = '-';

		/* Call strchr() again */
		FindGuess = strchr(UpperPhraseCopy, Guess);
	}
	
	return FoundALetter;
}

void DashIt(char *Phrase, char DashPhrase[])
{
	char *ReplaceIt;
	char Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i = 0;

	/* Put the uppercase version of Phrase into DashPhrase */
	for(int j = 0; j <= MAX_INPUT; j++)
	{
		DashPhrase[j] = toupper(Phrase[j]);
	}

	/* Call strpbrk() with DashPhrase and Alphabet and save the result in ReplaceIt */
	ReplaceIt = strpbrk(DashPhrase, Alphabet);
	
	/* while ReplaceIt is not NULL */
	while(ReplaceIt != NULL)
	{
		/* Dereference ReplaceIt and set it to a dash */
		*ReplaceIt = '-';
		
		/* Call strpbrk() again */
		ReplaceIt = strpbrk(DashPhrase, Alphabet);
	}
}
