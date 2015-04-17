Sudoku Solver and Generator
===========================
The program is a command line utility to slove and give a sudoku grid.<br />
The grid contain four 3x3 -1 box, and such box can only appear once in each 
row or column.<br />
The program will output 0, 1 and solved grid, 2 for unsolve, unique solve and 
multiple solve respectively.<br />
I/O are stdin and stdout.<br />

Environment 
--------------------------
OS: ubuntu 14.04 LTS<br />
gcc version: 4.8.2<br />

Compilation 
--------------------------
Solve question:
`make s`<br />
Give question:
`make q`<br />

Usage
--------------------------
*Solve*<br />
Run `./Solve` and input a 12x12 gird.<br />
*GiveQuestion*<br />
Run `./Givequestion`<br />
*GiveQuestion and Solve*<br />
Run `./GiveQuestion | ./Solve`<br />

Demo 
---------------------------
GiveQuestion: `./GiveQuestion > file.in` `cat file.in`

	0 0 0 -1 -1 -1 0 0 0 0 0 0
	7 8 0 -1 -1 -1 0 5 0 0 0 0
	5 6 3 -1 -1 -1 0 8 0 0 0 0
	4 0 0 0 9 0 1 0 0 -1 -1 -1
	0 0 0 2 0 0 0 0 0 -1 -1 -1
	3 0 0 0 0 0 0 0 0 -1 -1 -1
	8 5 0 6 0 0 -1 -1 -1 0 0 0
	0 0 0 0 0 0 -1 -1 -1 0 0 4
	0 2 4 0 8 7 -1 -1 -1 0 0 1
	-1 -1 -1 8 0 0 0 6 0 0 5 0
	-1 -1 -1 0 0 0 5 3 0 7 0 0
	-1 -1 -1 0 0 3 0 0 7 2 4 0

Solve: `time ./Solve < file.in`

	1
	2 4 9 -1 -1 -1 7 1 6 3 8 5
	7 8 1 -1 -1 -1 3 5 4 6 2 9
	5 6 3 -1 -1 -1 2 8 9 4 1 7
	4 7 8 5 9 6 1 2 3 -1 -1 -1
	6 1 5 2 3 4 9 7 8 -1 -1 -1
	3 9 2 7 1 8 6 4 5 -1 -1 -1
	8 5 7 6 4 1 -1 -1 -1 9 3 2
	1 3 6 9 2 5 -1 -1 -1 8 7 4
	9 2 4 3 8 7 -1 -1 -1 5 6 1
	-1 -1 -1 8 7 9 4 6 2 1 5 3
	-1 -1 -1 4 6 2 5 3 1 7 9 8
	-1 -1 -1 1 5 3 8 9 7 2 4 6
	
	real	0m2.279s
	user	0m2.280s
	sys	0m0.003s
