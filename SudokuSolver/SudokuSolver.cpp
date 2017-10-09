// SudokuSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

int stupidfun1(int x) {
	if (x == 0||x==1) {
		return 1;
	}
	else {
		return -2;
	}
}

int stupidfun2(int x) {
	if (x == 2 || x == 1) {
		return -1;
	}
	else {
		return 2;
	}
}

// Returns true if you cannot put k in the i,j entry of A
bool IsEntryForbidden(int i, int j, int k, int(*A)[9]) {
	bool forbid = false;

	//Check ith row
	for (int jj = 0; jj < 9; jj++) {
		if (A[i][jj] == k) {
			forbid = true;
			goto label;
		}
	}

	//Check jth column
	for (int ii = 0; ii < 9; ii++) {
		if (A[ii][j] == k) {
			forbid = true;
			goto label;
		}
	}

	//Check square
	int iloc = i % 3;
	int jloc = j % 3;
	if (A[i][j+stupidfun1(jloc)]==k || A[i][ j + stupidfun2(jloc)] == k|| A[i + stupidfun1(iloc)][j ] == k || A[i + stupidfun2(iloc)][j ] == k || A[i + stupidfun1(iloc)][j + stupidfun1(jloc)] == k || A[i + stupidfun1(iloc)][j + stupidfun2(jloc)] == k || A[i + stupidfun2(iloc)][j + stupidfun1(jloc)] == k || A[i + stupidfun2(iloc)][j + stupidfun2(jloc)] == k){
		forbid = true;
		goto label;
	}

label:
	return forbid;
}

// Returns true if k is the only number which can be placed in the i,jth entry of A
int WhichInteger(int i, int j, int(*A)[9]) {
	int WhichCanFit[9] = { 1,1,1,1,1,1,1,1,1 };
	for (int counter = 1; counter <10; counter++) {
		if (IsEntryForbidden(i, j, counter, A)) {
			WhichCanFit[counter-1] = 0;
		}
	}
	if (accumulate(WhichCanFit, WhichCanFit + 9, 0) == 1) {
		int p = distance(WhichCanFit,find(WhichCanFit, WhichCanFit + 9, 1));
		return p+1;
	}
	else {
		return 0;
	}
}

void PrintArray(int(*A)[9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << A[i][j] << ",";
		}
		cout << "\n";
	}
}
void CompleteSudoku(int(*A)[9]) {
	int counter = 0;
	while (counter < 81) {
		counter = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (A[i][j] == 0) {
					A[i][j] = WhichInteger(i, j, A);
				}
				else {
					counter++;
				}
			}
		}
	}
	PrintArray(A);
}

int main()
{
	int Example[9][9] = { { 0,0,0,2,6,0,7,0,1 },{ 6,8,0,0,7,0,0,9,0 },{1,9,0,0,0,4,5,0,0},{8,2,0,1,0,0,0,4,0},{0,0,4,6,0,2,9,0,0},{0,5,0,0,0,3,0,2,8},{0,0,9,3,0,0,0,7,4},{0,4,0,0,5,0,0,3,6},{7,0,3,0,1,8,0,0,0} };
	CompleteSudoku(Example);
	system("pause");
    return 0;
}

