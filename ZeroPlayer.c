/*
 * zeroPlayer.c
 *
 *  Created on: Dec 7, 2016
 *      Author: ise
 */

#include<stdio.h>
#include"defs.h"
#include"gameIO.h"
#include"zeroPlayer.h"


Element evolveCellZP (Element element)
{
	int i;
	int count=0;
	Cell cell=(Cell)element;

	//count how many neighbors i have
	for (i=0;i<8;i++)
	{
		if (cell->neighbors[i] == P1)
		{
				count++;
		}
	}
	if (count < 2)
	{
		cell->cellState=DEAD;
	}

	if (count > 3)
	{
		cell->cellState=DEAD;
	}
	// if cell is dead and have exactly three neighbors
	if (count==3)

	{
		if (cell->cellState == DEAD)
			{

		      cell->cellState=P1;
			}
	}
	return (Element)cell;
}

void zeroPlayer(int size, char * fileName, int numIteration)
{

	int i;
	Array gameBoard;

	gameBoard = creat_Board(size, fileName,1);

	for (i=0;i<numIteration;i++)
	{
		gameBoard->evolveElement((Element)gameBoard);
		updateNeib ((Element)gameBoard);


	}
	//Printing the gabe board
	printArray(gameBoard);
	gameBoard->freeElement((Element)gameBoard);
}
