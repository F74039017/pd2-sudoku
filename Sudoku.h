#include <iostream>
#include <cstring>
using namespace std;

class Sudoku
{
public:
	static const int size = 12;
	static const int width = 3; // block width
	Sudoku();
	Sudoku(int map[][size]);
	void setMap(int map[][size]);
	void printMap();
	void ReadIn();
	void Solve();
	bool Solve_print(); 
	void GiveQuestion();
	int getans();

private:
	int map[size][size];
	int ans;
	bool wrongMap;
	
	bool ok(int row, int col, int test);
	void setncan(int row, int col, bool ncan[]);
};
