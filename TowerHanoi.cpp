/**************************************************************
Problem: Solving Towers or Hanoi using recursion
Purpose: Practice
Compiled in Visual C++

Rules:
	-move one disk at a time
	-may only stack smaller disk on top of larger disk
	-3 positions (from, middle, to) to move



pseudocode:
moveDisks(int Disks, int FromPosition, int ToPosition)
	if(Disks = 1 for base case)
		return 1 move
	else
		move all disks except largest disk to middlePosition (Step 1)
		move largest disk to toPosition (Step 2)
		move all disks in middlePosition to toPosition (Step 3)


**************************************************************/

#include <iostream>
#include <string>
#include <math.h>
using namespace std;


//paramters: (number of disks, where disks start, where disks end)
string moveDisks(int NumDisks, int FromPosition, int ToPosition){

	int middlePosition; //to help move disks (middle man)

	string solution_step1, 
		solution_step2, 
		solution_step3,
		final_solution;

	//base case (Disks = 1)
	if (NumDisks == 1){
		final_solution = string("Position ") + to_string(FromPosition) + 
			string(" moves to position ") + to_string(ToPosition) + 
			string("\n");
		return final_solution;
	}
	else{
		//FromPosition + ToPosition + MiddlePosition = 6 => 1 + 3 + 2 = 6
		middlePosition = 6 - FromPosition - ToPosition;

		//Step 1: move all disks except largest disk (N-1) to middlePosition recursively
		solution_step1 = moveDisks(NumDisks - 1, FromPosition, middlePosition);

		//Step 2: move largest disk to toPosition
		solution_step2 = string("Position ") + to_string(FromPosition) +
			string(" moves to position ") + to_string(ToPosition) +
			string("\n");

		//Step 3: move all N-1 disks in middlePosition to toPosition
		solution_step3 = moveDisks(NumDisks - 1, middlePosition, ToPosition);

		//add all steps together
		final_solution = solution_step1 + solution_step2 + solution_step3;

		return final_solution;
	}

}

int main(){

	int NumberOfDisks = 2;
	cout << moveDisks(NumberOfDisks, 2, 3);
	system("pause");
	return 0;

}
