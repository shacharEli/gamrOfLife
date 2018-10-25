/*
 * defs.c
 *
 *  Created on: Dec 6, 2016
 *      Author: ise
 */
#include<stdio.h>
#include<stdlib.h>
#include"defs.h"

/*Creating the array*/
Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve)
{
	Array array = NULL;
	int i;

	if(_size == 0)
	{
		return NULL;
	}

	//Allocating memory for main array
	array = (Array)malloc(sizeof(struct t_array));
	if(array == NULL)
	{
		return NULL;
	}

	//Initializing the board size
	array->size = _size;

	//Allocating one dimension array of elements
	array->elements = NULL;
	array->elements = (Element*)malloc(sizeof(Element)*(array->size));
	if(array->elements == NULL)
	{
		free(array);
		return NULL;
	}

	for(i = 0; i < array->size; i++)
	{
		array->elements[i] = NULL;
	}

	//Initializing the function pointers
	array->evolveElement = _evolve;
	array->freeElement = _free;
	array->printElement = _print;
	array->copyElement = _copy;

	return array ;
}

/*Sub function for creating an array*/
Element createArr(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve)
{
	Array array = NULL;
	array=createArray(_size,_copy,_free,  _print,_evolve);
	return ((Element)array);
}

/*free Array*/
void destroyArray(Array array)
{
	int i;
	/* check if array!=null*/
	if (array == NULL)
		return;

	/*free every cell*/
	for(i =0; i< array->size;i++)
	{
		if(array->elements[i] != NULL)
			array->freeElement(array->elements[i]);
	}
	free(array->elements);
	free(array);
	return;
}

//free Array
void free_Arr(Element element)
{
	destroyArray((Array)element);
}

/*update Array[i] to be element*/
void set(Array array, int i, Element element)
{
	Element temp;
	if (element != NULL)
	{
		temp = array->copyElement(element);
		if(temp !=  NULL)
		{
			if(array->elements[i] != NULL)
			{
				array->freeElement(array->elements[i]);
			}
			array->elements[i]=temp;
                	//array->freeElement(element);
		}
	}
}

/*get Array[i]*/
Element get(Array array, int i)
{
	if (i>array->size || i <0)
	{
		printf("wrong, %d",i);
		return NULL;
	}
	return array->elements[i];
}

/*Copy array*/
Element copyArray(Element element)
{
	int i;
	Array newArray;

	Array cArray= (Array) element;


	newArray = createArray(cArray->size,cArray->copyElement,cArray->freeElement,cArray->printElement,cArray->evolveElement);

	for(i=0;i<newArray->size;i++)
	{
		newArray->elements[i]=cArray->elements[i];
	}
	return (Element)newArray;
}


void printArray(Element element)
{
	int i,check;
	Array array=(Array)element;
	check=array->size;

	for(i=0; i<array->size;i++ )
	{
		 printArr(array->elements[i],check-i);
	}
	printf("\n");
}

void printArr(Element element,int check )
{
	int i;
	Array array=(Array)element;

	for(i=0; i<array->size;i++ )
	{
		 array->printElement(array->elements[i]);
	}
	if (check != 1)
	printf("\n");
}

Element evolve_array(Element element)
{
	Array array= (Array) element;

	int i;

	for(i=0;i<array->size;i++)
	{
		array->evolveElement(array->elements[i]);
	}
	return  (Element)array;
}

Element createCell(char c)
{
	Cell pCell;
	pCell = (Cell)malloc(sizeof(struct t_cell)*1);
	if(pCell == NULL)
	{
		free(pCell);
		return NULL;
	}
	//Assign the status of the Cell
	switch (c)
	{
		case '.':
			pCell->cellState = DEAD;
			break;

		case 'X':
			pCell->cellState = P1;
			break;
		case 'Y':
			pCell->cellState = P2;
			break;
		default:
	 		pCell->cellState= BLANK;
	}
	int i;
	for(i=0; i<8; i++)
	{
		pCell->neighbors[i]=BLANK;
	}

	return (Element)pCell;
}

void printCell(Element element)
{
	Cell cell=(Cell) element;
	if (cell->cellState== DEAD)
	printf(".");
	if (cell->cellState==P1)
		printf("X");
	if (cell->cellState==P2)
		printf("Y");
	printf(" ");
}

void freeCell (Element element)
{
	Cell cell = (Cell)element;
	if (element == NULL)
	{
		return;
	}
	free(element);
	return;

}

/*Sub function that update the neighbors cells that above or below*/
void update_n (Cell cell,int row ,int colum,Array board)
{
	int r,c,n;
	n=0;
	for (r=row-1; r<row+2; r++)
	{
		for (c=colum-1; c<colum+2;c++)
		{
			if (!(r==row && c==colum))
			{
				if(r>-1 && r<board->size)
					if (c>-1 && c<board->size)
					{
						cell->neighbors[n]= ((Cell)((Array)(board->elements[c]))->elements[r])->cellState;
						n++;
					}
			}
		}
	}
}

/*Main function for updating the cells neighbors*/
void updateNeib (Element element)
{
	Array array= (Array) element;

	int i,j;

	for (i=0; i<array->size;i++)
	{
		for (j=0; j<array->size; j++)
		{
			update_n(((Cell)((Array)(array->elements[i]))->elements[j]),j,i,array);
		}

	}
}

Element copyCell (Element element)
{
	int i;
	Cell cell = (Cell)element;
	Element newCell;
	if (cell->cellState==DEAD)
		newCell=createCell ('.');
	else
		if (cell->cellState==P1)
			newCell=createCell ('X');
		else
			if (cell->cellState==P2)
				newCell=createCell ('Y');
			else
				newCell=createCell ('B');
	for(i=0; i<8;i++)
	{
		((Cell)newCell)->neighbors[i]=cell->neighbors[i];
	}
	return newCell;
}

