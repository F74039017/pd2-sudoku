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
	int ansmap[size][size];
	int swaptimes;

	void printMap(char qs);

	/* Solve */
	int Solve_print(); 
	bool ok(int row, int col, int test);
	void setncan(int row, int col, bool ncan[]);

	/* Give */
	void chooseLine(int &r, int &t);
	void swapRowLine();
	void swapColLine();
	void chooseGroup(int &r, int &t);
	void swapRowGroup();
	void swapColGroup();
	void startSwap();

};
