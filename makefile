
gameOfLife: defs.o gameIO.o ZeroPlayer.o twoPlayer.o main.o	
	gcc defs.o gameIO.o ZeroPlayer.o twoPlayer.o main.o -o gameOfLife 
	
defs.o: defs.c defs.h 
	gcc -c defs.c 
	
gameIO.o: gameIO.c gameIO.h defs.h twoPlayer.h zeroPlayer.h 
	gcc -c gameIO.c 
	
ZeroPlayer.o: defs.h gameIO.h zeroPlayer.h ZeroPlayer.c
	gcc -c ZeroPlayer.c 
	
twoPlayer.o: twoPlayer.h gameIO.h defs.h twoPlayer.c
	gcc -c twoPlayer.c 
	
main.o: main.c zeroPlayer.h twoPlayer.h
	gcc -c main.c

clean:
	 rm -f *.o
