all: main.o Sudoku.o
	g++ -o project1 Sudoku.o main.o

main.o: main.cpp
	g++ -c main.cpp

Sudoku.o: Sudoku.h Sudoku.cpp
	g++ -c Sudoku.cpp


clean:
	rm project1 *.o
