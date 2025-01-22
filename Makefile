a.out: main.o engine.o game.o score.o
	gcc main.o engine.o game.o score.o -Wextra -Wall -pedantic -o game
	touch scores.txt

main.o: main.c game.h engine.h score.h
	gcc -c main.c -Wextra -Wall -pedantic

game.o: game.c game.h engine.h score.h
	gcc -c game.c -Wextra -Wall -pedantic

engine.o: engine.c engine.h score.h
	gcc -c engine.c -Wextra -Wall -pedantic

score.o: score.c score.h
	gcc -c score.c -Wextra -Wall -pedantic



.phony: clean
clean:
	rm -f *.o game scores.txt