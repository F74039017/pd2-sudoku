s: Solve.o Sudoku.o
	g++ -o Solve Sudoku.o Solve.o

q: GiveQuestion.o Sudoku.o
	g++ -o GiveQuestion Sudoku.o GiveQuestion.o

Solve.o: Solve.cpp
	g++ -c Solve.cpp

GiveQuestion.o: GiveQuestion.cpp
	g++ -c GiveQuestion.cpp

Sudoku.o: Sudoku.h Sudoku.cpp
	g++ -c Sudoku.cpp


clean:
	rm GiveQuestion Solve *.o
