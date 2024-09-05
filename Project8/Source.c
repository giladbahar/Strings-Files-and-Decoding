/*
   Assigned by:
   Gilad Bahar 318939469
   Tomer Biton 209169333	
*/

#define _CRT_SECURE_NO_WARNINGS

/* Libraries */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Constant definitions */

#define N 3

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

char** split(char letter, char* str, int* p_size);
void createFile(char* filename);
char commonestLetter(char* filename);
void decode(char* text);

/* Declarations of auxiliary functions */

void printStringsArray(char** str_arr, int size);
void freeMatrix(void** A, int rows);

/* Main function */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= N; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-%d : ", N);
				scanf("%d", &select);
			} while ((select < 0) || (select > N));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}

/* Void functions to activate the program */

void Ex1()
{
	char letter;
	char** str_arr = NULL;
	char str[100];
	int p_size;

	rewind(stdin);
	printf("\nEnter a string: ");
	fgets(str, sizeof(str), stdin);

	printf("Enter a letter: ");
	scanf("%c", &letter);

	str_arr = split(letter, str, &p_size);

	printf("\nThe words that appear in the string and begin with the letter '%c' are:\n", letter);
	printStringsArray(str_arr, p_size);
	freeMatrix(str_arr, p_size);
}

void Ex2()
{
	char* filename = "input.txt", common_letter;
	createFile(filename);
	common_letter = commonestLetter(filename);
	printf("\nThe most common letter is '%c'.\n\n", common_letter);
}

void Ex3()
{
	char text[54] = "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt";
	printf("\nText before decoding:\n");
	puts(text);
	decode(text);
	printf("\nText after decoding:\n");
	puts(text);
	printf("\n");
}

/* Function definitions */

/* Ex 1 */
/* This function gets a letter and a string that contains a few words.
   It creates a dynamic array of strings, so that each word in the array starts with the letter recieved by the function. */
char** split(char letter, char* str, int* p_size)
{
	int word_len = 0;
	char** str_mat = NULL;
	*p_size = 0;
	int i;

	if (str[0] == letter || str[0] - 'a' == letter - 'A' || str[0] - 'A' == letter - 'a')
		(*p_size)++;

	for (i = 1; str[i]; i++)
	{
		if (str[i - 1] == ' ' && str[i] == letter || str[i - 1] == ' ' && str[i] - 'A' == letter - 'a' ||
			str[i - 1] == ' ' && str[i] - 'a' == letter - 'A')
			(*p_size)++;
	}

	if (*p_size == 0)
		return NULL;

	str_mat = (char**)calloc(*p_size, sizeof(char*));
	if (!str_mat) return NULL;

	char* word = strtok(str, " "); i = 0;
	while (word)
	{
	    word_len = 0;
		if (word[0] == letter || word[0] - 'A' == letter - 'a' || word[0] - 'a' == letter - 'A')
		{
			word_len = strlen(word);
			str_mat[i] = (char*)calloc(word_len + 1, sizeof(char));
			if (!str_mat) return NULL;

			strcpy(str_mat[i++], word);
		}
		word = strtok(NULL, " ");
	}
	return str_mat;
}

/* Ex 2 */
/* This function gets a string with a name of a txt file.
   It creates a file and enters characters from the keyboard into it. */
void createFile(char* filename)
{
	char c;
	FILE* src = fopen(filename, "w");
	if (!src)
	{
		printf("File open failed");
		return;
	}

	printf("\nEnter characters below.\nTo Exit enter '@'.\nCharacters:\n");
	while ((c = getchar()) != '@')
		fputc(c, src);

	fclose(src);
}

/* This function gets a txt file and return the most common letter in it. */
char commonestLetter(char* filename)
{
	int count[26] = { 0 }, max = 0, index = 0, i;
	char c;
	FILE* src = fopen(filename, "r");
	if (!src)
	{
		printf("File open failed");
		return '\0';
	}

	while ((c = fgetc(src)) != EOF)
	{
		if (isalpha(c))
			islower(c) ? count[c - 'a']++ : count[c - 'A']++;
	}

	for (i = 0; i < 26; i++)
	{
		if (count[i] >= max)
		{
			max = count[i];
			index = i;
		}
	}

	fclose(src);
	return max > 0 ? index + 'A' : '\0';
}

/* Ex 3 */
/* This function gets an encoded string, and decodes it by subtract numbers from the ASCII value of the characters. */
void decode(char* text)
{
	int count = 1, i = 0;

	while (text[i])
	{
		if (text[i] != ' ')
		{
			text[i++] -= count++;
		}
		else
		{
			count = 1;
			i++;
		}
	}
}

/* Auxiliary functions */

void printStringsArray(char** str_arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		puts(str_arr[i]);
	}
	printf("\n");
}

void freeMatrix(void** A, int rows)
{
	int i;
	for (i = 0; i < rows; i++)
	{
		free(A[i]);
	}
	free(A);
}