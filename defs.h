/*
 * defs.h
 *
 *  Created on: Dec 6, 2016
 *      Author: ise
 */

#ifndef DEFS_H_
#define DEFS_H_

/*
 * Basic definitions
 */
typedef void * Element;
typedef Element (*CopyFunction)(Element);
typedef void (*FreeFunction)(Element);
typedef void (*PrintFunction)(Element);
typedef Element (*EvolveFunction)(Element);

/*
 * Structs and enums
 */
typedef enum e_state {DEAD, P1, P2, BLANK}State;

struct t_cell
{
	State cellState;
	State neighbors[8];
};

typedef struct t_cell *Cell;

struct t_array
{
	int size;
	Element* elements;
	CopyFunction copyElement;
	FreeFunction freeElement;
	PrintFunction printElement;
	EvolveFunction evolveElement;
} t_array;

typedef struct t_array *Array;


/*
 * Function Deceleration
 */
Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve);
void destroyArray(Array array);
void set(Array array, int i, Element element);		//assigns array[i]=element;
Element get(Array array, int i);					//returns array[i]

// Array definitions
Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve);
Element copyArray(Element element);
void printArray(Element element);
void destroyArray(Array array);
//void evolve_arr (Element element );
void free_Arr(Element element);
Element createArr(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve);
Element evolve_array(Element element);
void updateNeib (Element element);
void printArr(Element element,int check );

Element createCell(char c);
void printCell(Element element);
void freeCell (Element element );
Element copyCell (Element element);
void evolve_CellZP (Element element );

#endif /* DEFS_H_ */
