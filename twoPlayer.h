/*
 * twoPlayer.h
 *
 *  Created on: Dec 16, 2016
 *      Author: eliasy
 */

#ifndef TWOPLAYER_H_
#define TWOPLAYER_H_
#include "defs.h"

Element evolveCellTW (Element element);
void twoPlayer(int size, char * fileName, int numIteration);
int validIndex(Element arr, int drow, int dcolumn, State compareValue);

#endif /* TWOPLAYER_H_ */
