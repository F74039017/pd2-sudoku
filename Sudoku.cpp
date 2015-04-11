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
	int template_qmap[12][12]={	
	{4, 2, 6, 8, 7, 3, 9, 5, 1, -1, -1, -1},
	{0, 0, 3, 9, 5, 0, 6, 0, 4, -1, -1, -1},
	{9, 0, 1, 6, 2, 4, 8, 0, 0, -1, -1, -1},
	{-1, -1, -1, 1, 3, 2, 0, 8, 7, 9, 5, 6},
	{-1, -1, -1, 0, 8, 0, 1, 9, 0, 4, 2, 0},
	{-1, -1, -1, 4, 9, 6, 2, 3, 0, 8, 7, 1},
	{1, 0, 0, 0, 4, 0, -1, -1, -1, 6, 9, 5},
	{0, 0, 4, 0, 6, 0, -1, -1, -1, 1, 3, 7},
	{6, 9, 5, 0, 1, 7, -1, -1, -1, 2, 8, 4},
	{3, 1, 2, -1, -1, -1, 7, 4, 0, 5, 0, 9},
	{7, 4, 8, -1, -1, -1, 0, 6, 9, 3, 0, 2},
	{0, 6, 0, -1, -1, -1, 3, 1, 0, 7, 0, 8}};
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

	/* check multiple solution */
	if(UniqueSquare())
	{
		cout << "2" << endl;
		return;
	}
	transpose();
	if(UniqueSquare())
	{
		cout << "2" << endl;
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

/* Choose candididate by ncan array */
void Sudoku::setncan(int row, int col, bool ncan[])
{
	/* test number is used in col or row */
	for(int i=0; i<size; i++)
	{
		ncan[map[i][col]] = true;
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

bool Sudoku::same2(int row, int col, vector<int> &record)
{
	bool a[10];
	for(int i=0; i<10; i++)
		a[i] = false;
	setncan(row, col, a);
	int k=0;
	vector<int> temp;
	for(int i=1; i<10; i++)
		if(i==record[k])
			k++, temp.push_back(i);
	record = temp;
	if(record.size()>1)
		return true;
	else
		return false;
}

bool Sudoku::same2Check(int row[], int col[], vector<int> &record)
{
	bool a[10], b[10];
	for(int z=0; z<10; z++)
	{		
		a[z] = false;
		b[z] = false;
	}
	setncan(row[0], col[0], a), setncan(row[1], col[1], b);
	for(int i=1; i<10; i++)
		if(a[i]==0 && b[i]==0) // is possible
			record.push_back(i);
	if(record.size()>1)
		return true;
	else
		return false;
}

bool Sudoku::UniqueSquare()
{
	for(int k=0; k<size; k++) // all row
	{
		for(int i=0; i<size/width; i++) // group
		{
			int offset = i*width;
			int cnt=0;
			int col[2];
			for(int j=0; j<width; j++) // element in group
			{
				int index = offset+j;
				if(map[k][index]==0)
					col[cnt++] = index;
				if(cnt==2)
				{
					int row[2];
					row[0] = row[1] = k;
					vector<int> record;
					if(same2Check(row, col, record)) // check up
						for(int c=k+1; c<size; c++) // locate down
							if(map[c][col[0]]==0 && map[c][col[1]]==0 && c/width!=k/width) // not in same block
							{
								vector<int> record1 = record;
								if(same2(c, col[0], record1) && same2(c, col[1], record1))
									return true;
							}
				}
			}

		}
	}
	return false;
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
