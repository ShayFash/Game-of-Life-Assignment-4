GCC_FLAGS= -Wall -Wextra -g 
GCC= gcc

program: game.c game.h main.c
	$(GCC) $(GCC_FLAGS)  -o program game.c main.c

testRunner: game.c game.h testRunner.c
	$(GCC) $(GCC_FLAGS)  -o testRunner game.c testRunner.c

clean:
	rm -f program
	rm -f testRunner
	rm -f *.o 
	rm -f *.a