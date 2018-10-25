/*
 * gameIO.c
 *
 *  Created on: Dec 6, 2016
 *      Author: ise
 */

#include<stdio.h>
#include<stdlib.h>
#include"gameIO.h"
#include"defs.h"
#include"zeroPlayer.h"
#include "twoPlayer.h"

//Creating the two dimention array for the game board and populating it
Array creat_Board(int size, char * fileName,int player)
{
	int flag;
	Array gameBoard = NULL;
	int i,j,n;

	/*Calling the function to create the array for the game board*/
	gameBoard = createArray(size, copyArray, free_Arr,printArray, evolve_array);

	for (i=0; i<size; i++)
	{
		if (player==1)
		{
			gameBoard->elements[i]=createArr(size, copyCell, freeCell, printCell, evolveCellZP);
		}
		if (player==2)
		{
			gameBoard->elements[i]=createArr(size , copyCell, freeCell, printCell, evolveCellTW);
		}

	}
	/*Creating the game board*/
	flag = populateArray(fileName,gameBoard);
	updateNeib ((Element)gameBoard);
	return (gameBoard);
}

//Populating the array from file
int populateArray(char *fileName, Array array)
{
	FILE *pFile;
	char * bufferLine;
	int arrRow,strColumn,arrColumn;
	Element e = NULL;

	//Allocating memory for reading the line
	bufferLine = (char *)malloc(sizeof(char)*(array->size)*2 + 1);
	if(bufferLine == NULL)
	{
		return 0;
	}

	pFile = fopen(fileName,"r");
	//Check if opening the file succeed or not
	if (pFile == NULL)
	{
		fprintf(stderr, "Can't open input file %s!\n",fileName);
		return 0;
	}
	//Reading the file
	arrRow = 0;
	arrColumn = 0;
	//Going over the lines in the file
	while (EOF != fscanf(pFile,"%[^\n]\n",bufferLine))
	{
		if(bufferLine[0] != '\n' && bufferLine[0] != ' ')
		{
			//printf("%s\n",bufferLine);

			//Going over the columns in the file
			bufferLine[(array->size)*2] = '\0';
			for(strColumn=0; (bufferLine[strColumn] != '\0' && bufferLine[strColumn] != '\n'); strColumn++)
			{
				//If the column is not a space delimiter
				if(strColumn%2 == 0)
				{
					e = createCell(bufferLine[strColumn]);
					if(e == NULL)
					{
						free(e);
						return 0;
					}
					set((Array)(array->elements[arrColumn]),arrRow,e);
					free(e);
					arrRow++;
				}
			}
			arrRow = 0;
			arrColumn++;
		}
	}
	free(bufferLine);
	fclose(pFile);
	return 1;
}

