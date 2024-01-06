CFLAG = -Wno-implicit-function-declaration

all: gameLauncher
gameLauncher: object/gameLauncher.o object/gamePlay.o object/gameInitializer.o object/getter.o object/printer.o object/constants.o
	gcc -o gameLauncher object/gameLauncher.o object/gamePlay.o object/gameInitializer.o object/getter.o object/printer.o object/constants.o 

object/gameLauncher.o: source/gameLauncher.c 
	gcc $(CFLAG) -c -o object/gameLauncher.o source/gameLauncher.c -I include

object/gamePlay.o: source/gamePlay.c 
	gcc $(CFLAG) -c -o object/gamePlay.o  source/gamePlay.c -I include

object/gameInitializer.o: source/gameInitializer.c
	gcc -c -o object/gameInitializer.o source/gameInitializer.c 

object/getter.o: source/getter.c
	gcc -c -o object/getter.o source/getter.c 

object/printer.o: source/printer.c
	gcc -c -o object/printer.o source/printer.c -I include

object/constants.o: source/constants.c
	gcc -c -o object/constants.o source/constants.c
	
.PHONY: clean
.PHONY: all

clean:
	rm -f object/*.o gameLauncher