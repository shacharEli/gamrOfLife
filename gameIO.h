/*
 * gameIO.h
 *
 *  Created on: Dec 6, 2016
 *      Author: ise
 */

#include"defs.h"

#ifndef GAMEIO_H_
#define GAMEIO_H_


void printFromFile(char *fileName, int n);
int populateArray(char *fileName, Array array);
Array creat_Board(int size, char * fileName,int player);



#endif /* GAMEIO_H_ */
