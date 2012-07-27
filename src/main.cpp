/*
 *
 * Main function of the example code-1: 8-puzzle
 *
 * */

#include<iostream>
#include<fstream>
#include "State.h"
#include "A_Star.h"
#include <stdlib.h>
using namespace std;

/* reading the input from file with the name specified in filename */
int read_inp(const char *filename, int*** array, int& sx, int& sy){
	ifstream fin;
	fin.open(filename);
	fin >> sx >> sy;
	*array = new int* [sx];
	for(int i=0; i<sx; i++)
		(*array)[i] = new int[sy];
	
	for(int i=0; i<sx; i++)
		for(int j=0; j<sy; j++)
			fin >> (*array)[i][j];

	fin.close();
	return 0;
}

void usage(){ cerr << "Usage: <exe> <input file>\n"; }

//int simpleAstar(char *fd)
extern "C" int simpleAstar(const char *fd, int start_x, int start_y, int target_x, int target_y)
{
	int** array;
	int size_x,size_y;
  //const char *fd = "inp/inp.txt";

	if(fd == NULL){
		usage();
		//exit(1);
    return 1;
	}
	
	read_inp(fd,&array,size_x,size_y);

  if(start_x < 0 || start_x > size_x)
    start_x = 0;
  if(start_y < 0 || start_y > size_y)
    start_y = 0;
  if(target_x < 0 || target_x > size_x)
    target_x = size_x - 1;  
  if(target_y < 0 || target_y > size_y)
    target_y = size_y - 1;

/*
int main(int argc, char *argv[])
{
	int** array;
	int size_x,size_y;
  int start_x = 1, start_y = 1, target_x = 2, target_y = 2;
  //const char *fd = "inp/inp.txt";

	if(argc != 6){
		usage();
		//exit(1);
    return 1;
	}
	
  start_x = atoi(argv[2]);
  start_y = atoi(argv[3]);
  target_x = atoi(argv[4]);
  target_y = atoi(argv[5]);
*/
	read_inp(fd,&array,size_x,size_y);
	/* the initial state (the root of the a-star tree) */
	State *x = new State(array, size_x, size_y, start_x, start_y, target_x, target_y);
	x->get_env()->print();

	A_Star as;
	int number_of_states;
	State *sol = as.solve(x,number_of_states);

	cout << "\nThe path followed:\n";
    for(int i=0;i<number_of_states;i++)
    	sol[i].print();


	//cout << "\nThe map locations that have been explored during A-star search are shown with X\n";
	//sol[0].get_env()->print();
	
	return 0;
}

