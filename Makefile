game: main.o engine.o game.o score.o board.o readingFromFile.o
	gcc main.o engine.o game.o score.o board.o readingFromFile.o -Wextra -Wall -pedantic -o game 
	touch scores.txt

main.o: main.c game.h engine.h score.h board.h readingFromFile.h
	gcc -c main.c -Wextra -Wall -pedantic

game.o: game.c game.h engine.h score.h 
	gcc -c game.c -Wextra -Wall -pedantic

engine.o: engine.c engine.h score.h
	gcc -c engine.c -Wextra -Wall -pedantic

board.o: board.c board.h engine.c game.c
	gcc -c board.c -Wextra -Wall -pedantic

score.o: score.c score.h board.h game.h
	gcc -c score.c -Wextra -Wall -pedantic

readingFromFile.o: readingFromFile.c engine.h game.h
	gcc -c readingFromFile.c -Wextra -Wall -pedantic

tests.o: tests.c engine.h score.o board.h
	gcc -c tests.c -Wextra -Wall -pedantic

tests: engine.o score.o board.o tests.o 
	gcc tests.o engine.o score.o board.o game.o -Wextra -Wall -pedantic -o tests
	./tests

.PHONY: clean
clean:
	rm -f *.o game scores.txt tests
