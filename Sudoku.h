#include <iostream>
using namespace std;

class Sudoku
{
public:
	static const int size = 12;
	static const int width = 3; // block width
	Sudoku();
	Sudoku(int map[][size]); // not used
	void setMap(int map[][size]);
	void ReadIn();
	void Solve();
	void GiveQuestion();
	int getans();
	void setSwapTimes(int times);

private:
	int map[size][size];
	int ans;
	bool wrongMap;
	int qmap[size][size];
	int swaptimes;

	void printMap(char qs);

	/* Solve */
	bool Solve_print(); 
	bool ok(int row, int col, int test);
	void setncan(int row, int col, bool ncan[]);

	/* Give */
	void swapline(int &r, int &t);
	void swaprow();
	void swapcol();
	void startSwap();

};
