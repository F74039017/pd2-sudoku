#include "Sudoku.h"

Sudoku::Sudoku()
{
	memset(map, 0, sizeof(map));
	ans = 0;
}

Sudoku::Sudoku(int map[][size])
{
	setMap(map);
}

void Sudoku::ReadIn()
{
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			cin >> map[i][j];	
}

void Sudoku::setMap(int map[][size])
{
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			this->map[i][j] = map[i][j];
}

void Sudoku::printMap()
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			cout << map[i][j];
			if(j!=size-1)
				cout << " ";
		}
		cout << endl; 
	}	
}

/* handle the output and function question require */
void Sudoku::Solve()
{
	if(!Solve_print())
		cout << "0" << endl;
}

/* the function set ans and print the matrxi with if solvable */
bool Sudoku::Solve_print()
{
	int row, col;
	/* locate hole and check finish */
	/* recursive out condition */
	bool finished=true;
	for(row=0; row<size; row++)
	{
		for(col=0; col<size; col++)
			if(map[row][col]==0)
			{
				//--cout << row*size+col << endl;
				finished = false;
				break;
			}
		if(finished==false)
			break;
	}
	//--cout << "locate hole in " << row << ", " << col << endl;
	if(finished)
	{
		ans++;
		cout << ans << endl;
		printMap();
		return true;
	}
	
	/* backtracking */
	for(int test=1; test<=9; test++)
	{
		if(ok(row, col, test))
		{
			map[row][col] = test;
			if(Solve())
				return true;
			/* if failed then remark */
			map[row][col] = 0;
		}
	}
	//--cout << "try all test number" << endl;
	return false;
		
}

bool Sudoku::ok(int row, int col, int test)
{
	bool check=true;
	/* test number is used in col or row */
	for(int i=0; i<size; i++)
	{
		if(map[i][col] == test)
			check = false;
		else if(map[row][i] == test)
			check = false;
	}
	/* test number is used in the block */
	int blocki = row-row%width;
	int blockj = col-col%width;
	for(int i=0; i<width; i++)
		for(int j=0; j<width; j++)
			if(map[blocki+i][blockj+j] == test)
				check = false;
	return check;
}

int Sudoku::getans()
{
	return ans;
}
