/*
 * main.c
 *
 *  Created on: Dec 6, 2016
 *      Author: ise
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"zeroPlayer.h"
#include"twoPlayer.h"

int main(int argc, char *argv[])
{
	char *path= "/home/eliasy/zero5.txt";
	int size, iteration,player;
	size = atoi(argv[2]);
    iteration = atoi(argv[4]);
     player= atoi(argv[1]);
	//size = 5;
	// iteration = 1;
	//player= 1;
    if (player == 1 )
	{
		zeroPlayer(size,argv[3],iteration);
    	//zeroPlayer(size,path,iteration);
	}
	else
		twoPlayer(size,argv[3],iteration);

	return 0;
}

