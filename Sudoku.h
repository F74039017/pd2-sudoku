#include <iostream>
using namespace std;

class Sudoku
{
public:
	static const int size = 12;
	static const int width = 3; // block width
	Sudoku();
	void setMap(int map[][size]);
	void ReadIn();
	void Solve();
	void GiveQuestion();
	void setSwapTimes(int times); // default is 500

private:
	int ans; // count ans number
	bool wrongMap; // check init wrong map
	int map[size][size]; // used to solve
	int qmap[size][size]; // question map
	int ansmap[size][size]; // ans map
	int swaptimes;

	/* Print qmap or ansmap by giving 'q' or 's' */
	void printMap(char qs);

	/***	 Solve		***/
	int backTrack(); // sovle by backtracking
	void setncan(int row, int col, bool ncan[]); // set not can.
	bool ok(int row, int col, int test); // check test number is ok

	/***	 Give 		***/
	void chooseLine(int &r, int &t);
	void swapRowLine();
	void swapColLine();
	void chooseGroup(int &r, int &t);
	void swapRowGroup();
	void swapColGroup();
	void startSwap(); // swap 4 type 'swaptimes' times

};
