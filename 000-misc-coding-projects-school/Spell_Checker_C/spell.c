#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "spell.h"

/*  
Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(D*T)

Worst case to do an unsuccessful binary search in a dictionary with D words, when 
all dictionary words and the searched word have length MAX_LEN 
Student answer:  Theta(log(n))
*/


/* You can write helper functions here */
void printtable(char * str1, char * str2,int row, int col, int dist[row][col])
{
	char str1new[100] = " ";
	char str2new[100] = "  ";
	
	strcat(str1new, str1);
	strcat(str2new, str2);
	
	for(int i = 0; i < strlen(str2new); i++)
	{
		printf("%3c|", str2new[i]);
	}
	
		//print ------- //
		printf("\n");
		for(int i = 0; i < strlen(str2new); i++)
		{
			char bar[5] = "----";
			printf("%s", bar);
		}
		printf("\n");
	
	for(int i = 0; i < strlen(str1new); i++)
	{
		printf("%3c|", str1new[i]);
		for(int j = 0; j < strlen(str2new)-1; j++)
		{
			printf("%3d|", dist[i][j]);
			
		}
		
		//print --------- //
		printf("\n");
		for(int i = 0; i < strlen(str2new); i++)
		{
			char bar[5] = "----";
			printf("%s", bar);
		}
		printf("\n");
	}
}

//Function that compares two strings to sort them
int compare(const void *a, const void *b)
{
	const char *ia = a;
   const char *ib = b;
   return strcasecmp(ia, ib);
}

int binary_search(int num, char dictionary[num][20], char text[], int verbose, int found[2])
{
	//Initializing Varaibles
	int size = strlen(text);
	int num_comp_words = 0;
	char text2[100] = "";
	
	//Changing string to lower case
	for(int i = 0; i < strlen(text); i++)
	{
		text2[i] = tolower(text[i]);
	}
	
	

	//Initializing Variables
	int left = 0;
	int right = num-1;
	int middle = 0;	
   
	if(verbose == 1)
	{
		printf("\nBinary Search for: %s", text2);
	}
	
	do
   {
		//Set Middle
		middle = (left + right )/ 2;
		
		for(int i = 0; i < strlen(dictionary[middle]); i++)
		{
			if(dictionary[middle][i] == '\n')
			{
				dictionary[middle][i] = '\0';
			}
		}
		
		if(verbose == 1)
		{
			printf("\ndict[%d] = %s", middle, dictionary[middle]);
		}
		
		num_comp_words++;
		
		//If text is < then go to UpperBound
      if (strcmp(text2,dictionary[middle]) < 0)
		{
			right = middle - 1;
			
		}      
      
		//If text is > go to LowerBound
		else if ((strcmp(text2,dictionary[middle])) > 0)
		{
			left = middle + 1;
		}  
		
   } while ((strcmp(text2, dictionary[middle])!=0) && left <= right);
	
	//If word is Found...
	if ((strcmp(text2,dictionary[middle]))==0)
	{
		if(verbose == 1)
		{
			printf("\nWord Found\n");
			
		}
		found[0] = 1;
		
	}
	//If word is not Found...
	else
	{
		if(verbose == 1)
		{
			printf("\nNot Found\n");
		}
		found[0] = 0;
	}
	return num_comp_words;
 }
	

//Function finds minimum of three values
int min(int a, int b, int c)
{	
	if(a <= b && a <= c)
	{
		return a;
	}
	else if(b <= a && b <= c)
	{
		return b;
	}
	else if(c <= a && c <= b)
	{
		return c;
	}
}

//Function Finds the edit distance of two strings
int edit_distance(char * first_string, char * second_string, int print_table)
{
	char first_string1[1000] = "";
	
	//If string contains '\n', change to '\0'
	for(int i = 0 ; i < strlen(second_string); i++)
	{
		if(second_string[i] == '\n')
		{
			second_string[i] = '\0';
		}
	}
	
	//Changing case
	for(int i = 0; i < strlen(first_string); i++)
	{
		first_string1[i] = tolower(first_string[i]);
	}
	
	int m = strlen(first_string1);
	int n = strlen(second_string);
	
	// Create a table to store results of subproblems
	int dp[m + 1][n + 1];
	
   // Filling dp using bottom up
   for (int i = 0; i <= m; i++) 
	{
      for (int j = 0; j <= n; j++) 
		{
			
         if (i == 0)
			{
				dp[i][j] = j;
			}
  
         else if (j == 0)
			{
				dp[i][j] = i;
			}
         
         else if (first_string1[i - 1] == second_string[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}

         else
			{
				dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]); 
			}
      }
	}
	
	if(print_table == 1)
	{
		printtable(first_string,second_string, m + 1, n + 1, dp );
	}

	return dp[m][n];
}

	

/*
Parameters:
testname - string containing the name of the file with the paragraph to spell check, includes .txt e.g. "text1.txt" 
dictname - name of file with dictionary words. Includes .txt, e.g. "dsmall.txt"
printOn - If 1 it will print EXTRA debugging/tracing information (in addition to what it prints when 0):
			 dictionary as read from the file	
			 dictionary AFTER sorting in lexicographical order
			 for every word searched in the dictionary using BINARY SEARCH shows all the "probe" words and their indices indices
			 See sample run.
	      If 0 (or anything other than 1) does not print the above information, but still prints the number of probes.
		     See sample run.
*/
void spell_check(char * testname, char * dictname, int printOn)
{
	//Opening Files...
	FILE *fp_text = fopen(testname, "r");
	FILE *fp_dict = fopen(dictname, "r");
	
	//If Files did not Open Properly...
	if(fp_text == NULL || fp_dict == NULL)
	{
		printf("A file did not open properly...");
		return;
	}
	
	printf("Corrected output filename: out_%s", testname);
	
	//Initializing Variables
	char buffer_text[200];
	char buffer_dict [2000];
	char dictionary[20000][20];
	int word_count;
	
	//Getting text from file
	fgets(buffer_text, sizeof(buffer_text)-1, fp_text);
	
	//Scanning Dictionary, Copying to 2D array
	int k = 0;
	fscanf(fp_dict, "%d", &word_count);
	
	
	printf("\n\nLoading the dictionary file: %s\n", dictname);
	printf("\nDictionary has size: %d", word_count);
	
	while(fgets(buffer_dict, sizeof(buffer_dict)-1, fp_dict) != NULL)
	{
		strcpy(dictionary[k], buffer_dict);
		k++;
	}
	
	if(printOn == 1)
	{
		printf("\n Original Dictionary:\n");
		for(int i = 0; i < word_count; i++)
		{
			printf("%d. %s", i, dictionary[i+1]);
		}
	}
	
	
	//Sorting Dictionary Alphabetically...
	qsort(&dictionary[1], word_count, sizeof(dictionary[0]), compare);
	
	if (printOn == 1)
	{
		printf("\n Sorted Dictionary (alphabetical order):\n");
		for(int i = 0; i < word_count; i++)
		{
	
			printf("%d. %s",i,  dictionary[i+1]);
		}
	}
	
	
	//Finding number of words in text file
	int number_of_words = 0;
	int consec_lett = 0;
	for(int i = 0; i < strlen(buffer_text); i++)
	{
		
		if(buffer_text[i] == ',' || buffer_text[i] == '!' || buffer_text[i] == '?' || buffer_text[i] == '.' || buffer_text[i] == ' ')
		{
			if (consec_lett > 0)
			{
				number_of_words++;
			}
			consec_lett = 0;
		}
		else
		{
			consec_lett++;
		}
	}
	
	
	
	number_of_words = number_of_words + 1;
	int max_length = 15; 
	
	//Reserving space to save words in text file to 2D array
	char saved_text[number_of_words][max_length];
	for(int i = 0; i < number_of_words; i++)
	{
		for(int j = 0; j < max_length; j++)
		{
			saved_text[i][j] = '\0';
		}
	}
	
	//Soring text into 2D array
	int num_pos = 0;
	int char_pos = 0;
	char punct_arr[500] = "";
	int a = 0;
	
for(int i = 0; i < strlen(buffer_text); i++)
	{
		if(buffer_text[i] == ' ')
		{
			if(buffer_text[i+1] == ' ' || buffer_text[i+1] == ',' || buffer_text[i+1] == '!' || buffer_text[i+1] == '?' || buffer_text[i+1] == '.' )
			{
				punct_arr[a] = buffer_text[i];
				a++;
				continue;
			}
			
			
			if((buffer_text[i+1] != ' ' &&  buffer_text[i+1] != ',' && buffer_text[i+1] != '!' && buffer_text[i+1] != '?' && buffer_text[i+1] != '.' ) && (buffer_text[i-1] == ',' || buffer_text[i-1] == '!' || buffer_text[i-1] == '?' || buffer_text[i-1] == '.' || buffer_text[i-1] == ' '))
			{
				if(char_pos !=0)
				{
					
					saved_text[num_pos][char_pos] = '\0';
					char_pos = 0;
					num_pos++;
				}
				punct_arr[a] = buffer_text[i];
				a++;
				continue;
				
			}
			
			
			else
			{
				saved_text[num_pos][char_pos] = '\0';
				char_pos = 0;
				num_pos++;
				punct_arr[a] = buffer_text[i];
				a++;
				continue;
			}
			
		}
		
		/*if((buffer_text[i] == ',' || buffer_text[i] == '!' || buffer_text[i] == '?' || buffer_text[i] == '.') && (buffer_text[i-1] != ',' && buffer_text[i-1] != '!' && buffer_text[i-1] != '?' && buffer_text[i-1] != '.' && buffer_text[i-1] != ' ') && (buffer_text[i+1] != ' ' || buffer_text[i+1] != ',' || buffer_text[i+1] != '!' || buffer_text[i+1] != '?' || buffer_text[i+1] != '.' ))
		{
			saved_text[num_pos][char_pos] = '\0';
			char_pos = 0;
			num_pos++;
			punct_arr[a] = buffer_text[i];
			a++;
			continue;
			
		}
		*/
		if(buffer_text[i] == ',' || buffer_text[i] == '!' || buffer_text[i] == '?' || buffer_text[i] == '.')
		{
			if(char_pos != 0)
			{
				saved_text[num_pos][char_pos] = '\0';
				char_pos = 0;
				num_pos++;
				
			}
			punct_arr[a] = buffer_text[i];
			a++;
			continue;
		}
		
		//If buffer is not punctation, save that charcater...
		if(buffer_text[i] != ',' && buffer_text[i] != '!' && buffer_text[i] != '?' && buffer_text[i] != '.' && buffer_text[i] != ' ')
		{
			saved_text[num_pos][char_pos] = buffer_text[i];
			char_pos++;
			punct_arr[a] = 'i';
			a++;
		}
	}
	
	//Initializing Variables
	int control = 1;
	int b = 0;
	int num_comp_words = 0;
	int edit_dist_value = 0;
	int edit_distance_arr[word_count];
	int arr_of_min[word_count];
	int min_dist = 0;
	int program_counter = 0;
	
	
	while(program_counter < number_of_words)
	{
		//Finding th enumber of words compared
		//Binary Search
		if(strcmp(saved_text[b], "") == 0)
		{
			break;
		}
		
		int found[2] = {0, 0};
		num_comp_words = binary_search(word_count, &dictionary[1], saved_text[b], printOn, found);
		
		printf("\n---> |%s| (words compared when searching %d)", saved_text[b],num_comp_words);
		
		if(found[0] == 1)
		{
			printf("\n     -OK\n\n");
			b++;
			program_counter++;
			continue;

		}
	
		
		
		
		//Creating an array of edit distances
		for(int i = 1; i <= word_count; i++)
		{
			int length_of_dict_word = strlen(dictionary[i]);
			
			char copied_dict_word[length_of_dict_word];
			strcpy(copied_dict_word, dictionary[i]);
			
			//Calculating edit distance
			edit_dist_value = edit_distance(saved_text[b], copied_dict_word, 0);
			edit_distance_arr[i] = edit_dist_value;
			
		}
		
		//Preparing to find minimum edit distance
		min_dist = edit_distance_arr[1];
		int index = 1;
		
		//Finding minimum value in edit distance array//
		for(int i = 1; i <= word_count; i++)
		{
			if(edit_distance_arr[i] < min_dist)
			{
				min_dist = edit_distance_arr[i];
			}
		}
		
		//Filling array of indexes of edit distances
		for(int i = 0; i <= word_count; i++)
		{
			arr_of_min[i] = -1;
		}
		
		int index_of_min = 1;
		
		//Creating array of indexes of minimum edit distances
		for(int i = 1; i <= word_count; i++)
		{
			if (edit_distance_arr[i] == min_dist)
			{
				arr_of_min[index_of_min] = i;
				index_of_min++;
			}
		}
	



		printf("\n-1 - type correction");
		printf("\n 0 - leave word as is (do not fix spelling)");
		printf("\n     Minimum distance: %d (computed edit distances: %d)", min_dist, word_count);
		printf("\n     Words that give the minimum distance:");
		
		//hello
		for(int i = 1; i < index_of_min; i++)
		{
			for(int j = 0; j < strlen(dictionary[arr_of_min[i]]); j++)
			{
				if(dictionary[arr_of_min[i]][j] == '\n')
				{
					dictionary[arr_of_min[i]][j] = '\0';
					
				}
				
			}
			printf("\n%d - %s", (i), dictionary[arr_of_min[i]]);
		}
		
		printf("\nEnter your choice (from the above options): ");
		scanf("%d", &control);
		
		
		
		
		
		
		
		
		
		
		char correct_str[100];
		
		if(control == -1)
		{
			printf("Enter correct word: ");
			scanf("%s", correct_str);
			strcpy(saved_text[b],correct_str);
		}
		else if(control == 0)
		{
		
		}
		else
		{
			strcpy(saved_text[b], dictionary[arr_of_min[control]]);
			for(int i = 0; i < strlen(saved_text[b]); i++)
			{
				if(saved_text[b][i] == '\n')
				{
					saved_text[b][i] = '\0';
				}
			}
		}
		
		b++;
		program_counter++;
		
	}


	FILE *fw;
	char output_beg[5] = "out_";
	char output_end[5] = ".txt";
	char output_name[100] = "";
	strcat(output_name, output_beg);
	strcat(output_name, testname);
	strcat(output_name, output_end);
	
	
	fw = fopen(output_name, "w+");
	
	b = 0;
	int p = 0;
	char empty[3] = "\0";
	int once = 0;
	
	for(int i = 0; i < strlen(punct_arr)+1; i++)
	{
		
		if(punct_arr[p] == 'i')
		{
			
			if(once > 0)
			{
				p++;
				continue;
			}
			
			else
			{
				
				fprintf(fw, "%s", saved_text[b]);
				b++;
				p++;
				once++;
				continue;
			}
			
		}
		
		else
		{
			once= 0;
			fprintf(fw, "%c", punct_arr[p]);
			p++;
		
			
		}
		
	
	}
	
	fclose(fp_text);
	fclose(fp_dict);
	fclose(fw);
	
	//TODO Binary Seach
	//Compare Edit Distance
	//Verbose & Non-Verbose
}

	