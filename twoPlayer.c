/*
 * twoPlayer.c
 *
 *  Created on: Dec 16, 2016
 *      Author: eliasy
 */

#include<stdio.h>
#include"defs.h"
#include"gameIO.h"
#include"zeroPlayer.h"
#include<stdlib.h>

static int validIndex(Element arr, int drow, int dcolumn, State compareValue)
{
	Element e;

	if (drow>-1 && dcolumn<((Array)arr)->size)
	{
		e = get((((Array)arr)->elements[drow]),dcolumn);
		if (((Cell)e)->cellState == compareValue)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;	
}


Element evolveCellTW (Element element)
{
	int i,count;
	int count1=0;
	int count2=0;
	Cell cell=(Cell)element;
	for (i=0;i<8;i++)
	{
		//count how many neighbors from each color;
		if (cell->neighbors[i] != BLANK && cell->neighbors[i] != DEAD)
		{
                	if (cell->neighbors[i] == P1)
                		count1++;
                	if (cell->neighbors[i] == P2)
                	count2++;
		}
	}
	//check how many neighbors in general
	count=count1+count2;
	//the cell died from lonleyness or from too many neighbors
	if ( count<2 || count>3 )
		cell->cellState=DEAD;
	//the cell have three neighbors and he is come back to live
	if (cell->cellState==DEAD && count==3)
	{
		if (count1>count2)
			cell->cellState=P1;
		else
			cell->cellState=P2;
	}

	if (cell->cellState!=DEAD && cell->cellState!= BLANK)
	{
		if (cell->cellState == P1 && count1<count2 )
			cell->cellState = P2;
		if (cell->cellState == P2 && count1>count2 )
			cell->cellState = P1;
	}
	return (Element)cell;
}


void twoPlayer(int size, char * fileName, int numIteration)
{
	//Element e;
	//e= createCell('.');
	Cell cell=createCell('.');
	Array gameBoard;

	//Creating the game board
	gameBoard = creat_Board(size, fileName, 2);
	printArray(gameBoard);
	printf("\n");
	int drow, dcolumn, i;

	//Main loop for the iteration
	for (i=0;i<numIteration;i++)
	{
		printf("Player number one please type a row and a column of a cell you want to kill: ");
		scanf("%d %d",&drow,&dcolumn);
		//Check that the indexes given by player one are valid
		while (validIndex(gameBoard,drow,dcolumn,P2) == 0)
		{
			printf("You typed wrong indexes please type again, row and a column you want to  kill: ");
			scanf("%d%d",&drow,&dcolumn);
		}
		cell->cellState=DEAD;
		set(((Array)(gameBoard->elements[drow])),dcolumn,(Element)cell);
		
		//free(cell);
		//cell=createCell('.');


		updateNeib ((Element)gameBoard);
		printArray((Element)gameBoard);
		printf("\n");
		printf("player number one please type a row and a column you want to bring to life: ");
		scanf("%d%d",&drow,&dcolumn);
		//Validating player one inputs
		while (validIndex(gameBoard,drow,dcolumn,DEAD) == 0)
		{
			printf("you type wrong indexes please type again, row and a column you want to bring to life:");
			scanf("%d%d",&drow,&dcolumn);
		}
		cell->cellState=P1;
		set(((Array)(gameBoard->elements[drow])),dcolumn,(Element)cell);

		//cell=createCell('.');

		updateNeib ((Element)gameBoard);
		printArray((Element)gameBoard);
		printf("\n");
		//Running evolve on the array
		gameBoard->evolveElement((Element)gameBoard);
		updateNeib ((Element)gameBoard);
		printArray((Element)gameBoard);
		printf("\n");
		printf("player number two please type a row and a column of a cell you want to kill: ");
		scanf("%d %d",&drow,&dcolumn);
		while (validIndex(gameBoard,drow,dcolumn,P1) == 0)
		{
			printf("you type wrong indexes please type again, row and a column you want to kill: ");
			scanf("%d %d",&drow,&dcolumn);
		}
		cell->cellState=DEAD;
		set(((Array)(gameBoard->elements[drow])),dcolumn,(Element)cell);

		//cell=createCell('.');

		updateNeib ((Element)gameBoard);
		printArray((Element)gameBoard);
		printf("\n");
		printf("player number one please type a row and a column you want to bring to life: ");
		scanf("%d %d",&drow,&dcolumn);
		while (validIndex(gameBoard,drow,dcolumn,DEAD == 0))
		{
			printf("you type wrong indexes please type again, row and a column you want to bring to life: ");
			scanf("%d %d",&drow,&dcolumn);
		}
		cell->cellState=P2;
		set(((Array)(gameBoard->elements[drow])),dcolumn,(Element)cell);

		//cell=createCell('.');

		updateNeib ((Element)gameBoard);
		printArray((Element)gameBoard);
		printf("\n");
		gameBoard->evolveElement((Element)gameBoard);
		updateNeib ((Element)gameBoard);
	}
	freeCell(cell);
	printArray(gameBoard);
	gameBoard->freeElement((Element)gameBoard);
}











