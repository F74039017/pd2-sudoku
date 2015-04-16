#include "Sudoku.h"
#include <cstring>
#include <cstdlib>
#include <ctime>
Sudoku::Sudoku()
{
	srand(time(NULL));
	memset(map, 0, sizeof(map));
	ans = 0;
	wrongMap = false;
	swaptimes = 500;
	/*int template_qmap[12][12]={	
	{5, 0, 0, 3, 0, 0, -1, -1, -1, 0, 4, 0},
	{0, 0, 2, 7, 0, 8, -1, -1, -1, 0, 0, 9},
	{0, 0, 8, 0, 6, 0, -1, -1, -1, 3, 1, 0},
	{-1, -1, -1, 0, 0, 0, 8, 0, 3, 0, 5, 0},
	{-1, -1, -1, 0, 0, 3, 0, 0, 0, 6, 0, 4},
	{-1, -1, -1, 9, 0, 1, 0, 2, 0, 8, 0, 0},
	{0, 5, 0, -1, -1, -1, 0, 3, 0, 0, 8, 7},
	{4, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0},
	{0, 7, 0, -1, -1, -1, 4, 0, 6, 0, 3, 0},
	{6, 9, 5, 1, 0, 0, 0, 0, 0, -1, -1, -1},
	{1, 3, 7, 0, 0, 4, 0, 0, 0, -1, -1, -1},
	{2, 8, 4, 0, 9, 5, 0, 1, 0, -1, -1, -1}};*/
	int template_qmap[12][12]={
	{0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0},
	{3, 5, 6, -1, -1, -1, 0, 8, 0, 0, 0, 0},
	{0, 7, 8, -1, -1, -1, 0, 5, 0, 0, 0, 0},
	{0, 3, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
	{0, 4, 0, 9, 0, 0, 1, 0, 0, -1, -1, -1},
	{0, 0, 0, 0, 2, 0, 0, 0, 0, -1, -1, -1},
	{0, 0, 0, 0, 0, 0, -1, -1, -1, 4, 0, 0},
	{4, 0, 2, 8, 0, 7, -1, -1, -1, 1, 0, 0},
	{0, 8, 5, 0, 6, 0, -1, -1, -1, 0, 0, 0},
	{-1, -1, -1, 0, 8, 0, 0, 6, 0, 0, 5, 0},
	{-1, -1, -1, 0, 0, 3, 0, 0, 7, 0, 4, 2},
	{-1, -1, -1, 0, 0, 0, 5, 3, 0, 0, 0, 7}};
	memcpy(qmap, template_qmap, sizeof(qmap));
}

/* Print qmap or ansmap by giving 'q' or 's' */
void Sudoku::printMap(char qs)
{
	int print[size][size];
	if(qs=='q')
		memcpy(print, qmap, sizeof(print));
	else if(qs=='s')
	{	
		cout << ans << endl;
		memcpy(print, ansmap, sizeof(print)); // change to the ansmap
	}
	else
		cerr << "print map error" << endl;

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			cout << print[i][j];
			if(j!=size-1)
				cout << " ";
		}
		cout << endl; 
	}	
}

void Sudoku::transpose()
{
	int mapt[size][size];
	memcpy(mapt, map, sizeof(map));
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			map[i][j] = mapt[j][i];
}

/*********************************
		Solve	Sudoku
*********************************/

/* Read map from STDIN */
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

/* Handle the output and function question require */
/* no -> 0, unique -> 1 and map, multi -> 2 */
void Sudoku::Solve()
{
	/*Check multiple solutions*/
	if(!multiCheck())
	{
		cout << "2" << endl;
		return;
	}

	/* Check -1 */
	if(!checkDonCare())
	{
		cout << "0" << endl;
		return;
	}

	/* wrong map check by base rule*/
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			if(!ok(i, j, map[i][j]))
				wrongMap = true;
	if(wrongMap)
	{
		cout << "0" << endl;
		return;
	}

	/* normal check */
	int type = backTrack();
	if(type==0)
		cout << "0" << endl;
	else if(type==1)
		printMap('s');
	else
		cout << "2" << endl;
}

/* return the ans type and set ansmap if exist */
int Sudoku::backTrack()
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
	//cout << "locate hole in " << row << ", " << col << endl;
	if(finished)
	{
		ans++;
		memcpy(ansmap, map, sizeof(ansmap));
		return 1;
	}
	
	/* set candidate */
	bool ncan[10]={0};
	setncan(row, col, ncan);

	/* backtracking */
	for(int test=1; test<=9; test++)
	{
		if(ncan[test] == false)
		{
			//cout << "test " << test << endl;
			map[row][col] = test;
			backTrack();
			if(ans>1)
				return 2;
			/* remark for next */
			map[row][col] = 0;
		}
	}
	//cout << "try all test number" << endl;
	if(!ans)
		return 0;
	else if(ans==1)
		return 1;
}

bool Sudoku::multiCheck()
{
	int cnt=0;
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			if(map[i][j])
				cnt++;
	if(cnt>90)
		return false;
	else
		return true;
}

/* Choose candididate by ncan array */
void Sudoku::setncan(int row, int col, bool ncan[])
{
	/* test number is used in col or row */
	for(int i=0; i<size; i++)
	{
		if(map[i][col]!=-1)
			ncan[map[i][col]] = true;
		if(map[row][i]!=-1)
			ncan[map[row][i]] = true;
	}
	/* test number is used in the block */
	int blocki = row-row%width;
	int blockj = col-col%width;
	for(int i=0; i<width; i++)
		for(int j=0; j<width; j++)
			ncan[map[blocki+i][blockj+j]] = true;
}

/* check whether test number is used */
bool Sudoku::ok(int row, int col, int test)
{
	if(test==-1 || test==0)
		return true;
	bool check=true;
	// test number is used in col or row 
	for(int i=0; i<size; i++)
	{
		if(i!=row)
			if(map[i][col] == test)
				check = false;
		if(i!=col)
			if(map[row][i] == test)
				check = false;
	}
	// test number is used in the block 
	int blocki = row-row%width;
	int blockj = col-col%width;
	for(int i=0; i<width; i++)
		for(int j=0; j<width; j++)
			if(map[blocki+i][blockj+j] == test)
				if(blocki+i!=row && blockj+j!=col)
					check = false;
	return check;
}

/* Return true when no error -1 input */
bool Sudoku::checkDonCare()
{
	bool exist = false;
	bool vis[size][size];
	memset(vis, 0, sizeof(vis));
	for(int i=0; i<size; i++)
	{
		if(i%width==0) // reset exist in row group
			exist=false;
		for(int j=0; j<size; j++)
		{
			if(map[i][j]==-1 && !vis[i][j]) // first time to meet -1
			{
				if(exist) // alreay exist one -1 block in the group
					return false;
				if(i%3==0 && j%3==0) // in left up corner
				{
					for(int k=0; k<width; k++)
						for(int l=0; l<width; l++)
						{
							if(map[i+k][j+l]==-1) // elements in block are -1
								vis[i+k][j+l] = true;
							else
								return false;
						}
					for(int k=0; k<size/width; k++) // not duplicated in col group
					{
						int row=k*3;
						if(map[row][j]==-1 && row!=i)
							return false;
					}
					exist = true;
				}
				else
					return false;
			}
		}
	}
	return true;
}

/*********************************
		Give	Question
**********************************/
void Sudoku::chooseLine(int &r, int &t)
{
	r = rand()%12;
	t = rand()%2;
	if(t)
		t = 1;
	else
		t = 2;
	if(0<=r && r<3)
		t = (r+t)%3;	
	else if(3<=r && r<6)
		t = (r+t)%3+3;
	else if(6<=r && r<9)
		t = (r+t)%3+6;
	else if(9<=r && r<12)
		t = (r+t)%3+9;
	//cout << r << " and " << t << endl;
}


void Sudoku::swapRowLine()
{
	int a, b;
	chooseLine(a, b);
	int temp[size];
	memcpy(temp, qmap[a], sizeof(temp));
	memcpy(qmap[a], qmap[b], sizeof(temp));
	memcpy(qmap[b], temp, sizeof(temp));
}

void Sudoku::swapColLine()
{
	int a, b;
	chooseLine(a, b);
	int temp[size];
	for(int j=0; j<size; j++)
	{
		temp[j] = qmap[j][a];
		qmap[j][a] = qmap[j][b];
		qmap[j][b] = temp[j];
	}
}


void Sudoku::chooseGroup(int &r, int &t)
{
	r = rand()%4;
	t = rand()%3+1;
	t = (r+t)%4;
	r *= 3, t *= 3;
}

void Sudoku::swapRowGroup()
{
	int size = 12;
	int width = 3;
	int a, b;
	chooseGroup(a, b);
	int temp[width][size];
	memcpy(temp, map[a], sizeof(temp));
	memcpy(map[a], map[b], sizeof(temp));
	memcpy(map[b], temp, sizeof(temp));
}

void Sudoku::swapColGroup()
{
	int size = 12;
	int width = 3;
	int a, b;
	chooseGroup(a, b);
	int temp[size][width];
	for(int i=0; i<size; i++)
		for(int j=0; j<width; j++)
		{
			temp[i][j] = map[i][a+j];
			map[i][a+j] = map[i][b+j];
			map[i][b+j] = temp[i][j];
		}
}

void Sudoku::setSwapTimes(int times)
{
	swaptimes = times;
}

/* Swap the map by swap group and line for 'swaptimes' */
void Sudoku::startSwap()
{
	for(int i=0; i<swaptimes; i++)
		swapRowLine(), swapColLine(), swapRowGroup(), swapColGroup();
}

void Sudoku::GiveQuestion()
{
	startSwap();
	printMap('q');
}
